/**
 ******************************************************************************
 * @file          : GestureDetectDU.h
 * @author        : Robbe Elsermans
 * @brief         : Dit bestand bevat de methodes om een Onder Boven gesture te detecteren
 ******************************************************************************
 *
 * @attention
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#ifndef _GESTUREDETECTDU_H
#define _GESTUREDETECTDU_H

#include "stm32f3xx_hal.h"
#include "stdbool.h" //Nodig om bool te kunnen gebruiken
#include "main.h"
#include "vl53l3cx.h"


/**
  * @brief  Detecteerd een hand dat van onder naar boven beweegt
  * 
  * @param  _gestureDU pointer bevat een bool dat voorgaande GestureDU bevat
  * @param  _object pointer bevat een bool dat voorgaande ObjectPresent meegeeft
  * @param  Result pointer bevat de afstand van de desbetreffende sensoren waarmee we 
  *         initiele metingen doen.
  * @note   De maximale afstand dat een object mag hebben is de parameter maxDistanceObject.
  * @note   De tijd wanneer er een object gedetecteerd wordt is gedefinieerd in timerMeasurmentTimeout.
  * @retval bool GestureDU
  */
bool CheckGestureDU(bool *_gestureDU, bool* _object,VL53L3CX_Result_t *Result);

#endif