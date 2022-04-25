/**
 ******************************************************************************
 * @file          : GestureDetectDU.c
 * @author        : Robbe Elsermans
 * @brief         : Dit bestand bevat de methodes om een Onder Boven gesture te detecteren
 ******************************************************************************
 *
 * @attention
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include "GestureDetectDU.h"

// Gesture Right Left
static bool hasCenter = false;
static bool hasBottom = false;

static int maxDistanceObject = 300;
static float timerMeasurment = 0;
static bool timerMeasurementSet = false;
static int timerMeasurmentTimeout = 750; // 1 seconden

bool CheckGestureDU(bool *_gestureDU, bool *_object, Resultaat_t *Result)
{
    // Detecteren commando van Onder naar boven
    // Eerst moet sensor onder (4) minder binnen krijgen
    // Dan sensor center (1)
    // Als laatste sensor boven (3)
    if (*_object)
    {
        int8_t sta0 = Result[LEFT].status;
        int8_t sta1 = Result[CENTER].status;
        int8_t sta2 = Result[RIGHT].status;
        int dis0 = (int)Result[LEFT].distance;
        int dis1 = (int)Result[CENTER].distance;
        int dis2 = (int)Result[RIGHT].distance;

        if ((dis0 < maxDistanceObject) && (dis2 < maxDistanceObject) && (dis1 > maxDistanceObject) && (sta0 == 0) && (sta2 == 0) && (!hasBottom && !hasCenter) && (dis0 != 0 && dis2 != 0)) // Sensor bottom
        {
            hasBottom = true;
            printf("DU Bottom: %4d\t%4d \r\n",dis0, dis2);
        }
        else if ((dis1 < maxDistanceObject) && (sta1 == 0) && hasBottom && !hasCenter && dis1 != 0) // Sensor center
        {
            hasCenter = true;
            printf("DU center: %4d \r\n", dis1);
        }

        // printf("TOP %2d, center %2d, BOTTOM %2d \r\n", hasTop, hasCenter, hasBottom);
    }

    // Een timeout timer plaatsen
    if (timerMeasurementSet == false && (hasBottom || hasCenter))
    {
        timerMeasurementSet = true;
        timerMeasurment = HAL_GetTick();
        // printf("timer set Trigger: \r\n");
    }

    // Bij het afgaan van de timer
    if ((timerMeasurementSet && ((HAL_GetTick() - timerMeasurment) >= timerMeasurmentTimeout)) || *_gestureDU)
        if (((HAL_GetTick() - timerMeasurment) >= timerMeasurmentTimeout))
        {
            timerMeasurementSet = false;
            hasBottom = false;
            hasCenter = false;
        }

    if (hasBottom && hasCenter)
    {
        timerMeasurementSet = false;
        hasBottom = false;
        hasCenter = false;
        return true;
    }
    else
        return false;
}
