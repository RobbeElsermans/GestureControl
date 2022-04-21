/**
 ******************************************************************************
 * @file          : GestureDetectRL.h
 * @author        : Robbe Elsermans
 * @brief         : Dit bestand bevat de methodes om een Rechts Links gesture te detecteren
 ******************************************************************************
 *
 * @attention
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#ifndef _GESTUREDETECTRL_H
#define _GESTUREDETECTRL_H

#include "stm32f3xx_hal.h"
#include "stdbool.h" //Nodig om bool te kunnen gebruiken
#include "main.h"
#include "vl53l3cx.h"

/**
  * @brief  Detecteerd een hand dat van rechts naar links beweegt
  * 
  * @param  _gestureRL pointer bevat een bool dat voorgaande GestureRL bevat
  * @param  _object pointer bevat een bool dat voorgaande ObjectPresent meegeeft
  * @param  Result pointer bevat de afstand van de desbetreffende sensoren waarmee we 
  *         initiele metingen doen.
  * @note   De maximale afstand dat een object mag hebben is de parameter maxDistanceObject.
  * @note   De tijd wanneer er een object gedetecteerd wordt is gedefinieerd in timerMeasurmentTimeout.
  * @retval bool GestureRL
  */
bool CheckGestureRL(bool *_gestureRL, bool* _object,Resultaat_t *Result);

#endif