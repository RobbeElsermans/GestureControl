/**
 * @file globalDefines.h
 * @author Robbe Elsermans (robbe.elsermans@student.ap.be)
 * @brief Dit bestand bevat globaal gebruikte structs en enums
 * @version 1.0
 * @date 2022-05-20
 * 
 * This software is licensed under terms that can be found in the LICENSE file in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS and shared in the Public Domain
 * 
 */

#ifndef GLOBAL_DEFINES_H
#define GLOBAL_DEFINES_H


#include "stdint.h"
#include "stdbool.h"

/**
 * @brief De commando's die de Gesture Controller kan versturen
 * 
 */
typedef enum
{
    RL = 0x22,
    LR = 0x21,
    UD = 0x23,
    DU = 0x24,
    OBJ = 0x20,
    NONE = 0x10
} command_t;

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
 * @brief Een struct dat de rijen en kolommen bevat van de matrix
 * 
 */
typedef struct{
gpio_t column;
gpio_t row;
}gpio_matrix_t;

/**
 * @brief De maximale kolom breedte van de gebruikte matrix
 * 
 */
#define MAX_X_POS 5

/**
 * @brief De maximale rij hoogte van de gebruikte matrix
 * 
 */
#define MAX_Y_POS 7

/**
 * @brief Struct die de positie onderhoud van de matrix dot met een status flag erbij
 * 
 */
typedef struct{
    int8_t x;
    int8_t y;
    bool state;
} position_t;

#endif