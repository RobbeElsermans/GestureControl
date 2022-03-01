#ifndef _GESTUREDETECTOBJECT_H
#define _GESTUREDETECTOBJECT_H

#include "stm32f4xx_nucleo.h"
#include "stdbool.h" //Nodig om bool te kunnen gebruiken
#include "53l3a2_ranging_sensor.h"

/**
  * @brief  Detecteerd een object
  * 
  * @param  Result pointer bevat de afstand van de desbetreffende sensor waarmee we 
  *         initiele metingen doen.
  * @param  WasObjectPresent pointer bevat een bool dat voorgaande ObjectPresent meegeeft
  * @note   De maximale afstand dat een object mag hebben is de parameter maxDistanceObject.
  * @note   De tijd wanneer er een object gedetecteerd wordt is gedefinieerd in timerMeasurmentTimeout.
  * @retval bool ObjectPresent
  */
bool ckeckObjectPresent(RANGING_SENSOR_Result_t Result[], bool *WasObjectPresent);
#endif