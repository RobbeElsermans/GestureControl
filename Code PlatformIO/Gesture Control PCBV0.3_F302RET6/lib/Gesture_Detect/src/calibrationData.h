#ifndef CALIBRATIONDATA_H
#define CALIBRATIONDATA_H

#include "vl53lx_api.h"			   //Om calibration methodes te kunnen gebruiken
#include "main.h"
#include "stdbool.h"



void RefSpadCal(VL53L3CX_Object_t* dev); 
void xTalkCal(VL53L3CX_Object_t* dev);
void offsetPerVcselCal(VL53L3CX_Object_t* dev, uint16_t distance);
VL53LX_CalibrationData_t getCalibrationData(VL53L3CX_Object_t* dev);
void setCalibrationData(VL53L3CX_Object_t* dev, sensorDev index, VL53LX_CalibrationData_t* data);
void setXTalkCompensation(VL53L3CX_Object_t* dev, bool state);
void setOffsetCorrectionMode(VL53L3CX_Object_t* dev, VL53LX_OffsetCorrectionModes state);
void convertCalibrationData(VL53LX_CalibrationData_t* data, int16_t* xtalk_bin_data, int16_t* xtalk_kcps,int16_t* xtalk_zero_distance,int16_t* offset);

#endif