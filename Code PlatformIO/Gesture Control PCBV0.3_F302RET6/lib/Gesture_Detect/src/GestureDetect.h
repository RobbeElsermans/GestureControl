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

#define maxMean 4
#define maxDistance 400

static int disMean[amountSensorUsed][maxMean];
static uint8_t disMeanindex[amountSensorUsed];

static bool LR_links = false;
static bool LR_rechts = false;
static bool LR_center = false;

static bool RL_links = false;
static bool RL_rechts = false;
static bool RL_center = false;

static bool DU_boven = false;
static bool DU_onder = false;
static bool DU_center = false;

static bool UD_boven = false;
static bool UD_onder = false;
static bool UD_center = false;

static float timerMeasurment = 0;
static bool timerMeasurementSet = false;
static int timerMeasurmentTimeout = 1200; // in milliseconden

commands detectgesture(int16_t left, int8_t leftStatus, int16_t center, int8_t centerStatus, int16_t right, int8_t rightStatus);
checkResetTimer();
int16_t getMean(uint8_t id);
int getCountMeans(uint8_t id);
int * getMeans(uint8_t id);
setMeanVal(uint8_t id, int16_t distance);
uint8_t getMaxMean();
uint8_t getMaxDis();

#endif