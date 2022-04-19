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
static bool hasTop = false;
static bool hasCenter = false;
static bool hasBottom = false;

static int maxDistanceObject = 300;
static float timerMeasurment = 0;
static bool timerMeasurementSet = false;
static int timerMeasurmentTimeout = 1200; // 1 seconden

bool CheckGestureDU(bool *_gestureDU, bool *_object, VL53L3CX_Result_t *Result)
{
    // Detecteren commando van Onder naar boven
    // Eerst moet sensor onder (4) minder binnen krijgen
    // Dan sensor center (1)
    // Als laatste sensor boven (3)
    if (*_object)
    {
        uint8_t sta3 = (uint8_t)Result[TOP].ZoneResult[0].Status[0];
        uint8_t sta1 = (uint8_t)Result[CENTER].ZoneResult[0].Status[0];
        uint8_t sta4 = (uint8_t)Result[BOTTOM].ZoneResult[0].Status[0];
        int dis3 = (int)Result[TOP].ZoneResult[0].Distance[0];
        int dis1 = (int)Result[CENTER].ZoneResult[0].Distance[0];
        int dis4 = (int)Result[BOTTOM].ZoneResult[0].Distance[0];

        if ((dis4 < maxDistanceObject) && (dis3 > maxDistanceObject) && (sta4 == 0) && !hasBottom && !hasCenter &&  !hasTop && dis4 != 0) // Sensor bottom
        {
            hasBottom = true;
            //printf("Bottom \r\n");
        }
        else if ((dis1 < maxDistanceObject) && (sta1 == 0) && hasBottom && !hasCenter && !hasTop && dis1 != 0) // Sensor center
        {
            hasCenter = true;
            //printf("center \r\n");
        }
        else if ((dis3 < maxDistanceObject) && (sta3 == 0) && hasBottom && hasCenter && !hasTop && dis3 != 0) // Sensor top
        {
            hasTop = true;
            //printf("Top \r\n");
        }

        //printf("TOP %2d, center %2d, BOTTOM %2d \r\n", hasTop, hasCenter, hasBottom);
    }

    // Een timeout timer plaatsen
    if (timerMeasurementSet == false && (hasBottom || hasCenter || hasTop))
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
            hasTop = false;
            hasCenter = false;
        }

    if(hasBottom && hasCenter && hasTop)
    return true;
    else
    return false;
}
