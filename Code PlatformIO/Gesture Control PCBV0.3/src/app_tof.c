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
#include "GestureDetectUD.h"	  //Bevat methode om gesture Onder Boven te herkennen.

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

	int sta0 = 0;
	int sta1 = 0;
	int sta2 = 0;
	int sta3 = 0;
	int sta4 = 0;

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

	// Timer Ticks
	static float timerTicks = 0;
	static uint8_t timerTicksCount = 0;
	int timeTicks = 0;

	bool toggleReading = false;

	RANGING_SENSOR_Result_t volatile _result[RANGING_SENSOR_INSTANCES_NBR]; // Niet gebruiken
	bool volatile isStarted0 = false;
	bool isStarted1 = false;
	bool isStarted2 = false;
	bool isStarted3 = false;
	bool isStarted4 = false;

	bool volatile isReady0 = false;
	bool volatile isReady1 = false;
	bool volatile isReady2 = false;
	bool volatile isReady3 = false;
	bool volatile isReady4 = false;

	int8_t buf;

	/* Intern functions ----------------------------------------------------------*/
	static void start_sensor(uint8_t sensor);
	static void stop_sensor(uint8_t sensor);
	static void getResult(uint8_t sensor, RANGING_SENSOR_Result_t *result);
	static long getDistance(uint8_t sensor, RANGING_SENSOR_Result_t *result, long prevDist);
	static void MX_53L3A2_MultiSensorRanging_Init(void);
	static void checkSensorReady(bool *_hasStarted, bool volatile *_isReady, uint8_t sensor, RANGING_SENSOR_Result_t *result);

	void MX_TOF_Init(void)
	{
		MX_53L3A2_MultiSensorRanging_Init();

		initObjectPresent(-1, -1, -1);

		// // Calibraties uitvoeren
		// VL53LX_CalibrationData_t callData[RANGING_SENSOR_INSTANCES_NBR];

		// RefSpadCal(VL53L3A2_DEV_LEFT);
		// RefSpadCal(VL53L3A2_DEV_CENTER);
		// RefSpadCal(VL53L3A2_DEV_RIGHT);
		// RefSpadCal(VL53L3A2_DEV_TOP);
		// RefSpadCal(VL53L3A2_DEV_BOTTOM);

		// callData[VL53L3A2_DEV_LEFT] = getCalibrationData(VL53L3A2_DEV_LEFT);
		// callData[VL53L3A2_DEV_CENTER] = getCalibrationData(VL53L3A2_DEV_CENTER);
		// callData[VL53L3A2_DEV_RIGHT] = getCalibrationData(VL53L3A2_DEV_RIGHT);
		// callData[VL53L3A2_DEV_TOP] = getCalibrationData(VL53L3A2_DEV_TOP);
		// callData[VL53L3A2_DEV_BOTTOM] = getCalibrationData(VL53L3A2_DEV_BOTTOM);

		// // // Callibratie van crosstalk (coverglas)
		// // xTalkCal(VL53L3A2_DEV_LEFT);
		// // xTalkCal(VL53L3A2_DEV_CENTER);
		// // xTalkCal(VL53L3A2_DEV_RIGHT);
		// // xTalkCal(VL53L3A2_DEV_TOP);
		// // xTalkCal(VL53L3A2_DEV_BOTTOM);

		// // // De offset bepalen zodat deze juist is is.
		// // offsetPerVcselCal(VL53L3A2_DEV_LEFT, 600);
		// // offsetPerVcselCal(VL53L3A2_DEV_CENTER, 600);
		// // offsetPerVcselCal(VL53L3A2_DEV_RIGHT, 600);
		// // offsetPerVcselCal(VL53L3A2_DEV_TOP, 600);
		// // offsetPerVcselCal(VL53L3A2_DEV_BOTTOM, 600);

		// // // Waardes opvragen
		// // callData[VL53L3A2_DEV_LEFT] = getCalibrationData(VL53L3A2_DEV_LEFT);
		// // callData[VL53L3A2_DEV_CENTER] = getCalibrationData(VL53L3A2_DEV_CENTER);
		// // callData[VL53L3A2_DEV_RIGHT] = getCalibrationData(VL53L3A2_DEV_RIGHT);
		// // callData[VL53L3A2_DEV_TOP] = getCalibrationData(VL53L3A2_DEV_TOP);
		// // callData[VL53L3A2_DEV_BOTTOM] = getCalibrationData(VL53L3A2_DEV_BOTTOM);

		// setCalibrationData(VL53L3A2_DEV_LEFT, callData[VL53L3A2_DEV_LEFT]);
		// setCalibrationData(VL53L3A2_DEV_CENTER, callData[VL53L3A2_DEV_CENTER]);
		// setCalibrationData(VL53L3A2_DEV_RIGHT, callData[VL53L3A2_DEV_RIGHT]);
		// setCalibrationData(VL53L3A2_DEV_TOP, callData[VL53L3A2_DEV_TOP]);
		// setCalibrationData(VL53L3A2_DEV_BOTTOM, callData[VL53L3A2_DEV_BOTTOM]);

		// setOffsetCorrectionMode(VL53L3A2_DEV_LEFT, (VL53LX_OffsetCorrectionModes)VL53LX_OFFSETCORRECTIONMODE_PERVCSEL);
		// setXTalkCompensation(VL53L3A2_DEV_LEFT, 1);

		// setOffsetCorrectionMode(VL53L3A2_DEV_CENTER, (VL53LX_OffsetCorrectionModes)VL53LX_OFFSETCORRECTIONMODE_PERVCSEL);
		// setXTalkCompensation(VL53L3A2_DEV_CENTER, 1);

		// setOffsetCorrectionMode(VL53L3A2_DEV_RIGHT, (VL53LX_OffsetCorrectionModes)VL53LX_OFFSETCORRECTIONMODE_PERVCSEL);
		// setXTalkCompensation(VL53L3A2_DEV_RIGHT, 1);

		// setOffsetCorrectionMode(VL53L3A2_DEV_TOP, (VL53LX_OffsetCorrectionModes)VL53LX_OFFSETCORRECTIONMODE_PERVCSEL);
		// // setXTalkCompensation(VL53L3A2_DEV_TOP, 1);

		// setOffsetCorrectionMode(VL53L3A2_DEV_BOTTOM, (VL53LX_OffsetCorrectionModes)VL53LX_OFFSETCORRECTIONMODE_PERVCSEL);
		// // setXTalkCompensation(VL53L3A2_DEV_BOTTOM, 1);
	}

	void MX_TOF_Process(void *_htim3, void *_hi2c3)
	{
		// htim3 = *(TIM_HandleTypeDef *)_htim3;
		hi2c3 = *(I2C_HandleTypeDef *)_hi2c3;

		// I2C slave stuff
		HAL_StatusTypeDef status = HAL_ERROR;

		HAL_GPIO_WritePin(LED_0_GPIO_Port, LED_0_Pin, 1);
		start_sensor(VL53L3A2_DEV_CENTER);
		start_sensor(VL53L3A2_DEV_LEFT);
		start_sensor(VL53L3A2_DEV_RIGHT);
		start_sensor(VL53L3A2_DEV_TOP);
		start_sensor(VL53L3A2_DEV_BOTTOM);
		
		//HAL_Delay(2000);

		int8_t sta4 = 0;

		while(1){
			//getResult(VL53L3A2_DEV_CENTER, Result);
			//HAL_Delay(20);
			checkSensorReady(&isStarted0, &isReady0, VL53L3A2_DEV_CENTER, Result);
			checkSensorReady(&isStarted1, &isReady1, VL53L3A2_DEV_LEFT, Result);
			checkSensorReady(&isStarted2, &isReady2, VL53L3A2_DEV_RIGHT, Result);
			checkSensorReady(&isStarted3, &isReady3, VL53L3A2_DEV_TOP, Result);
			checkSensorReady(&isStarted4, &isReady4, VL53L3A2_DEV_BOTTOM, Result);
			//HAL_Delay(20);
			dis0 = (long)Result[VL53L3A2_DEV_CENTER].ZoneResult[0].Distance[0];
			dis1 = (long)Result[VL53L3A2_DEV_LEFT].ZoneResult[0].Distance[0];
			dis2 = (long)Result[VL53L3A2_DEV_RIGHT].ZoneResult[0].Distance[0];
			dis3 = (long)Result[VL53L3A2_DEV_TOP].ZoneResult[0].Distance[0];
			dis4 = (long)Result[VL53L3A2_DEV_BOTTOM].ZoneResult[0].Distance[0];

			sta0 = (long)Result[VL53L3A2_DEV_CENTER].ZoneResult[0].Status[0];
			sta1 = (long)Result[VL53L3A2_DEV_LEFT].ZoneResult[0].Status[0];
			sta2 = (long)Result[VL53L3A2_DEV_RIGHT].ZoneResult[0].Status[0];
			sta3 = (long)Result[VL53L3A2_DEV_TOP].ZoneResult[0].Status[0];
			sta4 = (long)Result[VL53L3A2_DEV_BOTTOM].ZoneResult[0].Status[0];

			//HAL_Delay(500);
			HAL_GPIO_TogglePin(LED_2_GPIO_Port, LED_2_Pin);
			printf("dis0: %4d, %2d \tdis1: %4d, %2d \tdis2: %4d, %2d \tdis3: %4d, %2d \tdis4: %4d, %2d \r\n",dis0,sta0,dis1,sta1,dis2,sta2,dis3,sta3,dis4,sta4);
			HAL_Delay(200);
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

			/* left: 0x54, center: 0x56, right: 0x58,  */
			i2c_addr = (RANGING_SENSOR_VL53L3CX_ADDRESS + (device + 1) * 2);
			// printf(i2c_addr);
			VL53L3A2_RANGING_SENSOR_SetAddress(device, i2c_addr);

			/* check the communication with the device reading the ID */
			VL53L3A2_RANGING_SENSOR_ReadID(device, &id);
			printf("%d\r\n", device);
		}
	}

	static void start_sensor(uint8_t sensor)
	{

		RANGING_SENSOR_ProfileConfig_t Profile;

		Profile.RangingProfile = RS_MULTI_TARGET_MEDIUM_RANGE;
		Profile.TimingBudget = 100; /* 16 ms < TimingBudget < 500 ms */
		Profile.Frequency = 0;		/* not necessary in simple ranging */
		Profile.EnableAmbient = 1;	/* Enable: 1, Disable: 0 */
		Profile.EnableSignal = 1;	/* Enable: 1, Disable: 0 */

		VL53L3A2_RANGING_SENSOR_ConfigProfile(sensor, &Profile);
		status = VL53L3A2_RANGING_SENSOR_Start(sensor, VL53L3CX_MODE_ASYNC_CONTINUOUS);
		// status = VL53L3A2_RANGING_SENSOR_Start(sensor, VL53L3CX_MODE_BLOCKING_CONTINUOUS);

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

	static void checkSensorReady(bool *_hasStarted, bool volatile *_isReady, uint8_t sensor, RANGING_SENSOR_Result_t *result)
	{
		if (*_hasStarted && *_isReady)
		{
			*_isReady = false;
			getResult(sensor, result);
			//printf("getResult \r\n");
		}
		else if (!*_hasStarted)
		{
			*_hasStarted = true;
			getResult(sensor, result);
			//printf("trash \r\n");
		}
	}

	static void getResult(uint8_t sensor, RANGING_SENSOR_Result_t *result)
	{
		VL53L3A2_RANGING_SENSOR_GetDistance(sensor, &result[sensor]);

		// Bug van 1ste meeting dat deze fout is (Een te hoge waarden)
		if ((long)result[sensor].ZoneResult[0].Distance[0] >= 17760520)
		{
			HAL_Delay(2);
			VL53L3A2_RANGING_SENSOR_GetDistance(sensor, &result[sensor]);
		}
	}

	static long getDistance(uint8_t sensor, RANGING_SENSOR_Result_t *result, long prevDist)
	{
		long distance = prevDist;

		if (!result[sensor].ZoneResult[0].Status[0])
			distance = (long)result[sensor].ZoneResult[0].Distance[0];

		return distance;
	}

	void HAL_I2C_SlaveRxCpltCallback(I2C_HandleTypeDef *hi2c)
	{
		HAL_I2C_Slave_Transmit(&hi2c3, &commando, sizeof(commando), 50);
	}

	void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
	{
		if (GPIO_Pin == GPIOI_0_Pin)
		{
			isReady0 = true;
		}

		if (GPIO_Pin == GPIOI_1_Pin)
		{
			isReady1 = true;
		}

		if (GPIO_Pin == GPIOI_2_Pin)
		{
			isReady2 = true;
		}

		if (GPIO_Pin == GPIOI_3_Pin)
		{
			isReady3 = true;
		}

		if (GPIO_Pin == GPIOI_4_Pin)
		{
			isReady4 = true;
		}
	}

#ifdef __cplusplus
}
#endif
