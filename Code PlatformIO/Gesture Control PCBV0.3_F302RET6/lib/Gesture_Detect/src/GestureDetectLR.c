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

static int maxDistanceObject = 300;
static float timerMeasurment = 0;
static bool timerMeasurementSet = false;
static int timerMeasurmentTimeout = 1200; // 1 seconden

bool CheckGestureLR(bool *_gestureLR, bool *_object, VL53L3CX_Result_t *Result)
{
    // Detecteren commando van links naar rechts
    // Eerst moet sensor links minder binnen krijgen
    // Dan sensor center
    // Als laatste sensor rechts
    if (*_object)
    {
        uint8_t sta0 = (uint8_t)Result[LEFT].ZoneResult[0].Status[0];
        uint8_t sta1 = (uint8_t)Result[CENTER].ZoneResult[0].Status[0];
        uint8_t sta2 = (uint8_t)Result[RIGHT].ZoneResult[0].Status[0];
        int dis0 = (int)Result[LEFT].ZoneResult[0].Distance[0];
        int dis1 = (int)Result[CENTER].ZoneResult[0].Distance[0];
        int dis2 = (int)Result[RIGHT].ZoneResult[0].Distance[0];

        if ((dis0 < maxDistanceObject) && (dis2 > maxDistanceObject) && (sta0 == 0) && !hasLeft && !hasCenter &&  !hasRight && dis0 != 0) // Sensor right
        {
            hasLeft = true;
            printf("left \r\n");
        }
        else if ((dis1 < maxDistanceObject) && (sta1 == 0) && hasLeft && !hasCenter && !hasRight && dis1 != 0) // Sensor center
        {
            hasCenter = true;
            printf("center \r\n");
        }
        else if ((dis2 < maxDistanceObject) && (sta2 == 0) && hasLeft && hasCenter && !hasRight && dis2 != 0) // Sensor left
        {
            hasRight = true;
            printf("right \r\n");
        }
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

    if(hasRight && hasCenter && hasLeft)
    return true;
    else
    return false;
}
