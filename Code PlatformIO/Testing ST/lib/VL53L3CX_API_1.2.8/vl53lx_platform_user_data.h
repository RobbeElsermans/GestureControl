
/* SPDX-License-Identifier: GPL-2.0+ OR BSD-3-Clause */
/******************************************************************************
 * Copyright (c) 2020, STMicroelectronics - All Rights Reserved

 This file is part of VL53LX and is dual licensed,
 either GPL-2.0+
 or 'BSD 3-clause "New" or "Revised" License' , at your option.
 ******************************************************************************
 */



#ifndef _VL53LX_PLATFORM_USER_DATA_H_
#define _VL53LX_PLATFORM_USER_DATA_H_

#ifndef __KERNEL__
#include <stdlib.h>
#endif
#include "stm32f4xx_hal.h"
#include "vl53lx_def.h"
#include "vl53l3cx.h"

#ifdef __cplusplus
extern "C"
{
#endif


typedef struct {
	VL53LX_DevData_t   Data;
	/*!< Low Level Driver data structure */
    uint8_t   i2c_slave_address;
	uint8_t   comms_type;
	uint16_t  comms_speed_khz;
	I2C_HandleTypeDef *I2cHandle;
	uint8_t   I2cDevAddr;
	int     Present;
	int 	Enabled;
	int LoopState;
	int FirstStreamCountZero;
	int 	Idle;
	int		Ready;
	uint8_t RangeStatus;
	FixPoint1616_t SignalRateRtnMegaCps;
	VL53LX_DeviceState   device_state;  /*!< Device State */
} VL53LX_Dev_t;



typedef VL53LX_Dev_t* VL53LX_DEV;

#define VL53LXDevDataGet(Obj, field) 			(Obj->Dev.Data.field)
#define VL53LXDevDataSet(Obj, field, data) 		((Obj->Dev.Data.field) = (data))
#define PALDevDataGet(Obj, field) 				(Obj->Dev.Data.field)
#define PALDevDataSet(Obj, field, value) 		(Obj->Dev.Data.field)=(value)
#define VL53LXDevStructGetLLDriverHandle(Obj) 	(&Obj->Dev.Data.LLData)
#define VL53LXDevStructGetLLResultsHandle(Obj) 	(&Obj->Dev.Data.llresults)

#ifdef __cplusplus
}
#endif

#endif


