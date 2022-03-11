#ifndef CALIBRATIONDATA_H
#define CALIBRATIONDATA_H
#include "vl53lx_api.h"			   //Om calibration methodes te kunnen gebruiken
//#include "53l3a2_ranging_sensor.h" //Om dev obj te kunnen gebruiken
#include "stdbool.h" //Nodig om bool te kunnen gebruiken
#include "53l3a2_ranging_sensor.h" //Om VL53L3A2_DEV_LEFT, ... te gebruiken



void RefSpadCal(uint8_t dev); 
void xTalkCal(uint8_t dev);
void offsetPerVcselCal(uint8_t dev, uint16_t distance);
VL53LX_CalibrationData_t getCalibrationData(uint8_t dev);
bool setCalibrationData(uint8_t dev, VL53LX_CalibrationData_t data);
void setXTalkCompensation(uint8_t dev, bool state);
void setOffsetCorrectionMode(uint8_t dev, VL53LX_OffsetCorrectionModes state);

#endif