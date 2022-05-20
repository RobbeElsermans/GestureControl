/**
 * @file position.h
 * @author Robbe Elsermans (robbe.elsermans@student.ap.be)
 * @brief functies (soort van classen) om de positie te onderhouden
 * @version 1.0
 * @date 2022-05-20
 * 
 * This software is licensed under terms that can be found in the LICENSE file in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS and shared in the Public Domain
 * 
 */

#ifndef POSITION_H
#define POSITION_H


#include "stdint.h"
#include "stdbool.h"

#include "gpioMatrix.h"
#include "timer.h"

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

/**
 * @brief Initialiseren van de struct position_t
 * 
 * @param _pos het te initialiseren struct van het typen position_t
 */
void position_initPosition(position_t *_pos);

/**
 * @brief Aanzetten van een matrix
 * 
 * @param _pos het aan te zetten struct object
 */
void position_turnOn(position_t *_pos);

/**
 * @brief Uitzetten van een matrix
 * 
 * @param _pos het uit te zetten struct object
 */
void position_turnOff(position_t *_pos);

/**
 * @brief De positie op de matrix updaten aan de hand van de gegeven position_t struct
 * 
 * @param _pos het te updaten struct object
 */
void position_processPosition(position_t *_pos);

// void processPosition_set_position(position_t *_pos);

/**
 * @brief De dot een rij lager laten bewegen
 * 
 * @param _pos het te updaten struct object
 */
void position_rowDown(position_t *_pos);

/**
 * @brief De dot een rij hoger laten bewegen
 * 
 * @param _pos het te updaten struct object
 */
void position_rowUp(position_t *_pos);

/**
 * @brief De dot een kolom naar rechts laten bewegen
 * 
 * @param _pos het te updaten struct object
 */
void position_columnRight(position_t *_pos);

/**
 * @brief De dot een kolom naar links laten bewegen
 * 
 * @param _pos het te updaten struct object
 */
void position_columnLeft(position_t *_pos);

#endif