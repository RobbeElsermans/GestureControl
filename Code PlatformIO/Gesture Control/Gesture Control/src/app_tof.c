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

// #ifndef DEBUGGING
// #define DEBUGGING
// #endif

/* Includes ------------------------------------------------------------------*/
#include "app_tof.h"
#include "main.h"
#include <stdio.h>
#include "53l3a2_ranging_sensor.h"
#include "stm32f4xx_nucleo.h"
#include "stdbool.h" //Nodig om bool te kunnen gebruiken

#include "vl53lx_api.h"			   //Om calibration methodes te kunnen gebruiken
#include "53l3a2_ranging_sensor.h" //Om dev obj te kunnen gebruiken

#include "GestureDetectObject.h"  //Deze file bevat de detectie van een persoon
#include "GestureDetectDimming.h" //Bevat methodes om het dimmen te detecteren + om de value te verkrijgen.
#include "GestureDetectRL.h"	  //Bevat methode om gesture Rechts links te herkennen.
#include "GestureDetectLR.h"	  //Bevat methode om gesture Rechts links te herkennen.

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

	bool objectPresent = false; // flag ofdat er een object aanwezig is
	bool hasStarted = false;	// Kijken ofdat de linkse & rechte sensor al opgestart zijn of niet

	// Gesture Right Left
	bool prevGestureRL = false;
	bool gestureRL = false;

	// Gesture Left Right
	bool prevGestureLR = false;
	bool gestureLR = false;

	// Dimming led
	int pwmVal = 0;
	bool gestureDimming = false;

	TIM_HandleTypeDef htim3;

	enum commands
	{
		DIM,
		RL,
		LR,
		UD,
		DU,
		NONE
	};

	typedef enum commands command_t;

	command_t commando = NONE;

	// Timer command
	static float timerCommand = 0;
	static bool timerCommandSet = false;
	static int timerCommandTimeout = 2000; // 2 seconden

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

		initObjectPresent(-1, -1, -1);

		// Calibratie van SPAD uitvoeren uitvoeren
		VL53LX_CalibrationData_t callData_LEFT;
		VL53LX_CalibrationData_t callData_CENTER;
		VL53LX_CalibrationData_t callData_RIGHT;
		VL53LX_PerformRefSpadManagement(VL53L3A2_RANGING_SENSOR_CompObj[VL53L3A2_DEV_LEFT]);
		VL53LX_PerformRefSpadManagement(VL53L3A2_RANGING_SENSOR_CompObj[VL53L3A2_DEV_CENTER]);
		VL53LX_PerformRefSpadManagement(VL53L3A2_RANGING_SENSOR_CompObj[VL53L3A2_DEV_RIGHT]);

		VL53LX_GetCalibrationData(VL53L3A2_RANGING_SENSOR_CompObj[VL53L3A2_DEV_LEFT], &callData_LEFT);
		VL53LX_GetCalibrationData(VL53L3A2_RANGING_SENSOR_CompObj[VL53L3A2_DEV_CENTER], &callData_CENTER);
		VL53LX_GetCalibrationData(VL53L3A2_RANGING_SENSOR_CompObj[VL53L3A2_DEV_RIGHT], &callData_RIGHT);

		// Crosstalk data voor coverglas
		/**
		 * Dit moeten we herhalen bij telkens een nieuw coverglas op verschillende afstanden
		 * Kijk hier file:///C:/Users/robel/Desktop/testing%20Nucleo/um2778-vl53l3cx-timeofflight-ranging-module-with-multi-object-detection-stmicroelectronics.pdf
		 * voor meer uitleg (Voor mezelf)
		 *
		 */

		int xtalk_kcps_LEFT[] = {243, 493, 743, 993, 1243, 1494};
		int xtalk_bin_data_LEFT[] = {11, 327, 506, 180, 0, 0, 0, 0, 0, 0, 0, 0};

		int xtalk_kcps_CENTER[] = {941, 1878, 2815, 3752, 4689, 5627};
		int xtalk_bin_data_CENTER[] = {20, 429, 454, 121, 0, 0, 0, 0, 0, 0, 0, 0};

		int xtalk_kcps_RIGHT[] = {611, 1209, 1807, 2405, 3003, 3601};
		int xtalk_bin_data_RIGHT[] = {14, 425, 461, 124, 0, 0, 0, 0, 0, 0, 0, 0};

for (uint8_t i = 0; i < 6; i++)
		{
			callData_LEFT.algo__xtalk_cpo_HistoMerge_kcps[i] = xtalk_kcps_LEFT[i];
		}

		for (uint8_t i = 0; i < 12; i++)
		{
			callData_LEFT.xtalkhisto.xtalk_shape.bin_data[i] = xtalk_bin_data_LEFT[i];
		}

		for (uint8_t i = 0; i < 6; i++)
		{
			callData_CENTER.algo__xtalk_cpo_HistoMerge_kcps[i] = xtalk_kcps_CENTER[i];
		}

		for (uint8_t i = 0; i < 12; i++)
		{
			callData_CENTER.xtalkhisto.xtalk_shape.bin_data[i] = xtalk_bin_data_CENTER[i];
		}

		for (uint8_t i = 0; i < 6; i++)
		{
			callData_RIGHT.algo__xtalk_cpo_HistoMerge_kcps[i] = xtalk_kcps_RIGHT[i];
		}

		for (uint8_t i = 0; i < 12; i++)
		{
			callData_RIGHT.xtalkhisto.xtalk_shape.bin_data[i] = xtalk_bin_data_RIGHT[i];
		}

		callData_LEFT.xtalkhisto.xtalk_shape.zero_distance_phase = 4481;
		callData_LEFT.per_vcsel_cal_data.long_a_offset_mm = -33;
		callData_LEFT.per_vcsel_cal_data.long_b_offset_mm = 35;
		callData_LEFT.per_vcsel_cal_data.medium_a_offset_mm = -46;
		callData_LEFT.per_vcsel_cal_data.medium_b_offset_mm = -46;
		callData_LEFT.per_vcsel_cal_data.short_a_offset_mm = 43;
		callData_LEFT.per_vcsel_cal_data.short_b_offset_mm = -43;

		callData_CENTER.xtalkhisto.xtalk_shape.zero_distance_phase = 4186;
		callData_CENTER.per_vcsel_cal_data.long_a_offset_mm = -25;
		callData_CENTER.per_vcsel_cal_data.long_b_offset_mm = -25;
		callData_CENTER.per_vcsel_cal_data.medium_a_offset_mm = -28;
		callData_CENTER.per_vcsel_cal_data.medium_b_offset_mm = -30;
		callData_CENTER.per_vcsel_cal_data.short_a_offset_mm = -31;
		callData_CENTER.per_vcsel_cal_data.short_b_offset_mm = -27;

		callData_RIGHT.xtalkhisto.xtalk_shape.zero_distance_phase = 4204;
		callData_RIGHT.per_vcsel_cal_data.long_a_offset_mm = -32;
		callData_RIGHT.per_vcsel_cal_data.long_b_offset_mm = -34;
		callData_RIGHT.per_vcsel_cal_data.medium_a_offset_mm = -34;
		callData_RIGHT.per_vcsel_cal_data.medium_b_offset_mm = -38;
		callData_RIGHT.per_vcsel_cal_data.short_a_offset_mm = -40;
		callData_RIGHT.per_vcsel_cal_data.short_b_offset_mm = -40;

		//// Callibratie van crosstalk (coverglas)
		// VL53LX_PerformXTalkCalibration(VL53L3A2_RANGING_SENSOR_CompObj[VL53L3A2_DEV_LEFT]);
		// VL53LX_PerformXTalkCalibration(VL53L3A2_RANGING_SENSOR_CompObj[VL53L3A2_DEV_CENTER]);
		// VL53LX_PerformXTalkCalibration(VL53L3A2_RANGING_SENSOR_CompObj[VL53L3A2_DEV_RIGHT]);
		//// De offset bepalen zodat deze juist is is.
		// VL53LX_PerformOffsetPerVcselCalibration(VL53L3A2_RANGING_SENSOR_CompObj[VL53L3A2_DEV_LEFT], 600);
		// VL53LX_PerformOffsetPerVcselCalibration(VL53L3A2_RANGING_SENSOR_CompObj[VL53L3A2_DEV_CENTER], 600);
		// VL53LX_PerformOffsetPerVcselCalibration(VL53L3A2_RANGING_SENSOR_CompObj[VL53L3A2_DEV_RIGHT], 600);
		//// Waardes opvragen
		// VL53LX_GetCalibrationData(VL53L3A2_RANGING_SENSOR_CompObj[VL53L3A2_DEV_LEFT], &callData_LEFT);
		// VL53LX_GetCalibrationData(VL53L3A2_RANGING_SENSOR_CompObj[VL53L3A2_DEV_CENTER], &callData_CENTER);
		// VL53LX_GetCalibrationData(VL53L3A2_RANGING_SENSOR_CompObj[VL53L3A2_DEV_RIGHT], &callData_RIGHT);


		VL53LX_SetCalibrationData(VL53L3A2_RANGING_SENSOR_CompObj[VL53L3A2_DEV_LEFT], &callData_LEFT);
		VL53LX_SetCalibrationData(VL53L3A2_RANGING_SENSOR_CompObj[VL53L3A2_DEV_CENTER], &callData_CENTER);
		VL53LX_SetCalibrationData(VL53L3A2_RANGING_SENSOR_CompObj[VL53L3A2_DEV_RIGHT], &callData_RIGHT);

		VL53LX_SetOffsetCorrectionMode(VL53L3A2_RANGING_SENSOR_CompObj[VL53L3A2_DEV_LEFT], (VL53LX_OffsetCorrectionModes)VL53LX_OFFSETCORRECTIONMODE_PERVCSEL);
		VL53LX_SetXTalkCompensationEnable(VL53L3A2_RANGING_SENSOR_CompObj[VL53L3A2_DEV_LEFT], 1);

		VL53LX_SetOffsetCorrectionMode(VL53L3A2_RANGING_SENSOR_CompObj[VL53L3A2_DEV_CENTER], (VL53LX_OffsetCorrectionModes)VL53LX_OFFSETCORRECTIONMODE_PERVCSEL);
		VL53LX_SetXTalkCompensationEnable(VL53L3A2_RANGING_SENSOR_CompObj[VL53L3A2_DEV_CENTER], 1);

		VL53LX_SetOffsetCorrectionMode(VL53L3A2_RANGING_SENSOR_CompObj[VL53L3A2_DEV_RIGHT], (VL53LX_OffsetCorrectionModes)VL53LX_OFFSETCORRECTIONMODE_PERVCSEL);
		VL53LX_SetXTalkCompensationEnable(VL53L3A2_RANGING_SENSOR_CompObj[VL53L3A2_DEV_RIGHT], 1);
	}

	/*
	 * LM background task
	 */
	void MX_TOF_Process(void *_htim3)
	{
		htim3 = *(TIM_HandleTypeDef *)_htim3;

		start_sensor(VL53L3A2_DEV_CENTER);

		while (1)
		{
			// HAL_Delay(5);
			getResult(VL53L3A2_DEV_CENTER, Result);
			dis1 = getDistance(VL53L3A2_DEV_CENTER, Result);

			objectPresent = ckeckObjectPresent(Result, &objectPresent, &dis1);

			if (objectPresent)
			{
				if (!hasStarted) // Start andere sensoren ook op
				{
					hasStarted = true;
					start_sensor(VL53L3A2_DEV_LEFT);
					start_sensor(VL53L3A2_DEV_RIGHT);

					// PWM timer starten
					HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
				}

				// Resultaten opvragen sensoren
				getResult(VL53L3A2_DEV_LEFT, Result);
				dis0 = getDistance(VL53L3A2_DEV_LEFT, Result);
				// Resultaten opvragen sensoren
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

			if (objectPresent)
				__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, (pwmVal * 2) + 23);

			int sta0 = (int)Result[VL53L3A2_DEV_LEFT].ZoneResult[0].Status[0];
			int sta1 = (int)Result[VL53L3A2_DEV_CENTER].ZoneResult[0].Status[0];
			int sta2 = (int)Result[VL53L3A2_DEV_RIGHT].ZoneResult[0].Status[0];
			int dis0 = (int)Result[VL53L3A2_DEV_LEFT].ZoneResult[0].Distance[0];
			int dis1 = (int)Result[VL53L3A2_DEV_CENTER].ZoneResult[0].Distance[0];
			int dis2 = (int)Result[VL53L3A2_DEV_RIGHT].ZoneResult[0].Distance[0];
			int obj0 = (int)Result[VL53L3A2_DEV_LEFT].ZoneResult[0].NumberOfTargets;
			int obj1 = (int)Result[VL53L3A2_DEV_CENTER].ZoneResult[0].NumberOfTargets;
			int obj2 = (int)Result[VL53L3A2_DEV_RIGHT].ZoneResult[0].NumberOfTargets;

			printf("left: %5d obj: %1d sta: %2d \t center: %5d obj: %1d sta: %2d \t right: %5d obj: %d sta: %2d", dis0, obj0, sta0, dis1, obj1, sta1, dis2, obj2, sta2);
			printf("\r\n");

			// Kijken ofdat er een dimming commando aanwezig is
			gestureDimming = CheckDimmingCommand(&gestureDimming, &objectPresent, &dis1, &sta1);

			// Wanneer er geen dimming commando aanwezig is dan kijken we of dat er een Right Left beweging aanwezig is
			if (!gestureDimming)
				gestureRL = CheckGestureRL(&gestureRL, &objectPresent, Result);

			// Wanneer er geen dimming commando aanwezig is dan kijken we of dat er een Left Right beweging aanwezig is
			if (!gestureDimming)
				gestureLR = CheckGestureLR(&gestureLR, &objectPresent, Result);

			// Het commando dimming activeren
			if (gestureDimming)
			{
				commando = DIM;
				pwmVal = getDimmingValue(&gestureDimming, &pwmVal, &dis1);
			}

			// Het commando RL activeren
			if (gestureRL && !prevGestureRL)
			{
				prevGestureRL = gestureRL;
				printf("gestureCommand RL: %d \r\n", gestureRL);
				commando = RL;
			}

			// Het commando LR activeren
			if (gestureLR && !prevGestureLR)
			{
				prevGestureLR = gestureLR;
				printf("gestureCommand LR: %d \r\n", gestureLR);
				commando = LR;
			}
			prevGestureRL = gestureRL; // fix debouncing van gestureRL
			prevGestureLR = gestureLR; // fix debouncing van gestureLR

			// Refreshrate van schakeling zichtbaar maken
			HAL_GPIO_TogglePin(L_Y_GPIO_Port, L_Y_Pin);

			/* 	Timer om leds even aan te laten
				Er wordt gekeken wanneer commando veranderd wordt naar alles behalve NONE.
				Dan zetten we een timer
				Wanneer de timer afloopt wordt het commando gereset
			*/
			if (!timerCommandSet && commando != NONE)
			{
				timerCommandSet = true;
				timerCommand = HAL_GetTick();
			}
			if ((HAL_GetTick() - timerCommand) >= timerCommandTimeout)
			{
				timerCommandSet = false;
				commando = NONE;
			}
			// Commando's uitsturen
			switch (commando)
			{
			case NONE:
				HAL_GPIO_WritePin(SMD1_Port, SMD1_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(SMD2_Port, SMD2_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(SMD3_Port, SMD3_Pin, GPIO_PIN_RESET);
				break;
			case RL:
				HAL_GPIO_WritePin(SMD1_Port, SMD1_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(SMD2_Port, SMD2_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(SMD3_Port, SMD3_Pin, GPIO_PIN_RESET);
				break;
			case LR:
				HAL_GPIO_WritePin(SMD1_Port, SMD1_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(SMD2_Port, SMD2_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(SMD3_Port, SMD3_Pin, GPIO_PIN_RESET);
				break;
			case UD:
				HAL_GPIO_WritePin(SMD1_Port, SMD1_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(SMD2_Port, SMD2_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(SMD3_Port, SMD3_Pin, GPIO_PIN_SET);
				break;
			case DU:
				HAL_GPIO_WritePin(SMD1_Port, SMD1_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(SMD2_Port, SMD2_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(SMD3_Port, SMD3_Pin, GPIO_PIN_SET);
				break;
			case DIM:
				HAL_GPIO_WritePin(SMD1_Port, SMD1_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(SMD2_Port, SMD2_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(SMD3_Port, SMD3_Pin, GPIO_PIN_SET);
				break;

			default:
				HAL_GPIO_WritePin(SMD1_Port, SMD1_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(SMD2_Port, SMD2_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(SMD3_Port, SMD3_Pin, GPIO_PIN_RESET);
				break;
			}
			HAL_GPIO_WritePin(L_R_GPIO_Port, L_R_Pin, objectPresent);
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
#ifdef DEBUGGING
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
#ifdef DEBUGGING
			printf("VL53L3A2_RANGING_SENSOR_Start failed for sensor %s \r\n", TofDevStr[sensor]);
#endif
			while (1)
				;
		}
		else
		{
#ifdef DEBUGGING
			printf("sensor %s\t opgestart \r\n", TofDevStr[sensor]);
#endif
		}
	}

	static void stop_sensor(uint8_t sensor)
	{
		status = VL53L3A2_RANGING_SENSOR_Stop(sensor);
		if (status != BSP_ERROR_NONE)
		{
#ifdef DEBUGGING
			printf("VL53L3A2_RANGING_SENSOR_Stop failed\r\n");
#endif
			while (1)
				;
		}
		else
		{
#ifdef DEBUGGING
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
			// HAL_Delay(1);
			VL53L3A2_RANGING_SENSOR_GetDistance(sensor, &result[sensor]);
		}
	}

	static long getDistance(uint8_t sensor, RANGING_SENSOR_Result_t *result)
	{
		long distance = 0;
		// do
		// {
		// getResult(sensor, result);
		distance = (long)result[sensor].ZoneResult[0].Distance[0];
		// 	HAL_Delay(2);
		// } while (distance == 0);

		return distance;
	}

#ifdef __cplusplus
}
#endif
