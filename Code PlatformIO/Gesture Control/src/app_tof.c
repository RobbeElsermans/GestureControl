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
#include "GestureDetectRL.h"	  //Bevat methode om gesture Rechts Links te herkennen.
#include "GestureDetectLR.h"	  //Bevat methode om gesture Links Rechts te herkennen.
#include "GestureDetectDU.h"	  //Bevat methode om gesture Onder Boven te herkennen.

#include "calibrationData.h" //bevat methodes en instellingen om de sensoren te calibreren.

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#define POLLING_PERIOD (100U) /* milliseconds */

	/* Private variables ---------------------------------------------------------*/
	static int32_t status = 0;
	static uint8_t ToF_Present[RANGING_SENSOR_INSTANCES_NBR] = {0};
	volatile uint8_t ToF_EventDetected = 0;

	RANGING_SENSOR_Result_t Result[RANGING_SENSOR_INSTANCES_NBR];
	int dis0 = 0;
	int dis1 = 0;
	int dis2 = 0;
	int dis3 = 0;
	int dis4 = 0;

	bool objectPresent = false; // flag ofdat er een object aanwezig is
	bool hasStarted = false;	// Kijken ofdat de linkse & rechte sensor al opgestart zijn of niet

	// Gesture Right Left
	bool prevGestureRL = false;
	bool gestureRL = false;

	// Gesture Left Right
	bool prevGestureLR = false;
	bool gestureLR = false;

	// Gesture Down Up
	bool prevGestureDU = false;
	bool gestureDU = false;

	// Gesture Up Down
	bool prevGestureUD = false;
	bool gestureUD = false;

	// Dimming led
	int pwmVal = 0;
	bool gestureDimming = false;

	TIM_HandleTypeDef htim3;
	I2C_HandleTypeDef hi2c3;

	enum commands
	{
		DIM = 0x25,
		RL = 0x22,
		LR = 0x21,
		UD = 0x23,
		DU = 0x24,
		NONE = 0x10
	};

	typedef enum commands command_t;

	command_t commando = NONE;

	// Timer command
	static float timerCommand = 0;
	static bool timerCommandSet = false;
	static int timerCommandTimeout = 2000; // 2 seconden

	bool toggleReading = false;

	int8_t buf;

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

		// Calibraties uitvoeren
		VL53LX_CalibrationData_t callData[RANGING_SENSOR_INSTANCES_NBR];

		RefSpadCal(VL53L3A2_DEV_LEFT);
		RefSpadCal(VL53L3A2_DEV_CENTER);
		RefSpadCal(VL53L3A2_DEV_RIGHT);
		RefSpadCal(VL53L3A2_DEV_TOP);
		RefSpadCal(VL53L3A2_DEV_BOTTOM);

		callData[VL53L3A2_DEV_LEFT] = getCalibrationData(VL53L3A2_DEV_LEFT);
		callData[VL53L3A2_DEV_CENTER] = getCalibrationData(VL53L3A2_DEV_CENTER);
		callData[VL53L3A2_DEV_RIGHT] = getCalibrationData(VL53L3A2_DEV_RIGHT);
		callData[VL53L3A2_DEV_TOP] = getCalibrationData(VL53L3A2_DEV_TOP);
		callData[VL53L3A2_DEV_BOTTOM] = getCalibrationData(VL53L3A2_DEV_BOTTOM);

		// // Callibratie van crosstalk (coverglas)
		// xTalkCal(VL53L3A2_DEV_LEFT);
		// xTalkCal(VL53L3A2_DEV_CENTER);
		// xTalkCal(VL53L3A2_DEV_RIGHT);
		// xTalkCal(VL53L3A2_DEV_TOP);
		// xTalkCal(VL53L3A2_DEV_BOTTOM);

		// // De offset bepalen zodat deze juist is is.
		// offsetPerVcselCal(VL53L3A2_DEV_LEFT, 600);
		// offsetPerVcselCal(VL53L3A2_DEV_CENTER, 600);
		// offsetPerVcselCal(VL53L3A2_DEV_RIGHT, 600);
		// offsetPerVcselCal(VL53L3A2_DEV_TOP, 600);
		// offsetPerVcselCal(VL53L3A2_DEV_BOTTOM, 600);

		// // Waardes opvragen
		// callData[VL53L3A2_DEV_LEFT] = getCalibrationData(VL53L3A2_DEV_LEFT);
		// callData[VL53L3A2_DEV_CENTER] = getCalibrationData(VL53L3A2_DEV_CENTER);
		// callData[VL53L3A2_DEV_RIGHT] = getCalibrationData(VL53L3A2_DEV_RIGHT);
		// callData[VL53L3A2_DEV_TOP] = getCalibrationData(VL53L3A2_DEV_TOP);
		// callData[VL53L3A2_DEV_BOTTOM] = getCalibrationData(VL53L3A2_DEV_BOTTOM);

		setCalibrationData(VL53L3A2_DEV_LEFT, callData[VL53L3A2_DEV_LEFT]);
		setCalibrationData(VL53L3A2_DEV_CENTER, callData[VL53L3A2_DEV_CENTER]);
		setCalibrationData(VL53L3A2_DEV_RIGHT, callData[VL53L3A2_DEV_RIGHT]);
		setCalibrationData(VL53L3A2_DEV_TOP, callData[VL53L3A2_DEV_TOP]);
		setCalibrationData(VL53L3A2_DEV_BOTTOM, callData[VL53L3A2_DEV_BOTTOM]);

		setOffsetCorrectionMode(VL53L3A2_DEV_LEFT, (VL53LX_OffsetCorrectionModes)VL53LX_OFFSETCORRECTIONMODE_PERVCSEL);
		setXTalkCompensation(VL53L3A2_DEV_LEFT, 1);

		setOffsetCorrectionMode(VL53L3A2_DEV_CENTER, (VL53LX_OffsetCorrectionModes)VL53LX_OFFSETCORRECTIONMODE_PERVCSEL);
		setXTalkCompensation(VL53L3A2_DEV_CENTER, 1);

		setOffsetCorrectionMode(VL53L3A2_DEV_RIGHT, (VL53LX_OffsetCorrectionModes)VL53LX_OFFSETCORRECTIONMODE_PERVCSEL);
		setXTalkCompensation(VL53L3A2_DEV_RIGHT, 1);

		setOffsetCorrectionMode(VL53L3A2_DEV_TOP, (VL53LX_OffsetCorrectionModes)VL53LX_OFFSETCORRECTIONMODE_PERVCSEL);
		// setXTalkCompensation(VL53L3A2_DEV_TOP, 1);

		setOffsetCorrectionMode(VL53L3A2_DEV_BOTTOM, (VL53LX_OffsetCorrectionModes)VL53LX_OFFSETCORRECTIONMODE_PERVCSEL);
		// setXTalkCompensation(VL53L3A2_DEV_BOTTOM, 1);
	}

	/*
	 * LM background task
	 */
	void MX_TOF_Process(void *_htim3, void *_hi2c3)
	{
		htim3 = *(TIM_HandleTypeDef *)_htim3;
		hi2c3 = *(I2C_HandleTypeDef *)_hi2c3;

		// I2C slave stuff
		HAL_StatusTypeDef status = HAL_ERROR;

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

					start_sensor(VL53L3A2_DEV_TOP);
					start_sensor(VL53L3A2_DEV_BOTTOM);

					// PWM timer starten
					HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
				}


				// Resultaten opvragen sensoren
				getResult(VL53L3A2_DEV_LEFT, Result);
				dis0 = getDistance(VL53L3A2_DEV_LEFT, Result);

				// Resultaten opvragen sensoren
				getResult(VL53L3A2_DEV_RIGHT, Result);
				dis2 = getDistance(VL53L3A2_DEV_RIGHT, Result);

				getResult(VL53L3A2_DEV_TOP, Result);
				dis3 = getDistance(VL53L3A2_DEV_TOP, Result);

				getResult(VL53L3A2_DEV_BOTTOM, Result);
				dis4 = getDistance(VL53L3A2_DEV_BOTTOM, Result);
			}
			else
			{
				if (hasStarted)
				{
					hasStarted = false;
					stop_sensor(VL53L3A2_DEV_LEFT);
					stop_sensor(VL53L3A2_DEV_RIGHT);

					stop_sensor(VL53L3A2_DEV_TOP);
					stop_sensor(VL53L3A2_DEV_BOTTOM);

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
			int sta3 = (int)Result[VL53L3A2_DEV_TOP].ZoneResult[0].Status[0];
			int sta4 = (int)Result[VL53L3A2_DEV_BOTTOM].ZoneResult[0].Status[0];

			int obj0 = (int)Result[VL53L3A2_DEV_LEFT].ZoneResult[0].NumberOfTargets;
			int obj1 = (int)Result[VL53L3A2_DEV_CENTER].ZoneResult[0].NumberOfTargets;
			int obj2 = (int)Result[VL53L3A2_DEV_RIGHT].ZoneResult[0].NumberOfTargets;
			int obj3 = (int)Result[VL53L3A2_DEV_TOP].ZoneResult[0].NumberOfTargets;
			int obj4 = (int)Result[VL53L3A2_DEV_BOTTOM].ZoneResult[0].NumberOfTargets;

			printf("left: %5d obj: %1d sta: %2d \t center: %5d obj: %1d sta: %2d \t right: %5d obj: %d sta: %2d \t top: %5d obj: %d sta: %2d \t bottom: %5d obj: %d sta: %2d", dis0, obj0, sta0, dis1, obj1, sta1, dis2, obj2, sta2, dis3, obj3, sta3, dis4, obj4, sta4);
			printf("\r\n");

			// Kijken ofdat er een dimming commando aanwezig is
			gestureDimming = CheckDimmingCommand(&gestureDimming, &objectPresent, &dis1, &sta1);

			// Wanneer er geen dimming commando aanwezig is dan kijken we of dat er een Right Left beweging aanwezig is
			if (!gestureDimming)
				gestureRL = CheckGestureRL(&gestureRL, &objectPresent, Result);

			// Wanneer er geen dimming commando aanwezig is dan kijken we of dat er een Left Right beweging aanwezig is
			if (!gestureDimming)
				gestureLR = CheckGestureLR(&gestureLR, &objectPresent, Result);

			// Wanneer er geen dimming commando aanwezig is dan kijken we of dat er een Down Up beweging aanwezig is
			if (!gestureDimming)
				gestureDU = CheckGestureDU(&gestureDU, &objectPresent, Result);

			// Wanneer er geen dimming commando aanwezig is dan kijken we of dat er een Down Up beweging aanwezig is
			if (!gestureDimming)
				gestureUD = CheckGestureUD(&gestureUD, &objectPresent, Result);

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
				// printf("gestureCommand RL: %d \r\n", gestureRL);
				commando = RL;
			}

			// Het commando LR activeren
			if (gestureLR && !prevGestureLR)
			{
				prevGestureLR = gestureLR;
				// printf("gestureCommand LR: %d \r\n", gestureLR);
				commando = LR;
			}

			// Het commando DU activeren
			if (gestureDU && !prevGestureDU)
			{
				prevGestureDU = gestureDU;
				// printf("gestureCommand DU: %d \r\n", gestureDU);
				commando = DU;
			}

			// Het commando UD activeren
			if (gestureUD && !prevGestureUD)
			{
				prevGestureUD = gestureUD;
				// printf("gestureCommand UD: %d \r\n", gestureUD);
				commando = UD;
			}

			prevGestureRL = gestureRL; // fix debouncing van gestureRL
			prevGestureLR = gestureLR; // fix debouncing van gestureLR
			prevGestureDU = gestureDU; // fix debouncing van gestureDU
			prevGestureUD = gestureUD; // fix debouncing van gestureUD

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

			// I2C Slave spelen zonder delay
			HAL_I2C_Slave_Receive_IT(&hi2c3, &buf, sizeof(buf));
			
			
			//HAL_Delay(30);
		}
	}

	static void MX_53L3A2_MultiSensorRanging_Init(void)
	{
		uint8_t device;
		uint16_t i2c_addr;
		uint32_t id;

		/* Initialize Virtual COM Port */
		BSP_COM_Init(COM1);

		// printf("53L3A2 Gesture Control\r\n");

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

			/* left: 0x54, center: 0x56, right: 0x58,  */
			i2c_addr = (RANGING_SENSOR_VL53L3CX_ADDRESS + (device + 1) * 2);
			// printf(i2c_addr);
			VL53L3A2_RANGING_SENSOR_SetAddress(device, i2c_addr);

			/* check the communication with the device reading the ID */
			VL53L3A2_RANGING_SENSOR_ReadID(device, &id);
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
			while (1)
				;
	}

	static void stop_sensor(uint8_t sensor)
	{
		status = VL53L3A2_RANGING_SENSOR_Stop(sensor);
		if (status != BSP_ERROR_NONE)
			while (1)
				;
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

	void HAL_I2C_SlaveRxCpltCallback(I2C_HandleTypeDef *hi2c)
	{
		HAL_I2C_Slave_Transmit(&hi2c3, &commando, sizeof(commando), 50);
	}

#ifdef __cplusplus
}
#endif
