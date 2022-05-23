/**
 * @file gpioMatrix.h
 * @author Robbe Elsermans (robbe.elsermans@student.ap.be)
 * @brief functies om de led matrix aan te sturen
 * @version 1.0
 * @date 2022-05-20
 * 
 * This software is licensed under terms that can be found in the LICENSE file in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS and shared in the Public Domain
 * 
 */

#ifndef GPIO_MATRIX_H
#define GPIO_MATRIX_H

#include "globalDefines.h"

/**
 * @brief stuurt de meegeleverde rij en kolom aan
 * 
 * @param gpio een struct van het typen gpio_matrix_t dat de rij en kolom bevat die aangestuurd moet worden
 * @param state de state van de desbetreffende rij en kolom
 */
void gpioMatrix_set_gpio_matrix(gpio_matrix_t *gpio, state_t state);

#endif