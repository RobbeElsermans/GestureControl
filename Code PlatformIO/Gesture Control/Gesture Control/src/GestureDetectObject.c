#include "GestureDetectObject.h"

static int threshold = 1000;
static int minDistanceObject = 300;
static int maxDistanceObject = 1000;

static float timerMeasurment = 0;
static bool timerMeasurementSet = false;
static int timerMeasurmentTimeout = 2000; // 2 seconden

bool objectPresent(RANGING_SENSOR_Result_t *Result, bool WasObjectPresent)
{
    
    int dis1 = (long)Result[1].ZoneResult[0].Distance[0];

    /*	als dist1 onder de 1000 mm komt voor 3 seconden, dan is er een object.
     * 	+ er mag geen foutcode 12 zijn
     */
    if ((dis1 <= maxDistanceObject) && (uint8_t)Result[VL53L3A2_DEV_CENTER].ZoneResult[0].Status[0] == 0 && !WasObjectPresent)
    {
        if (!timerMeasurementSet)
        {
            timerMeasurementSet = true;
            timerMeasurment = HAL_GetTick();
        }
        if ((HAL_GetTick() - timerMeasurment) >= timerMeasurmentTimeout)
        {
            timerMeasurementSet = false;
            return true;
        }
    }
    else
    {
        if (timerMeasurementSet && !WasObjectPresent)
        {
            timerMeasurementSet = false;
        }
    }

    if ((dis1 >= maxDistanceObject) && WasObjectPresent)
    {
        if (timerMeasurementSet == false)
        {
            timerMeasurementSet = true;
            timerMeasurment = HAL_GetTick();
        }

        if ((HAL_GetTick() - timerMeasurment) >= timerMeasurmentTimeout)
        {
            timerMeasurementSet = false;
            return false;
        }
    }
    else
    {
        if (timerMeasurementSet && WasObjectPresent)
        {
            timerMeasurementSet = false;
        }
    }
    return WasObjectPresent;
}