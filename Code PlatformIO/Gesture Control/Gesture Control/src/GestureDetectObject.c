#include "GestureDetectObject.h"

static int maxDistanceObject = 1000;

static float timerMeasurment = 0;
static bool timerMeasurementSet = false;
static int timerMeasurmentTimeout = 2000; // 2 seconden


//Bug wanneer de sensor niets detecteerd maar de afstand blijft hetzelfde
static uint8_t max_prevDistances = 9;
static int prevDistances [10];
static uint8_t counter_prevDistances = 0;
static bool prevDistancesEqual = false;


uint8_t x = 0;

bool ckeckObjectPresent(RANGING_SENSOR_Result_t *Result, bool *WasObjectPresent)
{
    int dis1 = (long)Result[1].ZoneResult[0].Distance[0];
    uint8_t zone = (uint8_t)Result[VL53L3A2_DEV_CENTER].ZoneResult[0].Status[0];

    if(counter_prevDistances == max_prevDistances)
    counter_prevDistances = 0;

    //opslaan van data
    prevDistances[counter_prevDistances] = dis1;
    for (uint8_t i = 0; i <= max_prevDistances; i++)
    {
        if(i > 0)
        if(prevDistances[i] != prevDistances[i-1])
        {
            prevDistancesEqual = false;
            break;
        }

        //einde van de loop en nog steeds allemaal hetzelfde
        if(x == max_prevDistances)
            prevDistancesEqual = true;
    }

    if (x == 0)
    {
        printf("Zone result %1d: %2d \t", VL53L3A2_DEV_CENTER, (uint8_t)Result[VL53L3A2_DEV_CENTER].ZoneResult[0].Status[0]);
        printf("Dist result %1d: %2d \r\n", VL53L3A2_DEV_CENTER, dis1);
    }
    x++;

    /*	als dist1 onder de 1000 mm komt voor 3 seconden, dan is er een object.
     * 	+ er mag geen foutcode zijn
     */
    if (((dis1 <= maxDistanceObject) && zone == 0 && !*WasObjectPresent && !prevDistancesEqual))
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
        if (timerMeasurementSet && !*WasObjectPresent)
        {
            timerMeasurementSet = false;
        }
    }

    /*
     *   als het object verder is dan maxDistanceObject en het object was er dan is het object weg
     *   of als er een foutcode 12 of 4 is en de Objectresult is true, dan is het object weg.
     */
    if (((dis1 >= maxDistanceObject) && *WasObjectPresent) || ((zone == 12 || zone == 4) && *WasObjectPresent) || (prevDistancesEqual && *WasObjectPresent))
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
        if (timerMeasurementSet && *WasObjectPresent)
        {
            timerMeasurementSet = false;
        }
    }
    return *WasObjectPresent;
}