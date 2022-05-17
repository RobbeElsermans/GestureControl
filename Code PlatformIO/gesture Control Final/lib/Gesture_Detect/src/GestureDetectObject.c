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
#include "vl53l3cx.h"

// De maximale afstand dat een object kan staan om gedetecteerd te worden.
static int maxDistanceObject = 1000;           // Maximale afstand dat een object mag zijn om als object gedetecteerd te worden

// Timer om een object te herkennen
static float timerMeasurment = 0;           // opsalg van timer waarde
static bool timerMeasurementSet = false;    // de flag wanneer de timer gezet is
static int timerMeasurmentTimeout = 2000;      // x seconden moet het object voor het toestel staan om gedetecteerd te worden

//static uint8_t x = 0; // DEBUG

static uint8_t zone = 0;

bool ckeckObjectPresent(resultaat_t *Result, bool *WasObjectPresent, long *dist)
{
    // De afstand en zone results ophalen uit Result
    zone = Result->status;

    if (((*dist <= maxDistanceObject) && (zone <= 1 ||zone == 6) && !*WasObjectPresent))
    {
        if (!timerMeasurementSet)
        {
            timerMeasurementSet = true;
            timerMeasurment = HAL_GetTick();
        }

        if (HAL_GetTick() - timerMeasurment >= timerMeasurmentTimeout)
        {
            printf("Object! \r\n");
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
    //if (((*dist >= maxDistanceObject) && *WasObjectPresent) || ((zone == 12 || zone == 4) && *WasObjectPresent) || (prevDistancesEqual && *WasObjectPresent))
    if (((*dist >= maxDistanceObject) && *WasObjectPresent) || ((zone == 12 || zone == 4) && *WasObjectPresent))
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

uint16_t get_maxDistanceObject()
{
    return maxDistanceObject;
}
bool set_maxDistanceObject(uint16_t *max)
{
    if (*max != 0)
        maxDistanceObject = *max;
    else
        return false;
    return true;
}

uint16_t get_timerTimeout()
{
    return timerMeasurmentTimeout;
}

bool set_timerTimeout(uint16_t *time)
{
    if (*time != 0)
        timerMeasurmentTimeout = *time;
    else
        return false;
    return true;
}