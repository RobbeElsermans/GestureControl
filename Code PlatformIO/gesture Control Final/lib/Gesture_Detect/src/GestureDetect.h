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

#define MAX_MEAN 2
#define MAX_DISTANCE 300
#define TIMER_MEASUREMENT_TIMEOUT 1500U


/**
  * @brief  Detecteert een gesture 
  * @param  sensoren de pointer naar de sensor objecten
  * @note   Maakt gebruik van de static declaraties en mean values
  * @retval het commando of -1 bij geen commando
  */
commands_t detectgesture(sensorData_t* sensoren);

/**
  * @brief  Bekijkt en (re)set de timer van de flags
  * @retval void
  */
void checkResetTimerGesture();

/**
  * @brief  berekend het gemiddelde a.d.h.v. het gegeven id (sensor) en geeft dit terug
  * @param  id het id van de sensor
  * @note   Maakt gebruik van de static declaraties en mean values
  * @retval het gemiddelde in mm
  */
int getMean(uint8_t id);

/**
  * @brief  geeft de index terug van de counter van de gegeven id (sensor)
  * @param  id het id van de sensor
  * @note   Maakt gebruik van de static declaraties en mean values
  * @retval de counter 
  */
int getCountMean(uint8_t id);

/**
  * @brief  geeft een pointer terug waarin de opgeslagen raw afstanden staan in opgeslagen
  * @param  id het id van de sensor
  * @note   Maakt gebruik van de static declaraties en mean values
  * @retval de pointer naar de opgeslagen raw afstanden array
  */
int * getMeans(uint8_t id);

/**
  * @brief  Het opslaan van de raw afstands waardes
  * @param  sensor de pointer naar de sensor objecten
  * @note   Maakt gebruik van de static declaraties en mean values
  * @retval void
  */
void setMeanVal(sensorData_t* sensor);

/**
  * @brief  geeft het maximale aantal raw afstands opslag terug
  * @note   Maakt gebruik van de static declaraties en mean values
  * @retval Aantal opslag elementen
  */
int getMaxMean();

/**
  * @brief  geeft het maximale afstand terug waarin een gesture gedetecteerd kan worden
  * @note   Maakt gebruik van de static declaraties en mean values
  * @retval maximale afstand in mm
  */
int getMaxDis();

#endif