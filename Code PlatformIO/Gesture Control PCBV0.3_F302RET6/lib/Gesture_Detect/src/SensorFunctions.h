#ifndef SENSORFUNCTIONS_H
#define SENSORFUNCTIONS_H

#include "main.h"
#include "stdbool.h"
#include "vl53l3cx.h"
#include "custom_tof_conf.h"

/**
  * @brief  Zal nakijken of dat er een interrupt gegenereerd is
  * @param  sensor Een pointer naar het sensor object dat wordt geïnitialiseerd 
  * @param  index De XSHUT & GPIO pin waarop de sensor staat aangesloten
  * @param  isReady Een pointer value dat de waardes van de interrupt flags bevat
  * @retval Zal 1 retourneren bij een set en 0 bij een reset van de interrupt flag
  */
uint8_t Sensor_Ready(VL53L3CX_Object_t *sensor, sensorDev index, uint8_t *isReady);

/**
  * @brief  Configureerd de sensor bij de opstart van het programma
  * @param  sensor Een pointer naar het sensor object dat wordt geïnitialiseerd 
  * @param  index De XSHUT & GPIO pin waarop de sensor staat aangesloten
  * @param  address Een pointer value dat de waarde van het nieuwe adres bij zicht heeft
  * @note   mag maar 1x per sensor object aangeroepen worden
  * @retval void
  */
void Init_Sensor(VL53L3CX_Object_t *sensor, sensorDev index);

/**
  * @brief  Start de sensor op
  * @param  sensor Een pointer naar het sensor object dat wordt geïnitialiseerd 
  * @param  index De XSHUT & GPIO pin waarop de sensor staat aangesloten
  * @note   mag maar 1x per sensor object aangeroepen worden
  * @retval void
  */
void Start_Sensor(VL53L3CX_Object_t *sensor, sensorDev index);

/**
  * @brief  stopt de sensor
  * @param  sensor Een pointer naar het sensor object dat wordt geïnitialiseerd 
  * @note   mag maar 1x per sensor object aangeroepen worden
  * @retval void
  */
void Stop_Sensor(VL53L3CX_Object_t *sensor);

#endif