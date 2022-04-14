#ifndef CALIBRATIONDATA_H
#define CALIBRATIONDATA_H

#include "vl53lx_api.h"			   //Om calibration methodes te kunnen gebruiken

#include "main.h"



void RefSpadCal(uint8_t dev); 
void xTalkCal(uint8_t dev);
void offsetPerVcselCal(uint8_t dev, uint16_t distance);
VL53LX_CalibrationData_t getCalibrationData(uint8_t dev);
void setCalibrationData(uint8_t dev, VL53LX_CalibrationData_t data);
void setXTalkCompensation(uint8_t dev, bool state);
void setOffsetCorrectionMode(uint8_t dev, VL53LX_OffsetCorrectionModes state);

#endif