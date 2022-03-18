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

bool CheckGestureRL(bool *_gestureRL, bool *_object, RANGING_SENSOR_Result_t *Result)
{
    // Detecteren commando van rechts naar links
    // Eerst moet sensor right minder binnen krijgen
    // Dan sensor center
    // Als laatste sensor left
    if (*_object)
    {
        uint8_t sta0 = (uint8_t)Result[VL53L3A2_DEV_LEFT].ZoneResult[0].Status[0];
        uint8_t sta1 = (uint8_t)Result[VL53L3A2_DEV_CENTER].ZoneResult[0].Status[0];
        uint8_t sta2 = (uint8_t)Result[VL53L3A2_DEV_RIGHT].ZoneResult[0].Status[0];
        int dis0 = (int)Result[VL53L3A2_DEV_LEFT].ZoneResult[0].Distance[0];
        int dis1 = (int)Result[VL53L3A2_DEV_CENTER].ZoneResult[0].Distance[0];
        int dis2 = (int)Result[VL53L3A2_DEV_RIGHT].ZoneResult[0].Distance[0];

        if ((dis2 < maxDistanceObject) && (dis0 > maxDistanceObject) && (sta2 == 0) && !hasRight && !hasCenter &&  !hasLeft) // Sensor right
        {
            hasRight = true;
            //printf("right \r\n");
        }
        else if ((dis1 < maxDistanceObject) && (sta1 == 0) && hasRight && !hasCenter && !hasLeft) // Sensor center
        {
            hasCenter = true;
            //printf("center \r\n");
        }
        else if ((dis0 < maxDistanceObject) && (sta0 == 0) && hasRight && hasCenter && !hasLeft) // Sensor left
        {
            hasLeft = true;
            //printf("left \r\n");
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
