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
#include "custom_tof_conf.h"
#include "vl53l3cx.h"
#include <sys/unistd.h> // STDOUT_FILENO, STDERR_FI
#include <errno.h>
#include "stdbool.h"
#include "vl53lx_api.h"
#include "calibrationData.h" //bevat methodes en instellingen om de sensoren te calibreren.
#include "GestureDetectObject.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
volatile bool isReady[amountSensor] = {false, false, false};
volatile bool hasRead[amountSensor] = {false, false, false};

// Aanmaken sensor definities
//
Sensor_Definition_t center = {XSHUT_2, 0};
Sensor_Definition_t left = {XSHUT_3, 1};
Sensor_Definition_t right = {XSHUT_1, 2};

// Resultaat van de meetingen die de afstand, status en timestamp bevat voor amountSensorUsed aantal keer aangemaakt
Resultaat_t resultaat[amountSensorUsed];

bool objectPresent = false;
bool prevObjectPresent = false;
bool gestureRL = false;
bool gestureLR = false;
bool gestureDU = false;
bool gestureUD = false;

//Commando enum waarmee we de commando's opslaan
commands commando = NONE;

// Timer die het commando voor timerCommandTimeout seconden aanhoud
static float timerCommand = 0;
static bool timerCommandSet = false;    //Start in false state
static int timerCommandTimeout = 2000;  // 2 seconden

// Global Timer Counter
// static long timerGlobal = 0;

// Timer printf
// static float timerPrintf = 0;
// static bool timerPrintfSet = false;
// static int timerPrintfTimeout = 2000; // 2 seconden

// Opteller van waardes
#define counterHeight 4
int counter[amountSensorUsed][counterHeight];
uint8_t counterStep = 0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void Config_Sensor(VL53L3CX_Object_t *sensor, sensorDev index, uint8_t *address);
uint8_t Sensor_Ready(VL53L3CX_Object_t *sensor, sensorDev index, uint8_t *isReady);
void Wait_For_GPIOI(VL53L3CX_Object_t *sensor, sensorDev index);
void Init_Sensor(VL53L3CX_Object_t *sensor, sensorDev index);
void Start_Sensor(VL53L3CX_Object_t *sensor, sensorDev index);
void Stop_Sensor(VL53L3CX_Object_t *sensor);
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

  //Zal switchen tussen links en rechts sensor telkens bij een nieuwe loop
  bool toggler = false;

  //Define de sensor objecten amountSensorUsed keer.
  VL53L3CX_Object_t sensor[amountSensorUsed];

  //Omdat we in RAM de objecten aanmaken (en niet initializeren) gaat er random waardes insteken.
  //Isinitialized moet 0 zijn om verder te kunnen.
  sensor[left.id].IsInitialized = 0;
  sensor[center.id].IsInitialized = 0;
  sensor[right.id].IsInitialized = 0;
  
  CUSTOM_VL53L3CX_I2C_Init();

  Init_Sensor(&sensor[center.id], center.gpioPin);
  Init_Sensor(&sensor[left.id], left.gpioPin);
  Init_Sensor(&sensor[right.id], right.gpioPin);

  if (HAL_GPIO_ReadPin(SW_1_GPIO_Port, SW_1_Pin))
  //if (true)
  {
    VL53LX_CalibrationData_t callData[amountSensorUsed];

    printf("Calibrating in 10 seconds... \r\n\r\n");
    for (uint8_t i = 0; i < 2; i++)
    {
      HAL_GPIO_TogglePin(LED_0_GPIO_Port, LED_0_Pin);
      HAL_Delay(1000);
    }
    HAL_GPIO_WritePin(LED_0_GPIO_Port, LED_0_Pin, 0);

    printf("Sensor %2d\r\n", center.gpioPin);
    RefSpadCal(&sensor[center.id]);
    RefSpadCal(&sensor[left.id]);
    RefSpadCal(&sensor[right.id]);
    // HAL_GPIO_WritePin(LED_4_GPIO_Port, LED_4_Pin, 1);
    printf("refspad\r\n");
    xTalkCal(&sensor[center.id]);
    xTalkCal(&sensor[left.id]);
    xTalkCal(&sensor[right.id]);
    // HAL_GPIO_WritePin(LED_3_GPIO_Port, LED_3_Pin, 1);
    printf("xtalk\r\n");
    offsetPerVcselCal(&sensor[center.id], 600);
    HAL_Delay(2);
    offsetPerVcselCal(&sensor[left.id], 600);
    HAL_Delay(2);
    offsetPerVcselCal(&sensor[right.id], 600);
    // HAL_GPIO_WritePin(LED_2_GPIO_Port, LED_2_Pin, 1);
    callData[center.id] = getCalibrationData(&sensor[center.id]);
    callData[left.id] = getCalibrationData(&sensor[left.id]);
    callData[right.id] = getCalibrationData(&sensor[right.id]);

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
    // VL53LX_SetCalibrationData(&sensor[i], &callData[i]);
    // setCalibrationData(&sensor[center.id], center.id, &callData[center.id]);
    // setCalibrationData(&sensor[left.id], center.id, &callData[left.id]);
    // setCalibrationData(&sensor[right.id], center.id, &callData[right.id]);

    setOffsetCorrectionMode(&sensor[center.id], (VL53LX_OffsetCorrectionModes)VL53LX_OFFSETCORRECTIONMODE_PERVCSEL);
    setXTalkCompensation(&sensor[center.id], 1);
    setOffsetCorrectionMode(&sensor[left.id], (VL53LX_OffsetCorrectionModes)VL53LX_OFFSETCORRECTIONMODE_PERVCSEL);
    setXTalkCompensation(&sensor[left.id], 1);
    setOffsetCorrectionMode(&sensor[right.id], (VL53LX_OffsetCorrectionModes)VL53LX_OFFSETCORRECTIONMODE_PERVCSEL);
    setXTalkCompensation(&sensor[right.id], 1);

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
      printf("left %5d,center %5d,right %5d \r\n", (int)resultaat[left.id].distance, (int)resultaat[center.id].distance, (int)resultaat[right.id].distance);
    }
  }
  else
  {
    VL53LX_CalibrationData_t callData[amountSensorUsed];
    callData[center.id] = getCalibrationData(&sensor[center.id]);
    callData[left.id] = getCalibrationData(&sensor[left.id]);
    callData[right.id] = getCalibrationData(&sensor[right.id]);

    setCalibrationData(&sensor[center.id], center.id, &callData[center.id]);
    setCalibrationData(&sensor[left.id], center.id, &callData[left.id]);
    setCalibrationData(&sensor[right.id], center.id, &callData[right.id]);

    setOffsetCorrectionMode(&sensor[center.id], (VL53LX_OffsetCorrectionModes)VL53LX_OFFSETCORRECTIONMODE_PERVCSEL);
    setXTalkCompensation(&sensor[center.id], 1);
    setOffsetCorrectionMode(&sensor[left.id], (VL53LX_OffsetCorrectionModes)VL53LX_OFFSETCORRECTIONMODE_PERVCSEL);
    setXTalkCompensation(&sensor[left.id], 1);
    setOffsetCorrectionMode(&sensor[right.id], (VL53LX_OffsetCorrectionModes)VL53LX_OFFSETCORRECTIONMODE_PERVCSEL);
    setXTalkCompensation(&sensor[right.id], 1);
  }

  Start_Sensor(&sensor[center.id], center.gpioPin);
  // Start_Sensor(&sensor[left.id], left.gpioPin);
  // Start_Sensor(&sensor[right.id], right.gpioPin);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  initObjectPresent(-1, -1, -1);

  bool LR_links = false;
  bool LR_rechts = false;
  bool LR_center = false;

  bool RL_links = false;
  bool RL_rechts = false;
  bool RL_center = false;

#ifdef drie1
  bool DU_beiden = false;
#endif
#ifdef drie2
  bool DU_boven = false;
  bool DU_onder = false;
#endif
  bool DU_center = false;

#ifdef drie1
  bool UD_beiden = false;
#endif
#ifdef drie2
  bool UD_boven = false;
  bool UD_onder = false;
#endif
  bool UD_center = false;

  float timerMeasurment = 0;
  bool timerMeasurementSet = false;
  int timerMeasurmentTimeout = 1200; // 0.5 seconden

  while (1)
  {
    // Calculate time over main loop
    // timerGlobal = HAL_GetTick();

    VL53L3CX_Result_t tempResult;

    if (Sensor_Ready(&sensor[center.id], center.gpioPin, (uint8_t *)isReady))
    {
      isReady[center.id] = false;
      VL53L3CX_GetDistance(&sensor[center.id], &tempResult);
      // HAL_Delay(2);
      resultaat[center.id].distance = (long)tempResult.ZoneResult[0].Distance[0];
      resultaat[center.id].status = tempResult.ZoneResult[0].Status[0];
      // HAL_Delay(2);
    }

    if (objectPresent)
    {
      if (toggler)
      {
        if (Sensor_Ready(&sensor[left.id], left.gpioPin, (uint8_t *)isReady))
        {
          isReady[left.id] = false;
          VL53L3CX_GetDistance(&sensor[left.id], &tempResult);
          // HAL_Delay(2);
          resultaat[left.id].distance = (long)tempResult.ZoneResult[0].Distance[0];
          resultaat[left.id].status = tempResult.ZoneResult[0].Status[0];
          // HAL_Delay(2);
        }
      }
      else
      {
        if (Sensor_Ready(&sensor[right.id], right.gpioPin, (uint8_t *)isReady))
        {
          isReady[right.id] = false;
          VL53L3CX_GetDistance(&sensor[right.id], &tempResult);
          // HAL_Delay(2);
          resultaat[right.id].distance = (long)tempResult.ZoneResult[0].Distance[0];
          resultaat[right.id].status = tempResult.ZoneResult[0].Status[0];
          // HAL_Delay(2);
        }
      }

      counter[left.id][counterStep] = resultaat[left.id].distance;
      counter[right.id][counterStep] = resultaat[right.id].distance;

      toggler = !toggler;
    }
    else
    {
      long tempTimer = HAL_GetTick();
      while (HAL_GetTick() - tempTimer < 250)
        ;
    }

    counter[center.id][counterStep] = resultaat[center.id].distance;

    counterStep++;
    if (counterStep >= counterHeight)
      counterStep = 0;

    objectPresent = ckeckObjectPresent(&resultaat[center.id], &objectPresent, &resultaat[center.id].distance);
    int dis0 = 0;
    int dis1 = 0;
    int dis2 = 0;
    // Wanneer er geen commando aanwezig is, kijken ofdat er een gesture is
    if (commando == NONE)
    {
      uint8_t i = 0;

      // Gemiddelde berekenen
      for (i = 0; i < counterHeight; i++)
      {
        dis0 += counter[left.id][i];
      };
      dis0 /= counterHeight;

      for (i = 0; i < counterHeight; i++)
      {
        dis1 += counter[center.id][i];
      };
      dis1 /= counterHeight;

      for (i = 0; i < counterHeight; i++)
      {
        dis2 += counter[right.id][i];
      };
      dis2 /= counterHeight;
      // dis0 = resultaat[left.id].distance;
      // dis1 = resultaat[center.id].distance;
      // dis2 = resultaat[right.id].distance;

// printf("dis0: %5d, dis1: %5d, dis2: %5d\r\n", dis0, dis1, dis2);
#ifdef drie1
      int16_t maxDis = 300;

      // DU gesture
      if (dis0 < maxDis && dis2 < maxDis && !DU_center && resultaat[left.id].status == 0 && resultaat[right.id].status == 0 && dis1 > maxDis)
      {
        // Set flag
        DU_beiden = true;
      }

      if (dis1 < maxDis && resultaat[center.id].status == 0 && DU_beiden == true)
      {
        DU_center = true;
      }

      // UD gesture
      if (dis1 < maxDis && !UD_beiden && resultaat[center.id].status == 0 && dis0 > maxDis && dis2 > maxDis)
      {
        // Set flag
        UD_center = true;
      }

      if (dis0 < maxDis && dis2 < maxDis && resultaat[left.id].status == 0 && resultaat[right.id].status == 0 && UD_center)
      {
        // Set flag
        UD_beiden = true;
      }

      // LR gesture
      if (dis0 < maxDis && resultaat[left.id].status == 0 && !LR_center && !LR_rechts && dis1 > maxDis && dis2 > maxDis)
      {
        LR_links = true;
      }

      if (dis1 < maxDis && resultaat[center.id].status == 0 && !LR_rechts && LR_links && dis2 > maxDis)
      {
        LR_center = true;
      }

      if (dis2 < maxDis && resultaat[right.id].status == 0 && LR_center && LR_links)
      {
        LR_rechts = true;
      }

      // RL gesture
      if (dis2 < maxDis && resultaat[right.id].status == 0 && !RL_center && !RL_links && dis1 > maxDis && dis0 > maxDis)
      {
        RL_rechts = true;
      }

      if (dis1 < maxDis && resultaat[center.id].status == 0 && !RL_links && RL_rechts && dis0 > maxDis)
      {
        RL_center = true;
      }

      if (dis0 < maxDis && resultaat[left.id].status == 0 && RL_center && RL_rechts)
      {
        RL_links = true;
      }

      if (DU_beiden && DU_center)
      {
        commando = DU;
      }

      if (UD_beiden && UD_center)
      {
        commando = UD;
      }

      if (LR_links && LR_center && LR_rechts)
      {
        commando = LR;
      }

      if (RL_links && RL_center && RL_rechts)
      {
        commando = RL;
      }
#endif
#ifdef drie2
      int16_t maxDis = 450;

      // DU gesture
      if (dis0 < maxDis && resultaat[left.id].status == 0 && !DU_center && !DU_boven && dis1 > maxDis && dis2 > maxDis)
      {
        DU_onder = true;
      }

      if (dis2 < maxDis && resultaat[right.id].status == 0 && !DU_center && DU_onder && dis1 > maxDis)
      {
        DU_center = true;
      }

      if (dis1 < maxDis && resultaat[center.id].status == 0 && DU_center && DU_onder)
      {
        DU_boven = true;
      }

      // UD gesture
      if (dis1 < maxDis && resultaat[center.id].status == 0 && !UD_center && !UD_onder && dis0 > maxDis && dis2 > maxDis)
      {
        UD_boven = true;
      }

      if (dis2 < maxDis && resultaat[right.id].status == 0 && !UD_onder && UD_boven && dis0 > maxDis)
      {
        UD_center = true;
      }

      if (dis0 < maxDis && resultaat[left.id].status == 0 && UD_center && UD_boven)
      {
        UD_onder = true;
      }

      // LR gesture
      if (dis0 < maxDis && resultaat[left.id].status == 0 && !LR_center && !LR_rechts && dis1 > maxDis && dis2 > maxDis)
      {
        LR_links = true;
      }

      if (dis1 < maxDis && resultaat[center.id].status == 0 && !LR_rechts && LR_links && dis2 > maxDis)
      {
        LR_center = true;
      }

      if (dis2 < maxDis && resultaat[right.id].status == 0 && LR_center && LR_links)
      {
        LR_rechts = true;
      }

      // RL gesture
      if (dis2 < maxDis && resultaat[right.id].status == 0 && !RL_center && !RL_links && dis1 > maxDis && dis0 > maxDis)
      {
        RL_rechts = true;
      }

      if (dis1 < maxDis && resultaat[center.id].status == 0 && !RL_links && RL_rechts && dis0 > maxDis)
      {
        RL_center = true;
      }

      if (dis0 < maxDis && resultaat[left.id].status == 0 && RL_center && RL_rechts)
      {
        RL_links = true;
      }

      if (DU_boven && DU_center && DU_onder)
      {
        commando = DU;
      }

      if (UD_boven && UD_center && UD_onder)
      {
        commando = UD;
      }

      if (LR_links && LR_center && LR_rechts)
      {
        commando = LR;
      }

      if (RL_links && RL_center && RL_rechts)
      {
        commando = RL;
      }
#endif
      // printf("LR_links %1d, LR_center %1d\t LR_rechts %1d\r\n", LR_links, LR_center,LR_rechts);
      printf("L%d, C%d, R%d\r\n", dis0, dis1, dis2);
    }

    // reset gesture flags
    if (!timerMeasurementSet)
    {
      timerMeasurementSet = true;
      timerMeasurment = HAL_GetTick();
    }
    long temp = HAL_GetTick();
    if (timerMeasurementSet && (temp - timerMeasurment) > timerMeasurmentTimeout)
    {
      timerMeasurementSet = false;
      DU_boven = false;
      DU_center = false;
      DU_onder = false;
      UD_boven = false;
      UD_center = false;
      UD_onder = false;
      LR_links = false;
      LR_rechts = false;
      LR_center = false;
      RL_links = false;
      RL_rechts = false;
      RL_center = false;
    }

    // printf("Object: %1d \t", gestureRL);

    HAL_GPIO_WritePin(LED_3_GPIO_Port, LED_3_Pin, objectPresent);

    // HAL_Delay(2);
    // printf("distance center.gpioPin: %4d %3d\t distance left.gpioPin: %4d %3d\t distance right.gpioPin: %4d %3d\r\n",
    //       (int)resultaat[center.id].distance, resultaat[center.id].status, (int)resultaat[left.id].distance, resultaat[left.id].status, (int)resultaat[right.id].distance, resultaat[right.id].status);
    // printf("L%d, C%d, R%d\r\n", resultaat[left.id].distance, resultaat[center.id].distance, resultaat[right.id].distance);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

    if (objectPresent && !prevObjectPresent)
    {
      // Opstarten van sensoren
      Start_Sensor(&sensor[left.id], left.gpioPin);
      Start_Sensor(&sensor[right.id], right.gpioPin);
      // printf("Start\r\n");
    }

    if (!objectPresent && prevObjectPresent)
    {
      Stop_Sensor(&sensor[left.id]);
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

    // if (((HAL_GetTick() - timerPrintf) > timerPrintfTimeout))
    // {
    //   int timeTotal = HAL_GetTick() - timerGlobal;
    //   printf("totale tijd: %5d, distance: %5d, status: %5d\r\n", timeTotal, resultaat[center.id].distance, resultaat[center.id].status);
    //   printf("L: %5d, C: %5d, R: %5d\r\n", resultaat[left.id].distance, resultaat[center.id].distance, resultaat[right.id].distance);
    //   printf("L: %5d, C: %5d, R: %5d\r\n", resultaat[left.id].status, resultaat[center.id].status, resultaat[right.id].status);
    //   timerPrintf = HAL_GetTick();
    // }
    // printf("L: %5d %2d\r\n", resultaat[left.id].distance, resultaat[left.id].status);
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
void Config_Sensor(VL53L3CX_Object_t *sensor, sensorDev index, uint8_t *address)
{
  sensor->IsInitialized = 0;
  sensor->IO.DeInit = CUSTOM_VL53L3CX_I2C_DeInit;
  sensor->IO.Init = CUSTOM_VL53L3CX_I2C_Init;
  sensor->IO.ReadReg = CUSTOM_VL53L3CX_I2C_ReadReg;
  sensor->IO.WriteReg = CUSTOM_VL53L3CX_I2C_WriteReg;
  sensor->IO.GetTick = CUSTOM_VL53L3CX_I2C_GetTick;
  sensor->IO.Address = 0x52;

  switch (index)
  {
  case 0:
    HAL_GPIO_WritePin(XSHUT_0_GPIO_Port, XSHUT_0_Pin, 1);
    break;
  case 1:
    HAL_GPIO_WritePin(XSHUT_1_GPIO_Port, XSHUT_1_Pin, 1);
    break;
  case 2:
    HAL_GPIO_WritePin(XSHUT_2_GPIO_Port, XSHUT_2_Pin, 1);
    break;
  case 3:
    HAL_GPIO_WritePin(XSHUT_3_GPIO_Port, XSHUT_3_Pin, 1);
    break;
  case 4:
    HAL_GPIO_WritePin(XSHUT_4_GPIO_Port, XSHUT_4_Pin, 1);
    break;
  default:
    break;
  }

  HAL_Delay(2);
  VL53L3CX_Init(sensor);
  // VL53LX_SetMeasurementTimingBudgetMicroSeconds(sensor, 8000);
  VL53L3CX_SetAddress(sensor, (uint32_t)address);

  // Config profile
  VL53L3CX_ProfileConfig_t Profile;

  Profile.RangingProfile = VL53LX_DISTANCEMODE_MEDIUM;
  Profile.TimingBudget = 8 * 3; /* 8 ms < TimingBudget < 500 ms */
  Profile.Frequency = 0;        /* not necessary in simple ranging */
  Profile.EnableAmbient = 1;    /* Enable: 1, Disable: 0 */
  Profile.EnableSignal = 1;     /* Enable: 1, Disable: 0 */

  VL53L3CX_ConfigProfile(sensor, &Profile);
}

uint8_t Sensor_Ready(VL53L3CX_Object_t *sensor, sensorDev index, uint8_t *isReady)
{
  switch (index)
  {
  case 0:
    if (isReady[index] || (!isReady[index] && !HAL_GPIO_ReadPin(GPIOI_0_GPIO_Port, GPIOI_0_Pin)))
      return 1;
    break;
  case 1:
    if (isReady[index] || (!isReady[index] && !HAL_GPIO_ReadPin(GPIOI_1_GPIO_Port, GPIOI_1_Pin)))
      return 1;
    break;
  case 2:
    if (isReady[index] || (!isReady[index] && !HAL_GPIO_ReadPin(GPIOI_2_GPIO_Port, GPIOI_2_Pin)))
      return 1;
    break;
  case 3:
    if (isReady[index] || (!isReady[index] && !HAL_GPIO_ReadPin(GPIOI_3_GPIO_Port, GPIOI_3_Pin)))
      return 1;
    break;
  case 4:
    if (isReady[index] || (!isReady[index] && !HAL_GPIO_ReadPin(GPIOI_4_GPIO_Port, GPIOI_4_Pin)))
      return 1;
    break;
  default:
    return 0;
    break;
  }
  return 0;
}

void Wait_For_GPIOI(VL53L3CX_Object_t *sensor, sensorDev index)
{
  VL53L3CX_Result_t results;

  switch (index)
  {
  case 0:
    while (HAL_GPIO_ReadPin(GPIOI_0_GPIO_Port, GPIOI_0_Pin))
      ; // Zolang wachten totdat de GPIOI is af gegaan
    /* code */
    break;
  case 1:
    while (HAL_GPIO_ReadPin(GPIOI_1_GPIO_Port, GPIOI_1_Pin))
      ; // Zolang wachten totdat de GPIOI is af gegaan
    /* code */
    break;
  case 2:
    while (HAL_GPIO_ReadPin(GPIOI_2_GPIO_Port, GPIOI_2_Pin))
      ; // Zolang wachten totdat de GPIOI is af gegaan
    /* code */
    break;
  case 3:
    while (HAL_GPIO_ReadPin(GPIOI_3_GPIO_Port, GPIOI_3_Pin))
      ; // Zolang wachten totdat de GPIOI is af gegaan
    /* code */
    break;
  case 4:
    while (HAL_GPIO_ReadPin(GPIOI_4_GPIO_Port, GPIOI_4_Pin))
      ; // Zolang wachten totdat de GPIOI is af gegaan
    /* code */
    break;

  default:
    break;
  }

  VL53L3CX_GetDistance(sensor, &results); // 1ste meeting weg gooien
}

void Init_Sensor(VL53L3CX_Object_t *sensor, sensorDev index)
{
  uint32_t id;
  int ret;

  switch (index)
  {
  case 0:
    Config_Sensor(sensor, index, (uint8_t *)2);
    break;
  case 1:
    Config_Sensor(sensor, index, (uint8_t *)4);
    break;
  case 2:
    Config_Sensor(sensor, index, (uint8_t *)6);
    break;
  case 3:
    Config_Sensor(sensor, index, (uint8_t *)8);
    break;
  case 4:
    Config_Sensor(sensor, index, (uint8_t *)10);
    break;

  default:
    break;
  }

  ret = VL53L3CX_ReadID(sensor, &id);
  // printf("%d\r\n", ret);
}

void Start_Sensor(VL53L3CX_Object_t *sensor, sensorDev index)
{
  VL53L3CX_Start(sensor, VL53L3CX_MODE_ASYNC_CONTINUOUS); // Sensor staren met meten
  Wait_For_GPIOI(sensor, index);
}

void Stop_Sensor(VL53L3CX_Object_t *sensor)
{
  VL53L3CX_Stop(sensor); // Sensor staren met meten
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
