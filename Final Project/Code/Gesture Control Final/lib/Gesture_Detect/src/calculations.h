/**
 ******************************************************************************
 * @file          : calculations.h
 * @author        : Robbe Elsermans
 * @brief         : Dit bestand bevat de methodes voor het gemiddelde te berekenen.
 ******************************************************************************
 *
 * @attention
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
#ifndef CALCULATIONS_H
#define CALCULATIONS_H

#include "main.h"
#include "stdbool.h"

#define MAX_MEAN 2


/**
  * @brief  berekend het gemiddelde a.d.h.v. het gegeven id (sensor) en geeft dit terug
  * @param  id het id van de sensor
  * @note   Maakt gebruik van de static declaraties en mean values
  * @retval het gemiddelde in mm
  */
int calculations_getMean(uint8_t id);

/**
  * @brief  geeft de index terug van de counter van de gegeven id (sensor)
  * @param  id het id van de sensor
  * @note   Maakt gebruik van de static declaraties en mean values
  * @retval de counter 
  */
int calculations_getCountMean(uint8_t id);

/**
  * @brief  geeft een pointer terug waarin de opgeslagen raw afstanden staan in opgeslagen
  * @param  id het id van de sensor
  * @note   Maakt gebruik van de static declaraties en mean values
  * @retval de pointer naar de opgeslagen raw afstanden array
  */
int * calculations_getMeans(uint8_t id);

/**
  * @brief  Het opslaan van de raw afstands waardes
  * @param  sensor de pointer naar de sensor objecten
  * @note   Maakt gebruik van de static declaraties en mean values
  * @retval void
  */
void calculations_setMeanVal(sensorData_t* sensor);

/**
  * @brief  geeft het maximale aantal raw afstands opslag terug
  * @note   Maakt gebruik van de static declaraties en mean values
  * @retval Aantal opslag elementen
  */
int calculations_getMaxMean();
#endif