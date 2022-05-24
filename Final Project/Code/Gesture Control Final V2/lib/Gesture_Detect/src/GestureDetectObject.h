/**
 ******************************************************************************
 * @file          : GestureDetectObject.h
 * @author        : Robbe Elsermans
 * @brief         : Dit bestand bevat de methodes om een object te detecteren
 ******************************************************************************
 *
 * @attention
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#ifndef _GESTUREDETECTOBJECT_H
#define _GESTUREDETECTOBJECT_H

#include "main.h"

/**
  * @brief  gets maximale afstand dat object mag zijn
  * @note   Standaard is dit 1000 millimeter
  * @retval Geen
  */
uint16_t gestureDetectObject_getMaxDistanceObject();

/**
  * @brief  gets de timer timeout wanneer een object als object wordt herkend 
  * @note   Standaard is dit 2000 milliseconden
  * @retval Geen
  */
uint16_t gestureDetectObject_getTimerTimeout();

/**
  * @brief  Detecteerd een object
  * 
  * @param  Result pointer bevat de afstand van de desbetreffende sensor waarmee we 
  *         initiele metingen doen.
  * @param  WasObjectPresent pointer bevat een bool dat voorgaande ObjectPresent meegeeft
  * @param  dist pointer bevat een int waarde met de huidige afstand
  * @note   De maximale afstand dat een object mag hebben is de parameter MAX_DISTANCE_OBJECT.
  * @note   De tijd wanneer er een object gedetecteerd wordt is gedefinieerd in TIMER_MEASUREMENT_TIMEOUT.
  * @retval bool ObjectPresent
  */
bool gestureDetectObject_ckeckObjectPresent(sensorData_t* sensor, bool *WasObjectPresent);
#endif