/**
 ******************************************************************************
 * @file          : GestureDetectLR.h
 * @author        : Robbe Elsermans
 * @brief         : Dit bestand bevat de methodes om een Links Rechts gesture te detecteren
 ******************************************************************************
 *
 * @attention
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#ifndef _GESTUREDETECTLRH
#define _GESTUREDETECTLR_H

#include "stm32f4xx_nucleo.h"
#include "stdbool.h" //Nodig om bool te kunnen gebruiken
#include "53l3a2_ranging_sensor.h"


/**
  * @brief  Detecteerd een hand dat van links naar rechts beweegt
  * 
  * @param  _gestureLR pointer bevat een bool dat voorgaande GestureLR bevat
  * @param  _object pointer bevat een bool dat voorgaande ObjectPresent meegeeft
  * @param  Result pointer bevat de afstand van de desbetreffende sensoren waarmee we 
  *         initiele metingen doen.
  * @note   De maximale afstand dat een object mag hebben is de parameter maxDistanceObject.
  * @note   De tijd wanneer er een object gedetecteerd wordt is gedefinieerd in timerMeasurmentTimeout.
  * @retval bool GestureLR
  */
bool CheckGestureLR(bool *_gestureLR, bool* _object,RANGING_SENSOR_Result_t *Result);

#endif