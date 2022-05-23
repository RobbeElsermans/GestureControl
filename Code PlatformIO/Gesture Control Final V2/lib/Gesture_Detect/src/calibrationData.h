#ifndef CALIBRATIONDATA_H
#define CALIBRATIONDATA_H

#include "vl53lx_api.h"			   //Om calibration methodes te kunnen gebruiken
#include "main.h"
#include "stdbool.h"

/**
  * @brief  Het kalibreren van de sensoren met een nieuwe setup en nadien plotten in terminal
  * @param  sensor de pointer naar het sensor object
  * @retval void
  */
void calibrationData_getCalibrate(sensorData_t* sensor);

/**
  * @brief  Het kalibreren van de sensoren met de opgeslagen setup
  * @param  static de pointer naar het sensor object
  * @retval void
  */
void calibrationData_setCalibrate(sensorData_t* sensor);

#endif