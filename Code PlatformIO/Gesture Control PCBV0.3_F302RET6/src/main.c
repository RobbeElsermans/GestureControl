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
#include "GestureDetectRL.h"
#include "GestureDetectLR.h"
#include "GestureDetectUD.h"
#include "GestureDetectDU.h"
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
VL53L3CX_Object_t sensor[amountSensor];
long distance[amountSensor] = {0, 0, 0, 0, 0};
long status[amountSensor] = {0, 0, 0, 0, 0};
volatile bool isReady[amountSensor] = {false, false, false, false, false};
volatile bool hasRead[amountSensor] = {false, false, false, false, false};
// VL53L3CX_Result_t results[amountSensor]; // Vervangen door Resultaat_t

// Resultaat van de meetingen
Resultaat_t resultaat[amountSensor];

bool objectPresent = false;
bool prevObjectPresent = false;
bool gestureRL = false;
bool gestureLR = false;
bool gestureDU = false;
bool gestureUD = false;

bool prevGestureRL = false; // fix debouncing van gestureRL
bool prevGestureLR = false; // fix debouncing van gestureLR
bool prevGestureDU = false; // fix debouncing van gestureDU
bool prevGestureUD = false; // fix debouncing van gestureUD

bool toggler = false;

commands commando = NONE;

// Timer command
static float timerCommand = 0;
static bool timerCommandSet = false;
static int timerCommandTimeout = 2000; // 2 seconden

// Global Timer Counter
static long timerGlobal = 0;

// Timer printf
static float timerPrintf = 0;
static bool timerPrintfSet = false;
static int timerPrintfTimeout = 2000; // 2 seconden

// typedef enum SensorDef
// {
//   CENTER = 0,
//   LEFT = 4,
//   RIGHT = 1,
//   TOP = 2,
//   BOTTOM = 3,
// } sensorDev;

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
  MX_I2C3_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
  HAL_GPIO_WritePin(XSHUT_0_GPIO_Port, XSHUT_0_Pin, 0);
  HAL_GPIO_WritePin(XSHUT_1_GPIO_Port, XSHUT_1_Pin, 0);
  HAL_GPIO_WritePin(XSHUT_2_GPIO_Port, XSHUT_2_Pin, 0);
  HAL_GPIO_WritePin(XSHUT_3_GPIO_Port, XSHUT_3_Pin, 0);
  HAL_GPIO_WritePin(XSHUT_4_GPIO_Port, XSHUT_4_Pin, 0);

  HAL_Delay(20);

  CUSTOM_VL53L3CX_I2C_Init();

  Init_Sensor(&sensor[CENTER], CENTER);
  Init_Sensor(&sensor[LEFT], LEFT);
  Init_Sensor(&sensor[RIGHT], RIGHT);
  Init_Sensor(&sensor[TOP], TOP);
  Init_Sensor(&sensor[BOTTOM], BOTTOM);

  // if (HAL_GPIO_ReadPin(SW_1_GPIO_Port, SW_1_Pin))
  if (true)
  {
    VL53LX_CalibrationData_t callData[amountSensor];

    printf("Calibrating in 10 seconds... \r\n\r\n");
    for (uint8_t i = 0; i < 2; i++)
    {
      HAL_GPIO_TogglePin(LED_0_GPIO_Port, LED_0_Pin);
      HAL_Delay(1000);
    }
    HAL_GPIO_WritePin(LED_0_GPIO_Port, LED_0_Pin, 0);

    // printf("Sensor %2d\r\n", CENTER);
    RefSpadCal(&sensor[CENTER]);
    RefSpadCal(&sensor[LEFT]);
    RefSpadCal(&sensor[RIGHT]);
    RefSpadCal(&sensor[TOP]);
    RefSpadCal(&sensor[BOTTOM]);
    // HAL_GPIO_WritePin(LED_4_GPIO_Port, LED_4_Pin, 1);
    // printf("refspad\r\n");
    // xTalkCal(&sensor[CENTER]);
    // xTalkCal(&sensor[LEFT]);
    // xTalkCal(&sensor[RIGHT]);
    // xTalkCal(&sensor[TOP]);
    // xTalkCal(&sensor[BOTTOM]);
    // HAL_GPIO_WritePin(LED_3_GPIO_Port, LED_3_Pin, 1);
    printf("xtalk\r\n");
    // offsetPerVcselCal(&sensor[CENTER], 600);
    // HAL_Delay(2);
    // offsetPerVcselCal(&sensor[LEFT], 600);
    // HAL_Delay(2);
    // offsetPerVcselCal(&sensor[RIGHT], 600);
    // HAL_GPIO_WritePin(LED_2_GPIO_Port, LED_2_Pin, 1);
    callData[CENTER] = getCalibrationData(&sensor[CENTER]);
    callData[LEFT] = getCalibrationData(&sensor[LEFT]);
    callData[RIGHT] = getCalibrationData(&sensor[RIGHT]);
    callData[TOP] = getCalibrationData(&sensor[TOP]);
    callData[BOTTOM] = getCalibrationData(&sensor[BOTTOM]);
    // HAL_GPIO_WritePin(LED_1_GPIO_Port, LED_1_Pin, 1);
    // VL53LX_SetCalibrationData(&sensor[i], &callData[i]);
    setCalibrationData(&sensor[CENTER], CENTER, &callData[CENTER]);
    setCalibrationData(&sensor[LEFT], LEFT, &callData[LEFT]);
    setCalibrationData(&sensor[RIGHT], RIGHT, &callData[RIGHT]);
    setCalibrationData(&sensor[TOP], TOP, &callData[TOP]);
    setCalibrationData(&sensor[BOTTOM], BOTTOM, &callData[BOTTOM]);

    setOffsetCorrectionMode(&sensor[CENTER], (VL53LX_OffsetCorrectionModes)VL53LX_OFFSETCORRECTIONMODE_PERVCSEL);
    setXTalkCompensation(&sensor[CENTER], 1);
    setOffsetCorrectionMode(&sensor[LEFT], (VL53LX_OffsetCorrectionModes)VL53LX_OFFSETCORRECTIONMODE_PERVCSEL);
    setXTalkCompensation(&sensor[LEFT], 1);
    setOffsetCorrectionMode(&sensor[RIGHT], (VL53LX_OffsetCorrectionModes)VL53LX_OFFSETCORRECTIONMODE_PERVCSEL);
    setXTalkCompensation(&sensor[RIGHT], 1);
    setOffsetCorrectionMode(&sensor[TOP], (VL53LX_OffsetCorrectionModes)VL53LX_OFFSETCORRECTIONMODE_PERVCSEL);
    setXTalkCompensation(&sensor[TOP], 1);
    setOffsetCorrectionMode(&sensor[BOTTOM], (VL53LX_OffsetCorrectionModes)VL53LX_OFFSETCORRECTIONMODE_PERVCSEL);
    setXTalkCompensation(&sensor[BOTTOM], 1);
  }

  Start_Sensor(&sensor[CENTER], CENTER);
  // Start_Sensor(&sensor[LEFT], LEFT);
  // Start_Sensor(&sensor[RIGHT], RIGHT);
  // Start_Sensor(&sensor[TOP], TOP);
  // Start_Sensor(&sensor[BOTTOM], BOTTOM);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  initObjectPresent(-1, -1, -1);

  while (1)
  {
    // Calculate time over main loop
    timerGlobal = HAL_GetTick();

    VL53L3CX_Result_t tempResult;

    if (Sensor_Ready(&sensor[CENTER], CENTER, (uint8_t *)isReady))
    {
      isReady[CENTER] = false;
      VL53L3CX_GetDistance(&sensor[CENTER], &tempResult);
      // HAL_Delay(2);
      resultaat[CENTER].distance = (long)tempResult.ZoneResult[0].Distance[0];
      resultaat[CENTER].status = tempResult.ZoneResult[0].Status[0];
      // HAL_Delay(2);
    }

    if (objectPresent)
    {
      if (toggler)
      {
        if (Sensor_Ready(&sensor[LEFT], LEFT, (uint8_t *)isReady))
        {
          isReady[LEFT] = false;
          VL53L3CX_GetDistance(&sensor[LEFT], &tempResult);
          // HAL_Delay(2);
          resultaat[LEFT].distance = (long)tempResult.ZoneResult[0].Distance[0];
          resultaat[LEFT].status = tempResult.ZoneResult[0].Status[0];
          // HAL_Delay(2);
        }

        if (Sensor_Ready(&sensor[RIGHT], RIGHT, (uint8_t *)isReady))
        {
          isReady[RIGHT] = false;
          VL53L3CX_GetDistance(&sensor[RIGHT], &tempResult);
          // HAL_Delay(2);
          resultaat[RIGHT].distance = (long)tempResult.ZoneResult[0].Distance[0];
          resultaat[RIGHT].status = tempResult.ZoneResult[0].Status[0];
          // HAL_Delay(2);
        }
      }
      else
      {
        if (Sensor_Ready(&sensor[TOP], TOP, (uint8_t *)isReady))
        {
          isReady[TOP] = false;
          VL53L3CX_GetDistance(&sensor[TOP], &tempResult);
          // HAL_Delay(2);
          resultaat[TOP].distance = (long)tempResult.ZoneResult[0].Distance[0];
          resultaat[TOP].status = tempResult.ZoneResult[0].Status[0];
          // HAL_Delay(2);
        }

        if (Sensor_Ready(&sensor[BOTTOM], BOTTOM, (uint8_t *)isReady))
        {
          isReady[BOTTOM] = false;
          VL53L3CX_GetDistance(&sensor[BOTTOM], &tempResult);
          // HAL_Delay(2);
          resultaat[BOTTOM].distance = (long)tempResult.ZoneResult[0].Distance[0];
          resultaat[BOTTOM].status = tempResult.ZoneResult[0].Status[0];
          // HAL_Delay(2);
        }
      }
      toggler = !toggler;
    }
    else
    {
      long tempTimer = HAL_GetTick();
      while (HAL_GetTick() - tempTimer < 500)
        ;
    }

    objectPresent = ckeckObjectPresent(&resultaat[CENTER], &objectPresent, &resultaat[CENTER].distance);

    // Wanneer er geen dimming commando aanwezig is dan kijken we of dat er een Right Left beweging aanwezig is
    gestureRL = CheckGestureRL(&gestureRL, &objectPresent, resultaat);
    gestureLR = CheckGestureLR(&gestureLR, &objectPresent, resultaat);
    // gestureDU = CheckGestureDU(&gestureDU, &objectPresent, resultaat);
    // gestureUD = CheckGestureUD(&gestureUD, &objectPresent, resultaat);

    // printf("Object: %1d \t", gestureRL);

    HAL_GPIO_WritePin(LED_3_GPIO_Port, LED_3_Pin, objectPresent);

    // HAL_Delay(2);
    //  printf("distance CENTER: %4d %3d\t distance LEFT: %4d %3d\t distance RIGHT: %4d %3d\t distance TOP: %4d %3d\t distance BOTTOM: %4d %3d\r\n",
    //(int)distance[CENTER], status[CENTER], (int)distance[LEFT], status[LEFT], (int)distance[RIGHT], status[RIGHT], (int)distance[TOP], status[TOP], (int)distance[BOTTOM], status[BOTTOM]);
    //  printf("L: %5d, C: %5d, R: %5d\r\n", distance[LEFT], distance[CENTER], distance[RIGHT]);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

    if (objectPresent && !prevObjectPresent)
    {
      // Opstarten van sensoren
      Start_Sensor(&sensor[LEFT], LEFT);
      Start_Sensor(&sensor[RIGHT], RIGHT);
      Start_Sensor(&sensor[TOP], TOP);
      Start_Sensor(&sensor[BOTTOM], BOTTOM);
      printf("Start\r\n");
    }
    else if (!objectPresent && prevObjectPresent)
    {
      Stop_Sensor(&sensor[LEFT]);
      Stop_Sensor(&sensor[RIGHT]);
      Stop_Sensor(&sensor[TOP]);
      Stop_Sensor(&sensor[BOTTOM]);
      printf("Stop\r\n");
    }

    // Commando's instellen
    //  Het commando RL activeren
    if (gestureRL && !prevGestureRL && commando == NONE)
    {
      prevGestureRL = gestureRL;
      printf("gestureCommand RL: %d \r\n", gestureRL);
      commando = RL;
    }

    // Het commando LR activeren
    if (gestureLR && !prevGestureLR && commando == NONE)
    {
      prevGestureLR = gestureLR;
      printf("gestureCommand LR: %d \r\n", gestureLR);
      commando = LR;
    }

    // Het commando DU activeren
    if (gestureDU && !prevGestureDU && commando == NONE)
    {
      prevGestureDU = gestureDU;
      printf("gestureCommand DU: %d \r\n", gestureDU);
      commando = DU;
    }

    // Het commando UD activeren
    if (gestureUD && !prevGestureUD && commando == NONE)
    {
      prevGestureUD = gestureUD;
      printf("gestureCommand UD: %d \r\n", gestureUD);
      commando = UD;
    }

    prevObjectPresent = objectPresent;
    prevGestureRL = gestureRL; // fix debouncing van gestureRL
    prevGestureLR = gestureLR; // fix debouncing van gestureLR
    prevGestureDU = gestureDU; // fix debouncing van gestureDU
    prevGestureUD = gestureUD; // fix debouncing van gestureUD

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
    //   printf("totale tijd: %5d, distance: %5d, status: %5d\r\n", timeTotal, resultaat[CENTER].distance, resultaat[CENTER].status);
    //   printf("L: %5d, C: %5d, R: %5d\r\n", resultaat[LEFT].distance, resultaat[CENTER].distance, resultaat[RIGHT].distance);
    //   printf("L: %5d, C: %5d, R: %5d\r\n", resultaat[LEFT].status, resultaat[CENTER].status, resultaat[RIGHT].status);
    //   timerPrintf = HAL_GetTick();
    // }
    printf("C: %5d %2d\r\n", resultaat[CENTER].distance, resultaat[CENTER].status);
  }
  /* USER CODE END 3 */
}

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

  sensor->IO.DeInit = CUSTOM_VL53L3CX_I2C_DeInit;
  sensor->IO.Init = CUSTOM_VL53L3CX_I2C_Init;
  sensor->IO.ReadReg = CUSTOM_VL53L3CX_I2C_ReadReg;
  sensor->IO.WriteReg = CUSTOM_VL53L3CX_I2C_WriteReg;
  sensor->IO.GetTick = CUSTOM_VL53L3CX_I2C_GetTick;
  sensor->IO.Address = 0x52;

  switch (index)
  {
  case 0: // Sensor CENTER
    HAL_GPIO_WritePin(XSHUT_0_GPIO_Port, XSHUT_0_Pin, 1);
    break;
  case 1: // Sensor LEFT
    HAL_GPIO_WritePin(XSHUT_1_GPIO_Port, XSHUT_1_Pin, 1);
    break;
  case 2: // Sensor RIGHT
    HAL_GPIO_WritePin(XSHUT_2_GPIO_Port, XSHUT_2_Pin, 1);
    break;
  case 3: // Sensor TOP
    HAL_GPIO_WritePin(XSHUT_3_GPIO_Port, XSHUT_3_Pin, 1);
    break;
  case 4: // Sensor BOTTOM
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
  Profile.TimingBudget = 8 * 5; /* 8 ms < TimingBudget < 500 ms */
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
  printf("%d\r\n", ret);
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
