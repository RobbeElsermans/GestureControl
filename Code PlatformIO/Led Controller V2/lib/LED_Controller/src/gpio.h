/**
 * @file gpio.h
 * @author Robbe Elsermans (robbe.elsermans@student.ap.be)
 * @brief High level gpio driver die huidige gebruik maakt van de HAL_Library
 * @version 1.0
 * @date 2022-05-20
 * 
 * This software is licensed under terms that can be found in the LICENSE file in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS and shared in the Public Domain
 * 
 */

#ifndef GPIO_H
#define GPIO_H

#include "stdint.h"
#include "stdbool.h"

/**
 * @brief De mogelijke input en output pinnen die we gebruiken in dit project
 * 
 */
typedef enum{
    led1,
    btn1,
     R1,
    R2,
    R3,
    R4,
    R5,
    R6,
    R7,
    C1,
    C2,
    C3,
    C4,
    C5,
} gpio_t;

/**
 * @brief De mogelijke statussen die de output pinnen kunnen hebben
 * 
 */
typedef enum{
    resetPin,
    setPin,
} state_t;

/**
 * @brief Initialisatie van de gpio pinnen met gebruik maken van de HAL_lib
 * 
 */
void gpio_initGpio();

/**
 * @brief Een gpio pin van state veranderen
 * 
 * @param gpio een enum van het typen gpio_t die een pin voorstelt
 * @param state een enum van het typen state_t die de status voorstelt
 */
void gpio_set_gpio(gpio_t gpio ,state_t state);

/**
 * @brief Een GPIO uitlezen van waarde
 * 
 * @param gpio een enum van het typen gpio_t die een pin voorstelt
 * @return state_t dat de status bevat van de gegeven gpio
 */
state_t gpio_get_gpio(gpio_t gpio);

#endif