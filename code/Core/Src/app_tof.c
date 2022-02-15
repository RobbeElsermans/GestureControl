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
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "app_tof.h"
#include "main.h"
#include <stdio.h>
#include "53l3a2_ranging_sensor.h"
#include "stm32f4xx_nucleo.h"
#include "stdbool.h" //Nodig om bool te kunnen gebruiken
/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#define POLLING_PERIOD (100U) /* milliseconds */

/* Private variables ---------------------------------------------------------*/
static int32_t status = 0;
static uint8_t ToF_Present[RANGING_SENSOR_INSTANCES_NBR] = {0};
volatile uint8_t ToF_EventDetected = 0;



static const char *TofDevStr[] =
{
  [VL53L3A2_DEV_LEFT] = "LEFT",
  [VL53L3A2_DEV_CENTER] = "CENTER",
  [VL53L3A2_DEV_RIGHT] = "RIGHT"
};

/* Private function prototypes -----------------------------------------------*/
static void MX_53L3A2_MultiSensorRanging_Init(void);
static void MX_53L3A2_MultiSensorRanging_Process(void);
static void print_result(RANGING_SENSOR_Result_t *Result);
static void start_sensor(uint8_t sensor);
static void stop_sensor(uint8_t sensor);

void MX_TOF_Init(void)
{
  /* USER CODE BEGIN SV */

  /* USER CODE END SV */

  /* USER CODE BEGIN TOF_Init_PreTreatment */

  /* USER CODE END TOF_Init_PreTreatment */

  /* Initialize the peripherals and the TOF components */

  MX_53L3A2_MultiSensorRanging_Init();

  /* USER CODE BEGIN TOF_Init_PostTreatment */

  /* USER CODE END TOF_Init_PostTreatment */
}

/*
 * LM background task
 */
void MX_TOF_Process(void)
{
  /* USER CODE BEGIN TOF_Process_PreTreatment */
	RANGING_SENSOR_Result_t Result;

	  int preDis1 = 5000;
	  int dis1 = 0;
	  int treshhold = 1000;
	  int minDistanceObject = 500;
	  bool ObjectPresent = false;
	  int timeOutmeasurment = 2000; //2 seconden


	  uint8_t i;

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

	  //Enkel de 1ste sensor (Center) opstarten
	  /*	Hier zeggen we welk profiel we willen gebruiken
	   * 	bv.
	   *
	   */

	   start_sensor(VL53L3A2_DEV_CENTER);

  /* USER CODE END TOF_Process_PreTreatment */

  //MX_53L3A2_MultiSensorRanging_Process();

  /* USER CODE BEGIN TOF_Process_PostTreatment */
	  while(1){
		  VL53L3A2_RANGING_SENSOR_GetDistance(VL53L3A2_DEV_CENTER, &Result);
		  dis1 = (long)Result.ZoneResult[0].Distance[0];

		  //Bug van 1ste meeting dat deze fout is (Een te hoge waarden)
		  if(dis1 >= 17760520)
		  {
			  HAL_Delay(4);
			  VL53L3A2_RANGING_SENSOR_GetDistance(VL53L3A2_DEV_CENTER, &Result);
			  dis1 = (long)Result.ZoneResult[0].Distance[0];
		  }

		  /*	Als de waarde zakt t.o.v. de vorige waarden m.b.v. een treshhold en het object bevind zich op de minimum afstand.
		   * 	We kijken ook ofdat de Status niet = 12 (12 staat voor dat de sensor iets kan detecteren maar het signaal is te zwak dus te ver weg))
		   *
		   */
		  if(preDis1 - dis1 > treshhold && (dis1 <= minDistanceObject) && (uint8_t)Result.ZoneResult[0].Status[0] != 12){
			  //Persoon naderd en staat dicht genoeg
			  //Start andere sensoren ook op
			  ObjectPresent = true;
			  start_sensor(VL53L3A2_DEV_LEFT);
			  start_sensor(VL53L3A2_DEV_RIGHT);

		  }
		  else if (preDis1 - dis1 > treshhold){
			  //Wat dichter komen
			  //Zolang de distance niet voldoet aan minDistanceObject blijven meten.
			  //De meting stoppen na een bepaalde timeout
			  HAL_Delay(500);
		  }
		  else if( (preDis1 + dis1) > treshhold && ObjectPresent){
			  ObjectPresent = false;
			  stop_sensor(VL53L3A2_DEV_LEFT);
			  stop_sensor(VL53L3A2_DEV_RIGHT);
			  HAL_Delay(10);

		  }

		  //Ticks
		  // long x = HAL_GetTick();
		  //printf("Ticks: %ld ", x);

		  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, ObjectPresent);
		  HAL_GPIO_WritePin(L_O_GPIO_Port, L_O_Pin, ObjectPresent);

		  preDis1 = dis1;
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
    if (ToF_Present[device] == 0) continue;

    /* left: 0x54, center: 0x56, right: 0x58 */
    i2c_addr = (RANGING_SENSOR_VL53L3CX_ADDRESS + (device + 1) * 2);
    VL53L3A2_RANGING_SENSOR_SetAddress(device, i2c_addr);

    /* check the communication with the device reading the ID */
    VL53L3A2_RANGING_SENSOR_ReadID(device, &id);
    printf("ToF sensor %d - ID: %04lX\r\n", device, (unsigned long)id);
  }
}

static void MX_53L3A2_MultiSensorRanging_Process(void)
{
	uint8_t i;
	RANGING_SENSOR_Result_t Result;

  while (1)
  {
    /* polling mode */
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

static void start_sensor(uint8_t sensor){
	RANGING_SENSOR_ProfileConfig_t Profile;

	Profile.RangingProfile = RS_MULTI_TARGET_MEDIUM_RANGE;
	Profile.TimingBudget = 30; /* 16 ms < TimingBudget < 500 ms */
	Profile.Frequency = 0; /* not necessary in simple ranging */
	Profile.EnableAmbient = 1; /* Enable: 1, Disable: 0 */
	Profile.EnableSignal = 1; /* Enable: 1, Disable: 0 */

	VL53L3A2_RANGING_SENSOR_ConfigProfile(sensor, &Profile);
	status = VL53L3A2_RANGING_SENSOR_Start(sensor, RS_MODE_BLOCKING_CONTINUOUS);
    if (status != BSP_ERROR_NONE)
    {
    	printf("VL53L3A2_RANGING_SENSOR_Start failed for sensor %s \r\n", TofDevStr[sensor]);
		while(1);
    }
    else
	{
    	printf("sensor %s\t opgestart \r\n", TofDevStr[sensor]);
	}
}

static void stop_sensor(uint8_t sensor){
	status = VL53L3A2_RANGING_SENSOR_Stop(sensor);
    if (status != BSP_ERROR_NONE)
    {
    	printf("VL53L3A2_RANGING_SENSOR_Stop failed\r\n");
		while(1);
    }
    else
	{
    	printf("sensor %s\t afgezet \r\n", TofDevStr[sensor]);
	}
}

#ifdef __cplusplus
}
#endif
