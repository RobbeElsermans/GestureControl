/**
 ******************************************************************************
 * @file          : GestureDetectObject.c
 * @author        : Robbe Elsermans
 * @brief         : Dit bestand bevat de methodes om een object te detecteren
 ******************************************************************************
 *
 * @attention
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include "GestureDetectObject.h"

// De maximale afstand dat een object kan staan om gedetecteerd te worden.
#define MAX_DISTANCE_OBJECT 1000            // Maximale afstand dat een object mag zijn om als object gedetecteerd te worden

// Timer om een object te herkennen
static float timerMeasurment = 0;           // opsalg van timer waarde
static bool timerMeasurementSet = false;    // de flag wanneer de timer gezet is
#define TIMER_MEASUREMENT_TIMEOUT 2000      // x seconden moet het object voor het toestel staan om gedetecteerd te worden

//static uint8_t x = 0; // DEBUG

// bool gestureDetectObject_ckeckObjectPresent(resultaat_t *Result, bool *WasObjectPresent, long dist)
// {
//     // De afstand en zone results ophalen uit Result
//     zone = Result->status;

//     if (((dist <= MAX_DISTANCE_OBJECT) && (zone <= 1 ||zone == 6) && !*WasObjectPresent))
//     {
//         if (!timerMeasurementSet)
//         {
//             timerMeasurementSet = true;
//             timerMeasurment = HAL_GetTick();
//         }

//         if (HAL_GetTick() - timerMeasurment >= TIMER_MEASUREMENT_TIMEOUT)
//         {
//             printf("Object! \r\n");
//             timerMeasurementSet = false;
//             return true;
//         }
//     }
//     else
//     {
//         if (timerMeasurementSet && !*WasObjectPresent)
//         {
//             timerMeasurementSet = false;
//         }
//     }

//     /*
//      *   als het object verder is dan MAX_DISTANCE_OBJECT en het object was er dan is het object weg
//      *   of als er een foutcode 12 of 4 is en de Objectresult is true, dan is het object weg.
//      */
//     //if (((dist >= MAX_DISTANCE_OBJECT) && *WasObjectPresent) || ((zone == 12 || zone == 4) && *WasObjectPresent) || (prevDistancesEqual && *WasObjectPresent))
//     if (((dist >= MAX_DISTANCE_OBJECT) && *WasObjectPresent) || ((zone == 12 || zone == 4) && *WasObjectPresent))
//     {
//         if (timerMeasurementSet == false)
//         {
//             timerMeasurementSet = true;
//             timerMeasurment = HAL_GetTick();
//         }

//         if ((HAL_GetTick() - timerMeasurment) >= TIMER_MEASUREMENT_TIMEOUT)
//         {
//             timerMeasurementSet = false;
//             return false;
//         }
//     }
//     else
//     {
//         if (timerMeasurementSet && *WasObjectPresent)
//         {
//             timerMeasurementSet = false;
//         }
//     }
//     return *WasObjectPresent;
// }

bool gestureDetectObject_ckeckObjectPresent(sensorData_t* sensor, bool *WasObjectPresent)
{
    // De afstand en zone results ophalen uit Result
    int8_t zone = sensor->resultaat.status;
    long dist = sensor->resultaat.meanDistance;
    //long dist = sensor->resultaat.meanDistance;

    if (((dist <= MAX_DISTANCE_OBJECT) && ((zone <= 1 && zone >=0) || zone == 6) && !*WasObjectPresent) && 
        dist != 0)
    {
        if (!timerMeasurementSet)
        {
            timerMeasurementSet = true;
            timerMeasurment = timer_getTicks();
        }

        if (timer_getTicks() - timerMeasurment >= TIMER_MEASUREMENT_TIMEOUT)
        {
            //printf("Object! \r\n");
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
     *   als het object verder is dan MAX_DISTANCE_OBJECT en het object was er dan is het object weg
     *   of als er een foutcode 12, 4 of 14 is en de Objectresult is true of de afstand is groter dan 5000, dan is het object weg.
     */
    //if (((dist >= MAX_DISTANCE_OBJECT) && *WasObjectPresent) || ((zone == 12 || zone == 4) && *WasObjectPresent) || (prevDistancesEqual && *WasObjectPresent))
    if ((((dist >= MAX_DISTANCE_OBJECT) && *WasObjectPresent) || ((zone == 12 || zone == 4 || zone == 14) && *WasObjectPresent)) || dist > 5000 || dist < 0)
    {
        if (timerMeasurementSet == false)
        {
            timerMeasurementSet = true;
            timerMeasurment = timer_getTicks();
        }

        if ((timer_getTicks() - timerMeasurment) >= TIMER_MEASUREMENT_TIMEOUT || dist > 5000)
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

uint16_t gestureDetectObject_getMaxDistanceObject()
{
    return MAX_DISTANCE_OBJECT;
}

uint16_t gestureDetectObject_getTimerTimeout()
{
    return TIMER_MEASUREMENT_TIMEOUT;
}