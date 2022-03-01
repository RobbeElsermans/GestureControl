#ifndef _GESTUREDETECTOBJECT_H
#define _GESTUREDETECTOBJECT_H

#include "stm32f4xx_nucleo.h"
#include "stdbool.h" //Nodig om bool te kunnen gebruiken
#include "53l3a2_ranging_sensor.h"

bool objectPresent(RANGING_SENSOR_Result_t Result[], bool WasObjectPresent);
#endif