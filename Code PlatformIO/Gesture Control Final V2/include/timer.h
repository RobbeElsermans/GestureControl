/**
 * @file timer.h
 * @author Robbe Elsermans (robbe.elsermans@student.ap.be)
 * @brief high level tijd functies die gebruik maken van de HAL_libraries
 * @version 1.0
 * @date 2022-05-20
 * 
 * This software is licensed under terms that can be found in the LICENSE file in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS and shared in the Public Domain
 * 
 */


#ifndef PROCESS_TIMER_H
#define PROCESS_TIMER_H

#include "stdint.h"
#include "stdbool.h"

/**
 * @brief Een block delay
 * 
 * @param time de tijd in milliseconden
 */
void timer_delay(int time);

/**
 * @brief De systeemtijd sinds opstart
 * 
 * @return long de tijd sinds opstart in milliseconden
 */
long timer_getTicks();

#endif