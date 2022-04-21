/**
 ******************************************************************************
 * @file          : GestureDetectRL.c
 * @author        : Robbe Elsermans
 * @brief         : Dit bestand bevat de methodes om een Rechts Links gesture te detecteren
 ******************************************************************************
 *
 * @attention
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include "GestureDetectRL.h"

// Gesture Right Left
static bool hasLeft = false;
static bool hasCenter = false;
static bool hasRight = false;

static int maxDistanceObject = 300;
static float timerMeasurment = 0;
static bool timerMeasurementSet = false;
static int timerMeasurmentTimeout = 1200; // 1 seconden

bool CheckGestureRL(bool *_gestureRL, bool *_object, Resultaat_t *Result)
{
    // Detecteren commando van rechts naar links
    // Eerst moet sensor right minder binnen krijgen
    // Dan sensor center
    // Als laatste sensor left
    if (*_object)
    {
        int8_t sta0 = Result[LEFT].status;
        int8_t sta1 = Result[CENTER].status;
        int8_t sta2 = Result[RIGHT].status;
        int dis0 = (int)Result[LEFT].distance;
        int dis1 = (int)Result[CENTER].distance;
        int dis2 = (int)Result[RIGHT].distance;

        if ((dis2 < maxDistanceObject) && (dis0 > maxDistanceObject) && (sta2 == 0) && !hasRight && !hasCenter &&  !hasLeft && dis2 != 0) // Sensor right
        {
            hasRight = true;
            //printf("right  %4d \r\n", dis2);
        }
        else if ((dis1 < maxDistanceObject) && (sta1 == 0) && hasRight && !hasCenter && !hasLeft && dis1 != 0) // Sensor center
        {
            hasCenter = true;
            //printf("center %4d \r\n", dis1);
        }
        else if ((dis0 < maxDistanceObject) && (sta0 == 0) && hasRight && hasCenter && !hasLeft && dis0 != 0) // Sensor left
        {
            hasLeft = true;
            //printf("left %4d \r\n", dis0);
        }

        //printf("left %2d, center %2d, right %2d \r\n", hasLeft, hasCenter, hasRight);
    }

    // Een timeout timer plaatsen
    if (timerMeasurementSet == false && (hasRight || hasCenter || hasLeft))
    {
        timerMeasurementSet = true;
        timerMeasurment = HAL_GetTick();
        // printf("timer set Trigger: \r\n");
    }

    // Bij het afgaan van de timer
    if ((timerMeasurementSet && ((HAL_GetTick() - timerMeasurment) >= timerMeasurmentTimeout)) || *_gestureRL)
        if (((HAL_GetTick() - timerMeasurment) >= timerMeasurmentTimeout))
        {
            timerMeasurementSet = false;
            hasRight = false;
            hasLeft = false;
            hasCenter = false;
        }

    if(hasRight && hasCenter && hasLeft)
    return true;
    else
    return false;
}
