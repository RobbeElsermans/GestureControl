#include "GestureDetect.h"

//variabelen die niet mogen veranderen na weg gaan van methodes
static int disMean[AMOUNT_SENSOR_USED][MAX_MEAN];
static uint8_t disMeanindex[AMOUNT_SENSOR_USED];

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
// static int timerMeasurmentTimeout = 1200; // in milliseconden

int16_t tempMean = 0;

void checkIndex(uint8_t id);

commands_t detectgesture(sensorData_t* sensoren)
{
  //long left = sensoren[LEFT].resultaat.distance;
  long left = sensoren[LEFT].resultaat.meanDistance;
  //long right = sensoren[RIGHT].resultaat.distance;
  long right = sensoren[RIGHT].resultaat.meanDistance;
  //long center = sensoren[CENTER].resultaat.distance;
  long center = sensoren[CENTER].resultaat.meanDistance;
  uint8_t leftStatus = sensoren[LEFT].resultaat.status;
  uint8_t rightStatus = sensoren[RIGHT].resultaat.status;
  uint8_t centerStatus = sensoren[CENTER].resultaat.status;

    // DU gesture
      if (left < MAX_DISTANCE && (leftStatus == 0 || leftStatus == 7) && !DU_center && !DU_boven && center > MAX_DISTANCE && right > MAX_DISTANCE)
      {
        DU_onder = true;
      }

      if (right < MAX_DISTANCE && (rightStatus == 0 || rightStatus == 7) && !DU_center && DU_onder && center > MAX_DISTANCE)
      {
        DU_center = true;
      }

      if (center < MAX_DISTANCE && (centerStatus == 0 || centerStatus == 7) && DU_center && DU_onder)
      {
        DU_boven = true;
      }

      // UD gesture
      if (center < MAX_DISTANCE && centerStatus == 0 && !UD_center && !UD_onder && left > MAX_DISTANCE && right > MAX_DISTANCE)
      {
        UD_boven = true;
      }

      if (right < MAX_DISTANCE && rightStatus == 0 && !UD_onder && UD_boven && left > MAX_DISTANCE)
      {
        UD_center = true;
      }

      if (left < MAX_DISTANCE && leftStatus == 0 && UD_center && UD_boven)
      {
        UD_onder = true;
      }

      // LR gesture
      if (left < MAX_DISTANCE && leftStatus == 0 && !LR_center && !LR_rechts && center > MAX_DISTANCE && right > MAX_DISTANCE)
      {
        LR_links = true;
      }

      if (center < MAX_DISTANCE && centerStatus == 0 && !LR_rechts && LR_links && right > MAX_DISTANCE)
      {
        LR_center = true;
      }

      if (right < MAX_DISTANCE && rightStatus == 0 && LR_center && LR_links)
      {
        LR_rechts = true;
      }

      // RL gesture
      if (right < MAX_DISTANCE && rightStatus == 0 && !RL_center && !RL_links && center > MAX_DISTANCE && left > MAX_DISTANCE)
      {
        RL_rechts = true;
      }

      if (center < MAX_DISTANCE && centerStatus == 0 && !RL_links && RL_rechts && left > MAX_DISTANCE)
      {
        RL_center = true;
      }

      if (left < MAX_DISTANCE && leftStatus == 0 && RL_center && RL_rechts)
      {
        RL_links = true;
      }

      if (DU_boven && DU_center && DU_onder)
      {
        return DU;
      }

      if (UD_boven && UD_center && UD_onder)
      {
        return UD;
      }

      if (LR_links && LR_center && LR_rechts)
      {
        return LR;
      }

      if (RL_links && RL_center && RL_rechts)
      {
        return RL;
      }
      return -1;
}

void checkResetTimerGesture()
{
      // reset gesture flags
    if (!timerMeasurementSet)
    {
      timerMeasurementSet = true;
      timerMeasurment = HAL_GetTick();
    }
    long temp = HAL_GetTick();
    if (timerMeasurementSet && (temp - timerMeasurment) > TIMER_MEASUREMENT_TIMEOUT)
    {
      timerMeasurementSet = false;
      DU_boven = false;
      DU_center = false;
      DU_onder = false;
      UD_boven = false;
      UD_center = false;
      UD_onder = false;
      LR_links = false;
      LR_rechts = false;
      LR_center = false;
      RL_links = false;
      RL_rechts = false;
      RL_center = false;
    }
}

int getMean(uint8_t id)
{
    tempMean = 0;
    for (size_t i = 0; i < MAX_MEAN; i++)
    {
        tempMean += disMean[id][i];
    }
    tempMean /= MAX_MEAN;
    return tempMean;
}
int getCountMean(uint8_t id)
{
    return disMeanindex[id];
}
int *getMeans(uint8_t id)
{
    return disMean[id];
}
void setMeanVal(sensorData_t* sensor)
{
    disMean[sensor->id][disMeanindex[sensor->id]] = sensor->resultaat.distance;
    checkIndex(sensor->id);
}
int getMaxMean()
{
    return MAX_MEAN;
}
int getMaxDis()
{
    return MAX_DISTANCE;
}
void checkIndex(uint8_t id){
    if (disMeanindex[id] < MAX_MEAN - 1)
        disMeanindex[id]++;
    else
        disMeanindex[id] = 0;
}