/**
 ******************************************************************************
 * @file          : GestureDetect.h
 * @author        : Robbe Elsermans
 * @brief         : Dit bestand bevat de methodes om een gesture te detecteren
 ******************************************************************************
 *
 * @attention
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#ifndef GESTUREDETECT_H
#define GESTUREDETECT_H

#include "main.h"
#include "stdbool.h"

#define maxMean 6
#define maxDistance 300

commands detectgesture(int16_t left, int8_t leftStatus, int16_t center, int8_t centerStatus, int16_t right, int8_t rightStatus);
void checkResetTimer();
int16_t getMean(uint8_t id);
int getCountMeans(uint8_t id);
int * getMeans(uint8_t id);
void setMeanVal(uint8_t id, int16_t distance);
uint8_t getMaxMean();
uint8_t getMaxDis();

#endif