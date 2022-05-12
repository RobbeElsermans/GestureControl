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

#include "stm32f3xx_hal.h"
#include "stdbool.h" //Nodig om bool te kunnen gebruiken
#include "main.h"
#include "vl53l3cx.h"

/**
  * @brief  gets maximale afstand dat object mag zijn
  * @note   Standaard is dit 1000 millimeter
  * @retval Geen
  */
uint16_t get_maxDistanceObject();

/**
  * @brief  sets maximale afstand dat object mag zijn
  * @param  max pointer is de maximale afstand dat een object mag zijn om gedetecteerd te worden in millimeter
  * @note   Standaard is dit 1000 millimeter
  * @retval bool dat set is geslaagd of niet
  */
bool set_maxDistanceObject(uint16_t *max);

/**
  * @brief  gets de timer timeout wanneer een object als object wordt herkend 
  * @note   Standaard is dit 2000 milliseconden
  * @retval Geen
  */
uint16_t get_timerTimeout();

/**
  * @brief  sets de timer timeout wanneer een object als object wordt herkend 
  * @param  time pointer is de timeout tijd in milliseconden
  * @note   Standaard is dit 2000 milliseconden
  * @retval bool dat set is geslaagd of niet
  */
bool set_timerTimeout(uint16_t *time);

/**
  * @brief  gets maximaal aantal opslag voor voorgaande waardes
  * @note   Standaard is dit 10 plaatsen
  * @retval Geen
  */
uint16_t get_maxPrevDistances();

/**
  * @brief  sets maximaal aantal items voor de buffer
  * @param  max pointer is de maximale opslag capaciteit van de buffer
  * @note   Standaard is dit 10 plaatsen
  * @retval bool dat set is geslaagd of niet
  */
bool set_maxPrevDistances(uint16_t *max);

/**
  * @brief  Initialiseer Object Detect 
  * 
  * @param  _maxDistance pointer is de maximale afstand dat een object mag zijn om gedetecteerd te worden in millimeter. -1 is default (1000)
  * @param  _timerTimeout pointer is de timeout tijd in milliseconden. -1 is default (2000)
  * @param  _maxPrevDistances pointer is de maximale opslag capaciteit van de buffer. -1 is default (10)
  * @retval bool success Init
  */
bool initObjectPresent(int _maxDistance, int _timerTimeout, int _maxPrevDistances);

/**
  * @brief  Detecteerd een object
  * 
  * @param  Result pointer bevat de afstand van de desbetreffende sensor waarmee we 
  *         initiele metingen doen.
  * @param  WasObjectPresent pointer bevat een bool dat voorgaande ObjectPresent meegeeft
  * @param  dist pointer bevat een int waarde met de huidige afstand
  * @note   De maximale afstand dat een object mag hebben is de parameter maxDistanceObject.
  * @note   De tijd wanneer er een object gedetecteerd wordt is gedefinieerd in timerMeasurmentTimeout.
  * @retval bool ObjectPresent
  */
bool ckeckObjectPresent(Resultaat_t *Result, bool *WasObjectPresent, long *dist);
#endif