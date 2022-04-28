/**
 ******************************************************************************
 * @file          : GestureDetectLR.c
 * @author        : Robbe Elsermans
 * @brief         : Dit bestand bevat de methodes om een Links Rechts gesture te detecteren
 ******************************************************************************
 *
 * @attention
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include "GestureDetectLR.h"

// Gesture Right Left
static bool hasLeft = false;
static bool hasCenter = false;
static bool hasRight = false;

static int maxDistanceObject = 400;
static int minDistanceObject = 100;
static float timerMeasurment = 0;
static bool timerMeasurementSet = false;
static int timerMeasurmentTimeout = 750; // 750 mseconden

static int prevState0 = 0;

bool CheckGestureLR(bool *_gestureLR, bool *_object, Resultaat_t *Result)
{
    // Detecteren commando van links naar rechts
    // Eerst moet sensor links minder binnen krijgen
    // Dan sensor center
    // Als laatste sensor rechts
    if (*_object)
    {
        int8_t sta0 = Result[XSHUT_2].status;
        int8_t sta1 = Result[XSHUT_3].status;
        int8_t sta2 = Result[XSHUT_1].status;
        int dis0 = (int)Result[XSHUT_2].distance;
        int dis1 = (int)Result[XSHUT_3].distance;
        int dis2 = (int)Result[XSHUT_1].distance;

        if ((dis0 < maxDistanceObject) && (dis0 > minDistanceObject) && (dis2 > maxDistanceObject) && (sta0 == 0 || (prevState0 == 0)) && !hasLeft && !hasCenter && !hasRight && dis0 != 0) // Sensor right
        {
            hasLeft = true;
            printf(" LR left  %4d \r\n", dis0);
        }
        else if ((dis1 < maxDistanceObject) && (sta1 == 0) && hasLeft && !hasCenter && !hasRight && dis1 != 0) // Sensor center
        {
            hasCenter = true;
            printf(" LR center  %4d \r\n", dis1);
        }
        else if ((dis2 < maxDistanceObject) && (sta2 == 0) && hasLeft && hasCenter && !hasRight && dis2 != 0) // Sensor left
        {
            hasRight = true;
            printf(" LR right  %4d \r\n", dis2);
        }

        prevState0 = sta0;
    }

    // Een timeout timer plaatsen
    if (timerMeasurementSet == false && (hasRight || hasCenter || hasLeft))
    {
        timerMeasurementSet = true;
        timerMeasurment = HAL_GetTick();
        // printf("timer set Trigger: \r\n");
    }

    // Bij het afgaan van de timer
    if ((timerMeasurementSet && ((HAL_GetTick() - timerMeasurment) >= timerMeasurmentTimeout)) || *_gestureLR)
        if (((HAL_GetTick() - timerMeasurment) >= timerMeasurmentTimeout))
        {
            timerMeasurementSet = false;
            hasRight = false;
            hasLeft = false;
            hasCenter = false;
        }

    if (hasRight && hasCenter && hasLeft)
    {
        timerMeasurementSet = false;
        hasRight = false;
        hasLeft = false;
        hasCenter = false;
        return true;
    }
    else
        return false;
}
