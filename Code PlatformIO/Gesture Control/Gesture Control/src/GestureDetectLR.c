#include "GestureDetectLR.h"

// Gesture Right Left
static bool hasLeft = false;
static bool hasCenter = false;
static bool hasRight = false;

static int maxDistanceObject = 250;
static float timerMeasurment = 0;
static bool timerMeasurementSet = false;
static int timerMeasurmentTimeout = 1200; // 1 seconden

bool CheckGestureLR(bool *_gestureLR, bool *_object, RANGING_SENSOR_Result_t *Result)
{
    // Detecteren commando van links naar rechts
    // Eerst moet sensor links minder binnen krijgen
    // Dan sensor center
    // Als laatste sensor rechts
    if (*_object)
    {
        uint8_t sta0 = (uint8_t)Result[VL53L3A2_DEV_LEFT].ZoneResult[0].Status[0];
        uint8_t sta1 = (uint8_t)Result[VL53L3A2_DEV_CENTER].ZoneResult[0].Status[0];
        uint8_t sta2 = (uint8_t)Result[VL53L3A2_DEV_RIGHT].ZoneResult[0].Status[0];
        int dis0 = (int)Result[VL53L3A2_DEV_LEFT].ZoneResult[0].Distance[0];
        int dis1 = (int)Result[VL53L3A2_DEV_CENTER].ZoneResult[0].Distance[0];
        int dis2 = (int)Result[VL53L3A2_DEV_RIGHT].ZoneResult[0].Distance[0];

        // if ((dis2 < maxDistanceObject) && (dis0 > maxDistanceObject) && (sta2 == 0) && !hasRight && !hasCenter &&  !hasLeft) // Sensor right
        // {
        //     hasRight = true;
        // }
        // else if ((dis1 < maxDistanceObject) && (sta1 == 0) && hasRight && !hasCenter && !hasLeft) // Sensor center
        // {
        //     hasCenter = true;
        // }
        // else if ((dis0 < maxDistanceObject) && (sta0 == 0) && hasRight && hasCenter && !hasLeft) // Sensor left
        // {
        //     hasLeft = true;
        // }
         if ((dis0 < maxDistanceObject) && (dis2 > maxDistanceObject) && (sta0 == 0) && !hasLeft && !hasCenter &&  !hasRight) // Sensor right
        {
            hasLeft = true;
        }
        else if ((dis1 < maxDistanceObject) && (sta1 == 0) && hasLeft && !hasCenter && !hasRight) // Sensor center
        {
            hasCenter = true;
        }
        else if ((dis2 < maxDistanceObject) && (sta2 == 0) && hasLeft && hasCenter && !hasRight) // Sensor left
        {
            hasRight = true;
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
