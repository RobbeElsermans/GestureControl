/**
 ******************************************************************************
 * @file          : GestureDetect.h
 * @author        : Robbe Elsermans
 * @brief         : Dit bestand bevat de methodes om een gesture te detecteren
 ******************************************************************************
 *
 * @attention
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#ifndef GESTUREDETECT_H
#define GESTUREDETECT_H

#include "main.h"
#include "stdbool.h"


#define MAX_DISTANCE 300
#define TIMER_MEASUREMENT_TIMEOUT 1500U

/**
  * @brief  Detecteert een gesture 
  * @param  sensoren de pointer naar de sensor objecten
  * @note   Maakt gebruik van de static declaraties en mean values
  * @retval het commando of -1 bij geen commando
  */
commands_t gestureDetect_detectgesture(sensorData_t* sensoren);

/**
  * @brief  Bekijkt en (re)set de timer van de flags
  * @retval void
  */
void gestureDetect_checkResetTimerGesture();

/**
  * @brief  geeft het maximale afstand terug waarin een gesture gedetecteerd kan worden
  * @note   Maakt gebruik van de static declaraties en mean values
  * @retval maximale afstand in mm
  */
int gestureDetect_getMaxDis();


#endif