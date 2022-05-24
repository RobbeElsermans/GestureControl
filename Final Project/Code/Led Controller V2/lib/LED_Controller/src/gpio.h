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
#include "globalDefines.h"

/**
 * @brief Initialisatie van de gpio pinnen met gebruik maken van de HAL_lib
 * 
 */
void gpio_initGpio();

/**
 * @brief stuurt de meegeleverde rij en kolom aan
 * 
 * @param gpio een struct van het typen gpio_matrix_t dat de rij en kolom bevat die aangestuurd moet worden
 * @param state de state van de desbetreffende rij en kolom
 */
void gpioMatrix_set_gpio_matrix(gpio_matrix_t *gpio, state_t state);

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