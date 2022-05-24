/**
 * @file command.h
 * @author Robbe Elsermans (robbe.elsermans@student.ap.be)
 * @brief Dit bestand bevat command functies
 * @version 1.0
 * @date 2022-05-20
 * 
 * This software is licensed under terms that can be found in the LICENSE file in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS and shared in the Public Domain
 * 
 */

#ifndef COMMAND_H
#define COMMAND_H

#include "stdint.h"
#include "stdbool.h"
#include "globalDefines.h"
#include "position.h"

/**
 * @brief Initialiseer commando functie
 * 
 * @param _command dat van het typen command_t* is
 */
void command_initCommand(command_t *_command);

/**
 * @brief Het commando verwerken en hierop een actie uitvoeren
 * 
 * @param _command dat van het typen command_t* is
 * @param _pos een geïnitialiseerd struct object van het type position_t*
 */
void command_processCommand(command_t *_command, position_t *_pos);

#endif