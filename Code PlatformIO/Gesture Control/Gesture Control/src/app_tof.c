/**
 ******************************************************************************
 * @file          : app_tof.c
 * @author        : IMG SW Application Team
 * @brief         : This file provides code for the configuration
 *                  of the STMicroelectronics.X-CUBE-TOF1.3.0.0 instances.
 ******************************************************************************
 *
 * @attention
 *
 * Copyright (c) 2022 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#ifdef __cplusplus
extern "C"
{
#endif

#ifndef DEBUGGING
#define DEBUGGING true
#endif

/* Includes ------------------------------------------------------------------*/
#include "app_tof.h"
#include "main.h"
#include <stdio.h>
#include "53l3a2_ranging_sensor.h"
#include "stm32f4xx_nucleo.h"
#include "stdbool.h" //Nodig om bool te kunnen gebruiken

#include "GestureDetectObject.h"  //Deze file bevat de detectie van een persoon
#include "GestureDetectDimming.h" //Bevat methodes om het dimmen te detecteren + om de value te verkrijgen.

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#define POLLING_PERIOD (100U) /* milliseconds */

	/* Private variables ---------------------------------------------------------*/
	static int32_t status = 0;
	static uint8_t ToF_Present[RANGING_SENSOR_INSTANCES_NBR] = {0};
	volatile uint8_t ToF_EventDetected = 0;

	RANGING_SENSOR_Result_t Result[3];
	int dis0 = 0;
	int dis1 = 0;
	int dis2 = 0;

	bool ObjectPresent = false; // flag ofdat er een object aanwezig is
	bool hasStarted = false;	// Kijken ofdat de linkse & rechte sensor al opgestart zijn of niet

	// Gesture Right Left
	bool hasLeft = false;
	bool hasCenter = false;
	bool hasRight = false;
	bool gestureRL = false;
	int maxDistanceObject = 250;
	float timerMeasurment = 0;
	bool timerMeasurementSet = false;
	int timerMeasurmentTimeout = 1500; // 2 seconden

	// Dimming led
	uint16_t pwmVal = 0;
	bool dimming = false;

	TIM_HandleTypeDef htim3;

	static const char *TofDevStr[] =
		{
			[VL53L3A2_DEV_LEFT] = "LEFT",
			[VL53L3A2_DEV_CENTER] = "CENTER",
			[VL53L3A2_DEV_RIGHT] = "RIGHT"};

	/* Intern functions ----------------------------------------------------------*/
	static void start_sensor(uint8_t sensor);
	static void stop_sensor(uint8_t sensor);
	static void getResult(uint8_t sensor, RANGING_SENSOR_Result_t *result);
	static long getDistance(uint8_t sensor, RANGING_SENSOR_Result_t *result);
	static void MX_53L3A2_MultiSensorRanging_Init(void);

	void MX_TOF_Init(void)
	{
		MX_53L3A2_MultiSensorRanging_Init();
	}

	/*
	 * LM background task
	 */
	void MX_TOF_Process(void *_htim3)
	{
		htim3 = *(TIM_HandleTypeDef *)_htim3;

		// Enkel de 1ste sensor (Center) opstarten
		/*	Hier zeggen we welk profiel we willen gebruiken
		 * 	bv.
		 *
		 */
		start_sensor(VL53L3A2_DEV_CENTER);

		while (1)
		{
			// HAL_Delay(5);
			getResult(VL53L3A2_DEV_CENTER, Result);
			dis1 = getDistance(VL53L3A2_DEV_CENTER, Result);

			ObjectPresent = ckeckObjectPresent(Result, &ObjectPresent);

			if (ObjectPresent)
			{
				// Persoon naderd en staat dicht genoeg
				// Start andere sensoren ook op

				if (!hasStarted)
				{
					hasStarted = true;
					start_sensor(VL53L3A2_DEV_LEFT);
					start_sensor(VL53L3A2_DEV_RIGHT);

					// PWM timer starten
					HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
				}

				getResult(VL53L3A2_DEV_LEFT, Result);
				dis0 = getDistance(VL53L3A2_DEV_LEFT, Result);

				getResult(VL53L3A2_DEV_RIGHT, Result);
				dis2 = getDistance(VL53L3A2_DEV_RIGHT, Result);
			}
			else
			{
				if (hasStarted)
				{
					hasStarted = false;
					stop_sensor(VL53L3A2_DEV_LEFT);
					stop_sensor(VL53L3A2_DEV_RIGHT);

					// PWM timer starten
					HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_2);

					HAL_Delay(2);
				}
			}

			CheckDimmingCommand(&dimming, &ObjectPresent, &dis0);
			pwmVal = getDimmingValue(&dimming, &pwmVal, &dis0);

			if (ckeckObjectPresent)
				__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, (pwmVal * 2) + 23);

			// if (!ObjectPresent)
			// {
			// 	// uint8_t obj1 = (uint8_t)Result[VL53L3A2_DEV_CENTER].ZoneResult[0].NumberOfTargets;
			// 	// uint8_t sta1 = (uint8_t)Result[VL53L3A2_DEV_CENTER].ZoneResult[0].Status[0];

			// 	// printf("center: %5d obj: %1d sta: %2d", dis1, obj1, sta1);
			// 	// printf("\r\n");
			// }
			// else
			// {

			// 	// uint8_t obj0 = (uint8_t)Result[VL53L3A2_DEV_LEFT].ZoneResult[0].NumberOfTargets;
			// 	// uint8_t obj1 = (uint8_t)Result[VL53L3A2_DEV_CENTER].ZoneResult[0].NumberOfTargets;
			// 	// uint8_t obj2 = (uint8_t)Result[VL53L3A2_DEV_RIGHT].ZoneResult[0].NumberOfTargets;

			// 	// uint8_t sta0 = (uint8_t)Result[VL53L3A2_DEV_LEFT].ZoneResult[0].Status[0];
			// 	// uint8_t sta1 = (uint8_t)Result[VL53L3A2_DEV_CENTER].ZoneResult[0].Status[0];
			// 	// uint8_t sta2 = (uint8_t)Result[VL53L3A2_DEV_RIGHT].ZoneResult[0].Status[0];

			// 	//printf("left: %5d obj: %1d sta: %2d \t center: %5d obj: %1d sta: %2d \t right: %5d obj: %d sta: %2d", dis0, obj0, sta0, dis1, obj1, sta1, dis2, obj2, sta2);
			// 	//printf("\r\n");
			// }
			HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, ObjectPresent);

			// Detecteren commando van rechts naar links
			// Eerst moet sensor right minder binnen krijgen
			// Dan sensor center
			// Als laatste sensor left
			if (ObjectPresent)
			{
				uint8_t sta0 = (uint8_t)Result[VL53L3A2_DEV_LEFT].ZoneResult[0].Status[0];
				//uint8_t sta1 = (uint8_t)Result[VL53L3A2_DEV_CENTER].ZoneResult[0].Status[0];
				uint8_t sta2 = (uint8_t)Result[VL53L3A2_DEV_RIGHT].ZoneResult[0].Status[0];

				if ((dis2 < maxDistanceObject) && (sta2 == 0) && !hasRight && !hasLeft) // Sensor right
				{
					hasRight = true;
					printf("right Trigger: \r\n");
				}
				// else if ((dis1 < maxDistanceObject) && (sta1 == 0) && hasRight && !hasCenter && !hasLeft) // Sensor center
				// {
				// 	hasCenter = true;
				// 	printf("center Trigger: \r\n");
				// }
				else if ((dis0 < maxDistanceObject) && (sta0 == 0) && hasRight && !hasLeft) // Sensor left
				{
					hasLeft = true;
					gestureRL = true;
					printf("left Trigger: \r\n");
				}
			}

			// Een timeout timer plaatsen
			if (!timerMeasurementSet && (hasRight || hasCenter || hasLeft))
			{
				timerMeasurementSet = true;
				timerMeasurment = HAL_GetTick();
				// printf("timer set Trigger: \r\n");
			}

			// Bij het afgaan van de timer
			if (timerMeasurementSet)
				if (((HAL_GetTick() - timerMeasurment) >= timerMeasurmentTimeout))
				{
					timerMeasurementSet = false;
					hasRight = false;
					hasLeft = false;
					//hasCenter = false;
					gestureRL = false;
					printf("timer Trigger: \r\n");
				}

			if (gestureRL)
			{
				HAL_Delay(2000);
				printf("gestureCommand: %d \r\n", gestureRL);
				timerMeasurementSet = false;
				hasRight = false;
				hasLeft = false;
				//hasCenter = false;
				gestureRL = false;
			}

			HAL_GPIO_TogglePin(L_Y_GPIO_Port, L_Y_Pin);
		}
	}

	static void MX_53L3A2_MultiSensorRanging_Init(void)
	{
		uint8_t device;
		uint16_t i2c_addr;
		uint32_t id;

		/* Initialize Virtual COM Port */
		BSP_COM_Init(COM1);

		printf("53L3A2 Gesture Control\r\n");

		/* put all the devices in shutdown mode */
		for (device = 0; device < RANGING_SENSOR_INSTANCES_NBR; device++)
		{
			VL53L3A2_RANGING_SENSOR_SetPowerMode(device, RANGING_SENSOR_POWERMODE_OFF);
		}

		/* power on the devices one at a time, initialize them and change their address.
		 * once the address is updated, the communication with the devices is checked
		 * reading its ID.
		 */
		for (device = 0; device < RANGING_SENSOR_INSTANCES_NBR; device++)
		{
			VL53L3A2_RANGING_SENSOR_SetPowerMode(device, RANGING_SENSOR_POWERMODE_ON);
			status = VL53L3A2_RANGING_SENSOR_Init(device);

			/* 0: not detected, 1: detected */
			ToF_Present[device] = (status != BSP_ERROR_NONE) ? 0 : 1;

			/* skip this device if init not successful */
			if (ToF_Present[device] == 0)
				continue;

			/* left: 0x54, center: 0x56, right: 0x58 */
			i2c_addr = (RANGING_SENSOR_VL53L3CX_ADDRESS + (device + 1) * 2);
			VL53L3A2_RANGING_SENSOR_SetAddress(device, i2c_addr);

			/* check the communication with the device reading the ID */
			VL53L3A2_RANGING_SENSOR_ReadID(device, &id);
#if DEBUGGING
			printf("ToF sensor %d - ID: %04lX\r\n", device, (unsigned long)id);
#endif
		}
	}

	static void start_sensor(uint8_t sensor)
	{
		RANGING_SENSOR_ProfileConfig_t Profile;

		Profile.RangingProfile = RS_MULTI_TARGET_MEDIUM_RANGE;
		Profile.TimingBudget = 10; /* 16 ms < TimingBudget < 500 ms */
		Profile.Frequency = 0;	   /* not necessary in simple ranging */
		Profile.EnableAmbient = 1; /* Enable: 1, Disable: 0 */
		Profile.EnableSignal = 1;  /* Enable: 1, Disable: 0 */

		VL53L3A2_RANGING_SENSOR_ConfigProfile(sensor, &Profile);
		status = VL53L3A2_RANGING_SENSOR_Start(sensor, RS_MODE_BLOCKING_CONTINUOUS);
		if (status != BSP_ERROR_NONE)
		{
#if DEBUGGING
			printf("VL53L3A2_RANGING_SENSOR_Start failed for sensor %s \r\n", TofDevStr[sensor]);
#endif
			while (1)
				;
		}
		else
		{
#if DEBUGGING
			printf("sensor %s\t opgestart \r\n", TofDevStr[sensor]);
#endif
		}
	}

	static void stop_sensor(uint8_t sensor)
	{
		status = VL53L3A2_RANGING_SENSOR_Stop(sensor);
		if (status != BSP_ERROR_NONE)
		{
#if DEBUGGING
			printf("VL53L3A2_RANGING_SENSOR_Stop failed\r\n");
#endif
			while (1)
				;
		}
		else
		{
#if DEBUGGING
			printf("sensor %s\t afgezet \r\n", TofDevStr[sensor]);
#endif
		}
	}

	static void getResult(uint8_t sensor, RANGING_SENSOR_Result_t *result)
	{
		VL53L3A2_RANGING_SENSOR_GetDistance(sensor, &result[sensor]);

		// Bug van 1ste meeting dat deze fout is (Een te hoge waarden)
		if ((long)result[sensor].ZoneResult[0].Distance[0] >= 17760520)
		{
			//HAL_Delay(1);
			VL53L3A2_RANGING_SENSOR_GetDistance(sensor, &result[sensor]);
		}
	}

	static long getDistance(uint8_t sensor, RANGING_SENSOR_Result_t *result)
	{
		long distance = 0;
		// do
		// {
		//getResult(sensor, result);
		distance = (long)result[sensor].ZoneResult[0].Distance[0];
		// 	HAL_Delay(2);
		// } while (distance == 0);

		return distance;
	}

#ifdef __cplusplus
}
#endif
