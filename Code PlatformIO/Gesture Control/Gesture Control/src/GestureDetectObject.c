#include "GestureDetectObject.h"

//De maximale afstand dat een object kan staan om gedetecteerd te worden.
static int maxDistanceObject = 1000;

//Timer om een object te herkennen
static float timerMeasurment = 0;           // opsalg van timer waarde
static bool timerMeasurementSet = false;    // de flag wanneer de timer gezet is
static int timerMeasurmentTimeout = 2000;   // 2 seconden moet het object voor het toestel staan


//Bug wanneer de sensor niets detecteerd maar de afstand blijft hetzelfde en er zij geen foutcodes aanwezig (zone == 0)
static uint8_t max_prevDistances = 9;       // 10 metingen opslaan
static int prevDistances [10];              // opslag buffer
static uint8_t counter_prevDistances = 0;   // counter om de buffer te vullen
static bool prevDistancesEqual = false;     // Een flag die zegt dat de buffer bestaat uit gelijke waardes


uint8_t x = 0;  //DEBUG

int dist1 = 0;
uint8_t zone = 0;

bool ckeckObjectPresent(RANGING_SENSOR_Result_t *Result, bool *WasObjectPresent)
{
    //De afstand en zone results ophalen uite Result
    dist1 = (long)Result[1].ZoneResult[0].Distance[0];
    zone = (uint8_t)Result[VL53L3A2_DEV_CENTER].ZoneResult[0].Status[0];

    if(counter_prevDistances == max_prevDistances)
    counter_prevDistances = 0;

    //opslaan van data
    prevDistances[counter_prevDistances] = dist1;
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
        printf("Zone result %1d: %2d \t", VL53L3A2_DEV_CENTER, zone);
        printf("Dist result %1d: %2d \r\n", VL53L3A2_DEV_CENTER, dist1);
    }
    x++;

    /*	als dist1 onder de 1000 mm komt voor 3 seconden, dan is er een object.
     * 	+ er mag geen foutcode zijn
     */
    if (((dist1 <= maxDistanceObject) && zone == 0 && !*WasObjectPresent && !prevDistancesEqual))
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
    if (((dist1 >= maxDistanceObject) && *WasObjectPresent) || ((zone == 12 || zone == 4) && *WasObjectPresent) || (prevDistancesEqual && *WasObjectPresent))
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