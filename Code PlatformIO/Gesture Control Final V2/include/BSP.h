/**
 * @file BSP.h
 * @author Robbe Elsermans (robbe.elsermans@student.ap.be)
 * @brief High level driver die een verzameling zal bevatten van de geschreven abstractie layers
 * @version 1.0
 * @date 2022-05-20
 * 
 * This software is licensed under terms that can be found in the LICENSE file in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS and shared in the Public Domain
 * 
 */

#ifndef BSP_H
#define BSP_H

#include "gpio.h"
#include "timer.h"
#include "i2c2.h"
#include "usart1.h"
#include "custom_bus.h" //Sensor I2C stuff

/**
 * @brief initialiseer alle peripherals 
 * 
 */
void BSP_initBSP();

#endif