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

#include "GestureDetectObject.h"	//Deze file bevat de detectie van een persoon

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

	TIM_HandleTypeDef htim3;

	static const char *TofDevStr[] =
		{
			[VL53L3A2_DEV_LEFT] = "LEFT",
			[VL53L3A2_DEV_CENTER] = "CENTER",
			[VL53L3A2_DEV_RIGHT] = "RIGHT"};

	/* Private function prototypes -----------------------------------------------*/
	static void MX_53L3A2_MultiSensorRanging_Init(void);
	// static void MX_53L3A2_MultiSensorRanging_Process(void);
	// static void print_result(RANGING_SENSOR_Result_t *Result);
	static void start_sensor(uint8_t sensor);
	static void stop_sensor(uint8_t sensor);
	static void getResult(uint8_t sensor, RANGING_SENSOR_Result_t *result);
	static long getDistance(uint8_t sensor, RANGING_SENSOR_Result_t *result);

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
		/* USER CODE BEGIN TOF_Process_PreTreatment */

		/*
		for (i = 0; i < RANGING_SENSOR_INSTANCES_NBR; i++)
		{
		  //skip this device if not detected
		  if (ToF_Present[i] != 1) continue;
		   VL53L3A2_RANGING_SENSOR_ConfigProfile(i, &Profile);
		   status = VL53L3A2_RANGING_SENSOR_Start(i, RS_MODE_BLOCKING_CONTINUOUS);

		   if (status != BSP_ERROR_NONE)
		   {
			 printf("VL53L3A2_RANGING_SENSOR_Start failed\r\n");
			 while(1);
		   }
		  } */

		// Enkel de 1ste sensor (Center) opstarten
		/*	Hier zeggen we welk profiel we willen gebruiken
		 * 	bv.
		 *
		 */
		start_sensor(VL53L3A2_DEV_CENTER);

		while (1)
		{
			HAL_Delay(5);
			getResult(VL53L3A2_DEV_CENTER, Result);
			dis1 = getDistance(VL53L3A2_DEV_CENTER, Result);

			ObjectPresent = objectPresent(Result, ObjectPresent);

			// Het meten van de afstand van 2 buitenste sensoren.
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


			// Met afstand een led laten dimmen
			// Op voorwaarde dat de afstand kleiner is dan 500
			if (ObjectPresent && dis0 <= 500)
			{
				__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, (dis0 * 2) + 23);
			}

			// ObjectPresent();

			// Ticks
			//  long x = HAL_GetTick();
			// printf("Ticks: %ld ", x);

			if (!ObjectPresent)
			{
				uint8_t obj1 = (uint8_t)Result[VL53L3A2_DEV_CENTER].ZoneResult[0].NumberOfTargets;
				uint8_t sta1 = (uint8_t)Result[VL53L3A2_DEV_CENTER].ZoneResult[0].Status[0];
#if DEBUGGING
				printf("center: %5d obj: %1d sta: %2d", dis1, obj1, sta1);
				printf("\r\n");
#endif
			}
			else
			{
				uint8_t obj0 = (uint8_t)Result[VL53L3A2_DEV_LEFT].ZoneResult[0].NumberOfTargets;
				uint8_t obj1 = (uint8_t)Result[VL53L3A2_DEV_CENTER].ZoneResult[0].NumberOfTargets;
				uint8_t obj2 = (uint8_t)Result[VL53L3A2_DEV_RIGHT].ZoneResult[0].NumberOfTargets;

				uint8_t sta0 = (uint8_t)Result[VL53L3A2_DEV_LEFT].ZoneResult[0].Status[0];
				uint8_t sta1 = (uint8_t)Result[VL53L3A2_DEV_CENTER].ZoneResult[0].Status[0];
				uint8_t sta2 = (uint8_t)Result[VL53L3A2_DEV_RIGHT].ZoneResult[0].Status[0];

#if DEBUGGING
				if (sta0 == sta1 == sta2 == 0)
				{
					printf("left: %5d obj: %1d sta: %2d \t center: %5d obj: %1d sta: %2d \t right: %5d obj: %d sta: %2d", dis0, obj0, sta0, dis1, obj1, sta1, dis2, obj2, sta2);
					printf("\r\n");
				}
#endif
			}

			HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, ObjectPresent);
			HAL_GPIO_WritePin(L_Y_GPIO_Port, L_Y_Pin, ObjectPresent);
		}
		/* USER CODE END TOF_Process_PostTreatment */
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
	/*
	static void MX_53L3A2_MultiSensorRanging_Process(void)
	{
		uint8_t i;
		RANGING_SENSOR_Result_t Result;

	  while (1)
	  {
		//polling mode
		for (i = 0; i < RANGING_SENSOR_INSTANCES_NBR; i++)
		{
		  status = VL53L3A2_RANGING_SENSOR_GetDistance(i, &Result);

		  if (status == BSP_ERROR_NONE)
		  {
			printf("%s\t - ", TofDevStr[i]);
			print_result(&Result);
			HAL_Delay(POLLING_PERIOD);
		  }
		}
		printf ("\r\n");
	  }
	}
	*/

	/*
	static void print_result(RANGING_SENSOR_Result_t *Result)
	{
	  uint8_t i;

	  for (i = 0; i < RANGING_SENSOR_MAX_NB_ZONES; i++)
	  {
		printf("Status = %2ld, Distance = %5ld mm",
		  (long)Result->ZoneResult[i].Status[0],
		  (long)Result->ZoneResult[i].Distance[0]);
	  }
	  printf ("\r\n");
	}
	*/

	static void start_sensor(uint8_t sensor)
	{
		RANGING_SENSOR_ProfileConfig_t Profile;

		Profile.RangingProfile = RS_MULTI_TARGET_MEDIUM_RANGE;
		Profile.TimingBudget = 30; /* 16 ms < TimingBudget < 500 ms */
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
			HAL_Delay(4);
			VL53L3A2_RANGING_SENSOR_GetDistance(sensor, &result[sensor]);
		}
	}

	static long getDistance(uint8_t sensor, RANGING_SENSOR_Result_t *result)
	{
		long distance = (long)result[sensor].ZoneResult[0].Distance[0];
		return distance;
	}

#ifdef __cplusplus
}
#endif
