/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
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
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stm32f3xx_hal.h"
#include <sys/unistd.h> // STDOUT_FILENO, STDERR_FI
#include <errno.h>
#include "stdbool.h"
#include "vl53lx_api.h"
#include "calibrationData.h" //bevat methodes en instellingen om de sensoren te calibreren.
#include "GestureDetectObject.h"
#include "GestureDetect.h"
#include "SensorFunctions.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

// Toggle for data collection
//#define DATACOLLECTION

// Toggle voor calibrate
//#define CALIBRATE

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
volatile bool isReady[amountSensor] = {false, false, false};
volatile bool hasRead[amountSensor] = {false, false, false};

// detectie distance
int16_t maxDis = 300;

#ifdef DATACOLLECTION
long timerDataCollection = 0;
int timerDataCollectionTimeout = 20; // aantal milliseconden per meeting
#endif

// Aanmaken sensor definities
//
Sensor_Definition_t center = {XSHUT_2, 0};
Sensor_Definition_t left = {XSHUT_3, 1};
Sensor_Definition_t right = {XSHUT_1, 2};

// Resultaat van de meetingen die de afstand, status en timestamp bevat voor amountSensorUsed aantal keer aangemaakt
Resultaat_t resultaat[amountSensorUsed];

bool objectPresent = false;
bool prevObjectPresent = false;

// Commando enum waarmee we de commando's opslaan
commands commando = NONE;

// Timer die het commando voor timerCommandTimeout seconden aanhoud
static float timerCommand = 0;
static bool timerCommandSet = false;   // Start in false state
static int timerCommandTimeout = 2000; // 2 seconden

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{
  /* USER CODE BEGIN 1 */
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
  // Define de sensor objecten amountSensorUsed keer.
  VL53L3CX_Object_t sensor[amountSensorUsed];
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
#ifdef env1
  MX_I2C3_Init();
#endif
#ifdef env2
  MX_I2C2_Init();
#endif
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
  HAL_GPIO_WritePin(XSHUT_0_GPIO_Port, XSHUT_0_Pin, 0);
  HAL_GPIO_WritePin(XSHUT_1_GPIO_Port, XSHUT_1_Pin, 0);
  HAL_GPIO_WritePin(XSHUT_2_GPIO_Port, XSHUT_2_Pin, 0);
  HAL_GPIO_WritePin(XSHUT_3_GPIO_Port, XSHUT_3_Pin, 0);
  HAL_GPIO_WritePin(XSHUT_4_GPIO_Port, XSHUT_4_Pin, 0);

  HAL_Delay(20);

  // while(1)
  // {
  //   HAL_GPIO_TogglePin(LED_0_GPIO_Port, LED_0_Pin);
  //   HAL_Delay(1000);
  // }

  // Zal switchen tussen links en rechts sensor telkens bij een nieuwe loop
  bool toggler = false;

  // Omdat we in RAM de objecten aanmaken (en niet initializeren) gaat er random waardes insteken.
  // Isinitialized moet 0 zijn om verder te kunnen.
  sensor[left.id].IsInitialized = 0;
  sensor[center.id].IsInitialized = 0;
  sensor[right.id].IsInitialized = 0;

  CUSTOM_VL53L3CX_I2C_Init();

  Init_Sensor(&sensor[center.id], center.gpioPin);
  Init_Sensor(&sensor[left.id], left.gpioPin);
  Init_Sensor(&sensor[right.id], right.gpioPin);

#ifndef CALIBRATE
  if (HAL_GPIO_ReadPin(SW_1_GPIO_Port, SW_1_Pin))
#else
  if (true)
#endif
  {
    // VL53LX_CalibrationData_t callData[amountSensorUsed];

    // printf("Calibrating in 20 seconds... \r\n\r\n");
    // for (uint8_t i = 0; i < 20; i++)
    // {
    //   HAL_GPIO_TogglePin(LED_0_GPIO_Port, LED_0_Pin);
    //   HAL_Delay(1000);
    // }
    // HAL_GPIO_WritePin(LED_0_GPIO_Port, LED_0_Pin, 0);

    // printf("Sensor %2d\r\n", center.gpioPin);
    // RefSpadCal(&sensor[center.id]);
    // RefSpadCal(&sensor[left.id]);
    // RefSpadCal(&sensor[right.id]);
    // // HAL_GPIO_WritePin(LED_4_GPIO_Port, LED_4_Pin, 1);
    // printf("refspad\r\n");
    // xTalkCal(&sensor[center.id]);
    // xTalkCal(&sensor[left.id]);
    // xTalkCal(&sensor[right.id]);
    // // HAL_GPIO_WritePin(LED_3_GPIO_Port, LED_3_Pin, 1);
    // printf("xtalk\r\n");
    // offsetPerVcselCal(&sensor[center.id], 600);
    // HAL_Delay(2);
    // offsetPerVcselCal(&sensor[left.id], 600);
    // HAL_Delay(2);
    // offsetPerVcselCal(&sensor[right.id], 600);
    // // HAL_GPIO_WritePin(LED_2_GPIO_Port, LED_2_Pin, 1);
    // callData[center.id] = getCalibrationData(&sensor[center.id]);
    // callData[left.id] = getCalibrationData(&sensor[left.id]);
    // callData[right.id] = getCalibrationData(&sensor[right.id]);

    // for (uint8_t i = 0; i < 3; i++)
    // {
    //   /* code */
    //   printf("sensor: %2d\r\n", i);
    //   printf("XTalk_kps\r\n");
    //   for (uint8_t j = 0; j < 6; j++)
    //   {
    //     printf(j);
    //     printf("%2d: %5d \r\n", j, callData[i].algo__xtalk_cpo_HistoMerge_kcps[j]);
    //   }
    //   printf("\r\n");
    //   printf("xtalk_bin_data\r\n");
    //   for (uint8_t j = 0; j < 12; j++)
    //   {
    //     printf(j);
    //     printf("%2d: %5d \r\n", j, callData[i].xtalkhisto.xtalk_shape.bin_data[j]);
    //   }
    //   printf("\r\n");
    //   printf("zero_distance_phase: %5d\r\n", callData[i].xtalkhisto.xtalk_shape.zero_distance_phase);
    //   printf("phasecal_result__reference_phase: %5d\r\n", callData[i].xtalkhisto.xtalk_shape.phasecal_result__reference_phase);
    //   printf("cal_config__vcsel_start: %5d\r\n", callData[i].xtalkhisto.xtalk_shape.cal_config__vcsel_start);
    //   printf("zone_id: %5d\r\n", callData[i].xtalkhisto.xtalk_shape.zone_id);
    //   printf("vcsel_width: %5d\r\n", callData[i].xtalkhisto.xtalk_shape.vcsel_width);
    //   printf("VL53LX_p_015: %5d\r\n", callData[i].xtalkhisto.xtalk_shape.VL53LX_p_015);
    //   printf("\r\n");
    //   printf("short_a_offset_mm: %5d\r\n", callData[i].per_vcsel_cal_data.short_a_offset_mm);
    //   printf("short_b_offset_mm: %5d\r\n", callData[i].per_vcsel_cal_data.short_b_offset_mm);
    //   printf("medium_a_offset_mm: %5d\r\n", callData[i].per_vcsel_cal_data.medium_a_offset_mm);
    //   printf("medium_b_offset_mm: %5d\r\n", callData[i].per_vcsel_cal_data.medium_b_offset_mm);
    //   printf("long_a_offset_mm: %5d\r\n", callData[i].per_vcsel_cal_data.long_a_offset_mm);
    //   printf("long_b_offset_mm: %5d\r\n", callData[i].per_vcsel_cal_data.long_b_offset_mm);
    //   printf("\r\n");
    //   printf("global_config__spad_enables_ref_0: %5d\r\n", callData[i].customer.global_config__spad_enables_ref_0);
    //   printf("global_config__spad_enables_ref_1: %5d\r\n", callData[i].customer.global_config__spad_enables_ref_1);
    //   printf("global_config__spad_enables_ref_2: %5d\r\n", callData[i].customer.global_config__spad_enables_ref_2);
    //   printf("global_config__spad_enables_ref_3: %5d\r\n", callData[i].customer.global_config__spad_enables_ref_3);
    //   printf("global_config__spad_enables_ref_4: %5d\r\n", callData[i].customer.global_config__spad_enables_ref_4);
    //   printf("global_config__spad_enables_ref_5: %5d\r\n", callData[i].customer.global_config__spad_enables_ref_5);
    //   printf("ref_spad_man__num_requested_ref_spads: %5d\r\n", callData[i].customer.ref_spad_man__num_requested_ref_spads);
    //   printf("ref_spad_man__ref_location: %5d\r\n", callData[i].customer.ref_spad_man__ref_location);
    //   printf("algo__crosstalk_compensation_plane_offset_kcps: %5d\r\n", callData[i].customer.algo__crosstalk_compensation_plane_offset_kcps);
    //   printf("ref_spad_char__total_rate_target_mcps: %5d\r\n", callData[i].customer.ref_spad_char__total_rate_target_mcps);
    //   printf("mm_config__inner_offset_mm: %5d\r\n", callData[i].customer.mm_config__inner_offset_mm);
    //   printf("mm_config__outer_offset_mm: %5d\r\n", callData[i].customer.mm_config__outer_offset_mm);
    // }
    // HAL_GPIO_WritePin(LED_1_GPIO_Port, LED_1_Pin, 1);

    // setCalibrationData(&sensor[center.id], center.id, &callData[center.id]);
    // setCalibrationData(&sensor[left.id], center.id, &callData[left.id]);
    // setCalibrationData(&sensor[right.id], center.id, &callData[right.id]);

    // setOffsetCorrectionMode(&sensor[center.id], (VL53LX_OffsetCorrectionModes)VL53LX_OFFSETCORRECTIONMODE_PERVCSEL);
    // setXTalkCompensation(&sensor[center.id], 1);
    // setOffsetCorrectionMode(&sensor[left.id], (VL53LX_OffsetCorrectionModes)VL53LX_OFFSETCORRECTIONMODE_PERVCSEL);
    // setXTalkCompensation(&sensor[left.id], 1);
    // setOffsetCorrectionMode(&sensor[right.id], (VL53LX_OffsetCorrectionModes)VL53LX_OFFSETCORRECTIONMODE_PERVCSEL);
    // setXTalkCompensation(&sensor[right.id], 1);

    getCalibrate(&sensor[center.id], center.id);
    getCalibrate(&sensor[left.id], left.id);
    getCalibrate(&sensor[right.id], right.id);

    VL53L3CX_Result_t tempResult;
    Start_Sensor(&sensor[center.id], center.gpioPin);
    Start_Sensor(&sensor[left.id], left.gpioPin);
    Start_Sensor(&sensor[right.id], right.gpioPin);
    while (1)
    {
      if (Sensor_Ready(&sensor[center.id], center.gpioPin, (uint8_t *)isReady))
      {
        isReady[center.id] = false;
        VL53L3CX_GetDistance(&sensor[center.id], &tempResult);
        // HAL_Delay(2);
        resultaat[center.id].distance = (long)tempResult.ZoneResult[0].Distance[0];
        resultaat[center.id].status = tempResult.ZoneResult[0].Status[0];
        // HAL_Delay(2);
      }
      if (Sensor_Ready(&sensor[left.id], left.gpioPin, (uint8_t *)isReady))
      {
        isReady[left.id] = false;
        VL53L3CX_GetDistance(&sensor[left.id], &tempResult);
        // HAL_Delay(2);
        resultaat[left.id].distance = (long)tempResult.ZoneResult[0].Distance[0];
        resultaat[left.id].status = tempResult.ZoneResult[0].Status[0];
        // HAL_Delay(2);
      }
      if (Sensor_Ready(&sensor[right.id], right.gpioPin, (uint8_t *)isReady))
      {
        isReady[right.id] = false;
        VL53L3CX_GetDistance(&sensor[right.id], &tempResult);
        HAL_Delay(2);
        resultaat[right.id].distance = (long)tempResult.ZoneResult[0].Distance[0];
        resultaat[right.id].status = tempResult.ZoneResult[0].Status[0];
        HAL_Delay(2);
      }
      HAL_Delay(200);
      printf("left %5d, %2d,center %5d, %2d,right %5d, %2d \r\n", (int)resultaat[left.id].distance, resultaat[left.id].status, (int)resultaat[center.id].distance, resultaat[center.id].status, (int)resultaat[right.id].distance, resultaat[right.id].status);
    }

  }
  else
  {
    // VL53LX_CalibrationData_t callData[amountSensorUsed];
    // callData[center.id] = getCalibrationData(&sensor[center.id]);
    // callData[left.id] = getCalibrationData(&sensor[left.id]);
    // callData[right.id] = getCalibrationData(&sensor[right.id]);

    // setCalibrationData(&sensor[center.id], center.id, &callData[center.id]);
    // setCalibrationData(&sensor[left.id], center.id, &callData[left.id]);
    // setCalibrationData(&sensor[right.id], center.id, &callData[right.id]);

    // setOffsetCorrectionMode(&sensor[center.id], (VL53LX_OffsetCorrectionModes)VL53LX_OFFSETCORRECTIONMODE_PERVCSEL);
    // setXTalkCompensation(&sensor[center.id], 1);
    // setOffsetCorrectionMode(&sensor[left.id], (VL53LX_OffsetCorrectionModes)VL53LX_OFFSETCORRECTIONMODE_PERVCSEL);
    // setXTalkCompensation(&sensor[left.id], 1);
    // setOffsetCorrectionMode(&sensor[right.id], (VL53LX_OffsetCorrectionModes)VL53LX_OFFSETCORRECTIONMODE_PERVCSEL);
    // setXTalkCompensation(&sensor[right.id], 1);

    // // Smudge detectie
    // VL53LX_SmudgeCorrectionEnable(&sensor[center.id], VL53LX_SMUDGE_CORRECTION_SINGLE); //Deze sensor zal bij elke meeting de smudge toepassen
    // VL53LX_SmudgeCorrectionEnable(&sensor[left.id], VL53LX_SMUDGE_CORRECTION_CONTINUOUS); // Deze sensor zal bij elke start de correctie toepassen
    // VL53LX_SmudgeCorrectionEnable(&sensor[right.id], VL53LX_SMUDGE_CORRECTION_SINGLE); //Deze sensor zal bij elke start de correctie toepassen
    setCalibrate(&sensor[center.id], center.id);;
    setCalibrate(&sensor[left.id], left.id);
    setCalibrate(&sensor[right.id], right.id);
  }

  Start_Sensor(&sensor[left.id], left.gpioPin);
  // Start_Sensor(&sensor[left.id], left.gpioPin);
  // Start_Sensor(&sensor[right.id], right.gpioPin);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  initObjectPresent(-1, -1, -1);

  while (1)
  {
    VL53L3CX_Result_t tempResult;

    if (Sensor_Ready(&sensor[left.id], left.gpioPin, (uint8_t *)isReady))
    {
      isReady[left.id] = false;
      VL53L3CX_GetDistance(&sensor[left.id], &tempResult);
      // HAL_Delay(2);
      if ((long)tempResult.ZoneResult[0].Distance[0] < 3000)
        resultaat[left.id].distance = (long)tempResult.ZoneResult[0].Distance[0];
      resultaat[left.id].status = tempResult.ZoneResult[0].Status[0];
      // HAL_Delay(2);
    }

    if (objectPresent)
    {
      if (Sensor_Ready(&sensor[center.id], center.gpioPin, (uint8_t *)isReady))
      {
        isReady[center.id] = false;
        VL53L3CX_GetDistance(&sensor[center.id], &tempResult);
        // HAL_Delay(2);
        if ((long)tempResult.ZoneResult[0].Distance[0] < 3000)
          resultaat[center.id].distance = (long)tempResult.ZoneResult[0].Distance[0];
        resultaat[center.id].status = tempResult.ZoneResult[0].Status[0];
        // HAL_Delay(2);
      }

      if (Sensor_Ready(&sensor[right.id], right.gpioPin, (uint8_t *)isReady))
      {
        isReady[right.id] = false;
        VL53L3CX_GetDistance(&sensor[right.id], &tempResult);
        // HAL_Delay(2);
        if ((long)tempResult.ZoneResult[0].Distance[0] < 3000)
          resultaat[right.id].distance = (long)tempResult.ZoneResult[0].Distance[0];
        resultaat[right.id].status = tempResult.ZoneResult[0].Status[0];
        // HAL_Delay(2);
      }

      setMeanVal(center.id, resultaat[center.id].distance);
      setMeanVal(right.id, resultaat[right.id].distance);
    }
    else
    {
      long tempTimer = HAL_GetTick();
      while (HAL_GetTick() - tempTimer < 250)
        ;
    }

    setMeanVal(left.id, resultaat[left.id].distance);

    objectPresent = ckeckObjectPresent(&resultaat[left.id], &objectPresent, &resultaat[left.id].distance);
    int dis0 = 0;
    int dis1 = 0;
    int dis2 = 0;
    // Wanneer er geen commando aanwezig is, kijken ofdat er een gesture is
    if (commando == NONE)
    {
      dis0 = getMean(left.id);
      dis1 = getMean(center.id);
      dis2 = getMean(right.id);
      int8_t val = detectgesture(dis0, resultaat[left.id].status, dis1, resultaat[center.id].status, dis2, resultaat[right.id].status);
      if (val != -1)
        commando = val;

      printf("dis0: %5d,dis1: %5d,dis2: %5d \r\n", dis0, dis1, dis2);
    }

    checkResetTimer();

    HAL_GPIO_WritePin(LED_3_GPIO_Port, LED_3_Pin, objectPresent);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

    if (objectPresent && !prevObjectPresent)
    {
      // Opstarten van sensoren
      Start_Sensor(&sensor[center.id], center.gpioPin);
      Start_Sensor(&sensor[right.id], right.gpioPin);
      // printf("Start\r\n");
    }

    if (!objectPresent && prevObjectPresent)
    {
      Stop_Sensor(&sensor[center.id]);
      Stop_Sensor(&sensor[right.id]);
      // printf("Stop\r\n");
    }

    prevObjectPresent = objectPresent;

    /* 	Timer om leds even aan te laten
        Er wordt gekeken wanneer commando veranderd wordt naar alles behalve NONE.
        Dan zetten we een timer
        Wanneer de timer afloopt wordt het commando gereset
      */
    if (!timerCommandSet && commando != NONE)
    {
      timerCommandSet = true;
      timerCommand = HAL_GetTick();
      // printf("command: %2d\r\n", commando);
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
      HAL_GPIO_WritePin(LED_0_GPIO_Port, LED_0_Pin, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(LED_1_GPIO_Port, LED_1_Pin, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(LED_2_GPIO_Port, LED_2_Pin, GPIO_PIN_RESET);
      break;
    case RL:
      HAL_GPIO_WritePin(LED_0_GPIO_Port, LED_0_Pin, GPIO_PIN_SET);
      HAL_GPIO_WritePin(LED_1_GPIO_Port, LED_1_Pin, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(LED_2_GPIO_Port, LED_2_Pin, GPIO_PIN_RESET);
      break;
    case LR:
      HAL_GPIO_WritePin(LED_0_GPIO_Port, LED_0_Pin, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(LED_1_GPIO_Port, LED_1_Pin, GPIO_PIN_SET);
      HAL_GPIO_WritePin(LED_2_GPIO_Port, LED_2_Pin, GPIO_PIN_RESET);
      break;
    case UD:
      HAL_GPIO_WritePin(LED_0_GPIO_Port, LED_0_Pin, GPIO_PIN_SET);
      HAL_GPIO_WritePin(LED_1_GPIO_Port, LED_1_Pin, GPIO_PIN_SET);
      HAL_GPIO_WritePin(LED_2_GPIO_Port, LED_2_Pin, GPIO_PIN_RESET);
      break;
    case DU:
      HAL_GPIO_WritePin(LED_0_GPIO_Port, LED_0_Pin, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(LED_1_GPIO_Port, LED_1_Pin, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(LED_2_GPIO_Port, LED_2_Pin, GPIO_PIN_SET);
      break;
    case DIM:
      HAL_GPIO_WritePin(LED_0_GPIO_Port, LED_0_Pin, GPIO_PIN_SET);
      HAL_GPIO_WritePin(LED_1_GPIO_Port, LED_1_Pin, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(LED_2_GPIO_Port, LED_2_Pin, GPIO_PIN_SET);
      break;

    default:
      HAL_GPIO_WritePin(LED_0_GPIO_Port, LED_0_Pin, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(LED_1_GPIO_Port, LED_1_Pin, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(LED_2_GPIO_Port, LED_2_Pin, GPIO_PIN_RESET);
      break;
    }

    HAL_GPIO_TogglePin(LED_4_GPIO_Port, LED_4_Pin);

#ifdef DATACOLLECTION
    // DataCollection
    if (((HAL_GetTick() - timerDataCollection) > timerDataCollectionTimeout))
    {
      printf("L%d, C%d, R%d\r\n", dis0, dis1, dis2);
      timerDataCollection = HAL_GetTick();
    }
#endif
    // printf("%d,%d\r\n", dis0, resultaat[left.id].status);
    //  printf("L%d, C%d, R%d\r\n", dis0, dis1, dis2);
    int8_t buf;
    HAL_I2C_Slave_Receive_IT(&hi2c2, &buf, sizeof(buf));
    HAL_Delay(20);
  }
  /* USER CODE END 3 */
}

#ifdef env1

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
   * in the RCC_OscInitTypeDef structure.
   */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
   */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSE;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1 | RCC_PERIPHCLK_I2C1 | RCC_PERIPHCLK_I2C3;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_SYSCLK;
  PeriphClkInit.I2c3ClockSelection = RCC_I2C3CLKSOURCE_SYSCLK;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

#endif
#ifdef env2

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
   * in the RCC_OscInitTypeDef structure.
   */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI | RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
   */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSE;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1 | RCC_PERIPHCLK_USART2 | RCC_PERIPHCLK_I2C1 | RCC_PERIPHCLK_I2C2;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
  PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_HSI;
  PeriphClkInit.I2c2ClockSelection = RCC_I2C2CLKSOURCE_HSI;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}
#endif

/* USER CODE BEGIN 4 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  switch (GPIO_Pin)
  {
  case GPIOI_0_Pin:
    if (!hasRead[0])
    {
      hasRead[0] = true;
    }
    else
      isReady[0] = true;

    break;

  case GPIOI_1_Pin:
    if (!hasRead[1])
    {
      hasRead[1] = true;
    }
    else
      isReady[1] = true;
    break;

  case GPIOI_2_Pin:
    if (!hasRead[2])
    {
      hasRead[2] = true;
    }
    else
      isReady[2] = true;
    break;

  case GPIOI_3_Pin:
    if (!hasRead[3])
    {
      hasRead[3] = true;
    }
    else
      isReady[3] = true;
    break;

  case GPIOI_4_Pin:
    if (!hasRead[4])
    {
      hasRead[4] = true;
    }
    else
      isReady[4] = true;
    break;
  default:
    break;
  }
}

int _write(int file, char *data, int len)
{
  if ((file != STDOUT_FILENO) && (file != STDERR_FILENO))
  {
    errno = EBADF;
    return -1;
  }

  // arbitrary timeout 1000
  HAL_StatusTypeDef status = HAL_UART_Transmit(&huart1, (uint8_t *)data, len, 1000);

  // return # of bytes written - as best we can tell
  return (status == HAL_OK ? len : 0);
}

void HAL_I2C_SlaveRxCpltCallback(I2C_HandleTypeDef *hi2c)
{
  HAL_I2C_Slave_Transmit(&hi2c2, &commando, sizeof(commando), 50);
}
/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
