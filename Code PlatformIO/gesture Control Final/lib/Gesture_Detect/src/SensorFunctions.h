#ifndef SENSORFUNCTIONS_H
#define SENSORFUNCTIONS_H

#include "main.h"
#include "stdbool.h"
#include "vl53l3cx.h"
#include "custom_tof_conf.h"

/**
  * @brief  Zal nakijken of dat er een interrupt gegenereerd is
  * @param  sensor Een pointer naar het sensor object
  * @retval uint8_t isReady: Zal 1 retourneren bij een set en 0 bij een reset van de interrupt flag
  */
uint8_t sensorFunctions_sensorReady(sensorData_t* sensor);

/**
  * @brief  Configureerd de sensor bij de opstart van het programma
  * @param  sensor Een pointer naar het sensor object dat wordt geïnitialiseerd 
  * @note   mag maar 1x per sensor object aangeroepen worden
  * @retval void
  */
void sensorFunctions_initSensor(sensorData_t* sensor);

/**
  * @brief  Start de sensor op
  * @param  sensor Een pointer naar het sensor object
  * @retval void
  */
void sensorFunctions_startSensor(sensorData_t* sensor);

/**
  * @brief  stopt de sensor
  * @param  sensor Een pointer naar het sensor object 
  * @retval void
  */
void sensorFunctions_stopSensor(sensorData_t* sensor);

/**
  * @brief  Vraagt de data op en bewaard deze
  * @param  sensor Een pointer naar het sensor object
  * @retval void
  */
bool sensorFunctions_getData(sensorData_t* sensor);

#endif