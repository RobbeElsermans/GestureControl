#include "GestureDetect.h"

// variabelen die niet mogen veranderen na weg gaan van methodes

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
// static int TIMER_MEASUREMENT_TIMEOUT = 1200; // in milliseconden

long left = 0;
long right = 0;
long center = 0;
uint8_t leftStatus = 0;
uint8_t rightStatus = 0;
uint8_t centerStatus = 0;

void check_DU();
void check_UD();
void check_LR();
void check_RL();
commands_t check_Gesture();

commands_t gestureDetect_detectgesture(sensorData_t *sensoren)
{
  // long left = sensoren[LEFT].resultaat.distance;
  left = sensoren[LEFT].resultaat.meanDistance;
  // long right = sensoren[RIGHT].resultaat.distance;
  right = sensoren[RIGHT].resultaat.meanDistance;
  // long center = sensoren[CENTER].resultaat.distance;
  center = sensoren[CENTER].resultaat.meanDistance;
  leftStatus = sensoren[LEFT].resultaat.status;
  rightStatus = sensoren[RIGHT].resultaat.status;
  centerStatus = sensoren[CENTER].resultaat.status;

  check_DU();
  check_UD();
  check_LR();
  check_RL();
  return check_Gesture();
}

void gestureDetect_checkResetTimerGesture()
{
  // reset gesture flags
  if (!timerMeasurementSet)
  {
    timerMeasurementSet = true;
    timerMeasurment = timer_getTicks();
  }
  long temp = timer_getTicks();
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
int gestureDetect_getMaxDis()
{
  return MAX_DISTANCE;
}

void check_DU()
{
  // DU gesture
  if (left < MAX_DISTANCE && leftStatus == 0 && 
  !DU_center && !DU_boven && 
  center > MAX_DISTANCE && right > MAX_DISTANCE)
    DU_onder = true;

  if (right < MAX_DISTANCE && rightStatus == 0 && 
  !DU_center && DU_onder && 
  center > MAX_DISTANCE)
    DU_center = true;

  if (center < MAX_DISTANCE && centerStatus == 0 && 
  DU_center && DU_onder)
    DU_boven = true;
}

void check_UD()
{
  // UD gesture
  if (center < MAX_DISTANCE && centerStatus == 0 && 
      !UD_center && !UD_onder && 
      left > MAX_DISTANCE && right > MAX_DISTANCE)
    UD_boven = true;

  if (right < MAX_DISTANCE && rightStatus == 0 && 
  !UD_onder && UD_boven && 
  left > MAX_DISTANCE)
    UD_center = true;

  if (left < MAX_DISTANCE && leftStatus == 0 && 
  UD_center && UD_boven)
    UD_onder = true;
}

void check_LR()
{
  // LR gesture
  if (left < MAX_DISTANCE && leftStatus == 0 &&
      !LR_center && !LR_rechts &&
      center > MAX_DISTANCE && right > MAX_DISTANCE)
    LR_links = true;

  if (center < MAX_DISTANCE && centerStatus == 0 && 
      !LR_rechts && LR_links && 
      right > MAX_DISTANCE)
    LR_center = true;

  if (right < MAX_DISTANCE && rightStatus == 0 && 
      LR_center && LR_links)
    LR_rechts = true;
}

void check_RL()
{
  // RL gesture
  if (right < MAX_DISTANCE && rightStatus == 0 &&
      !RL_center && !RL_links &&
      center > MAX_DISTANCE && left > MAX_DISTANCE)
    RL_rechts = true;

  if (center < MAX_DISTANCE && centerStatus == 0 &&
      !RL_links && RL_rechts &&
      left > MAX_DISTANCE)
    RL_center = true;

  if (left < MAX_DISTANCE && leftStatus == 0 &&
      RL_center && RL_rechts)
    RL_links = true;
}

commands_t check_Gesture()
{
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