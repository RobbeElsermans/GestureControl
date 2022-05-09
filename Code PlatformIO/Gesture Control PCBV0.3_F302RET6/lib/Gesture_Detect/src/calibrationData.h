#ifndef CALIBRATIONDATA_H
#define CALIBRATIONDATA_H

#include "vl53lx_api.h"			   //Om calibration methodes te kunnen gebruiken
#include "main.h"
#include "stdbool.h"


void getCalibrate(VL53L3CX_Object_t* dev, uint8_t id);
void setCalibrate(VL53L3CX_Object_t* dev, uint8_t id);



#endif