#ifndef UNIT_TOF_TEST_H
#define UNIT_TOF_TEST_H

#include <unity.h>

#include "stdbool.h" //Nodig om bool te kunnen gebruiken
#include "stm32f3xx_hal.h"

#include "i2c.h"
#include "gpio.h"
#include "main.h"

#include "vl53lx_api.h"
#include "custom_tof_conf.h"
#include "vl53l3cx.h"

void run_tof_connectivity();
void run_tof_range();
void run_all_tof_connectivity();
void run_all_tof_range();

#endif