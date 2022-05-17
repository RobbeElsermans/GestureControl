#ifndef CALIBRATIONDATA_H
#define CALIBRATIONDATA_H

#include "vl53lx_api.h"			   //Om calibration methodes te kunnen gebruiken
#include "main.h"
#include "stdbool.h"

/**
  * @brief  Het calibreren van de sensoren met een nieuwe setup
  * @param  dev de pointer naar het sensor object
  * @param  id de id van de sensor
  * @note   Zal de calibrate data over seriële communicatie plotten
  * @retval void
  */
void getCalibrate_oud(VL53L3CX_Object_t* dev, uint8_t id);
void getCalibrate(sensorData_t* sensor);

/**
  * @brief  Het calibreren van de sensoren met de opgeslagen setup
  * @param  dev de pointer naar het sensor object
  * @param  id de id van de sensor
  * @retval void
  */
void setCalibrate_oud(VL53L3CX_Object_t* dev, uint8_t id);
void setCalibrate(sensorData_t* sensor);

#endif