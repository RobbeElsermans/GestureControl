#include "GestureDetect.h"

int16_t tempMean = 0;

bool checkIndex(uint8_t id);

commands detectgesture(int16_t left, int8_t leftStatus, int16_t center, int8_t centerStatus, int16_t right, int8_t rightStatus)
{
    // DU gesture
      if (left < maxDistance && leftStatus == 0 && !DU_center && !DU_boven && center > maxDistance && right > maxDistance)
      {
        DU_onder = true;
      }

      if (right < maxDistance && rightStatus == 0 && !DU_center && DU_onder && center > maxDistance)
      {
        DU_center = true;
      }

      if (center < maxDistance && centerStatus == 0 && DU_center && DU_onder)
      {
        DU_boven = true;
      }

      // UD gesture
      if (center < maxDistance && centerStatus == 0 && !UD_center && !UD_onder && left > maxDistance && right > maxDistance)
      {
        UD_boven = true;
      }

      if (right < maxDistance && rightStatus == 0 && !UD_onder && UD_boven && left > maxDistance)
      {
        UD_center = true;
      }

      if (left < maxDistance && leftStatus == 0 && UD_center && UD_boven)
      {
        UD_onder = true;
      }

      // LR gesture
      if (left < maxDistance && leftStatus == 0 && !LR_center && !LR_rechts && center > maxDistance && right > maxDistance)
      {
        LR_links = true;
      }

      if (center < maxDistance && centerStatus == 0 && !LR_rechts && LR_links && right > maxDistance)
      {
        LR_center = true;
      }

      if (right < maxDistance && rightStatus == 0 && LR_center && LR_links)
      {
        LR_rechts = true;
      }

      // RL gesture
      if (right < maxDistance && rightStatus == 0 && !RL_center && !RL_links && center > maxDistance && left > maxDistance)
      {
        RL_rechts = true;
      }

      if (center < maxDistance && centerStatus == 0 && !RL_links && RL_rechts && left > maxDistance)
      {
        RL_center = true;
      }

      if (left < maxDistance && leftStatus == 0 && RL_center && RL_rechts)
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
}

checkResetTimer(){
      // reset gesture flags
    if (!timerMeasurementSet)
    {
      timerMeasurementSet = true;
      timerMeasurment = HAL_GetTick();
    }
    long temp = HAL_GetTick();
    if (timerMeasurementSet && (temp - timerMeasurment) > timerMeasurmentTimeout)
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

int16_t getMean(uint8_t id)
{
    tempMean = 0;
    for (size_t i = 0; i < maxMean; i++)
    {
        tempMean += disMean[id][i];
    }
    tempMean /= maxMean;
    return tempMean;
}
int getCountMeans(uint8_t id)
{
    return disMeanindex[id];
}
int *getMeans(uint8_t id)
{
    return disMean[id];
}
setMeanVal(uint8_t id, int16_t distance)
{
    disMean[id][disMeanindex[id]] = distance;
    checkIndex(id);
}
uint8_t getMaxMean()
{
    return maxMean;
}
uint8_t getMaxDis()
{
    return maxDistance;
}
bool checkIndex(uint8_t id){
    if (disMeanindex[id] < maxMean - 1)
        disMeanindex[id]++;
    else
        disMeanindex[id] = 0;
}