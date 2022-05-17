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
#define DATACOLLECTION

// Toggle voor calibrate
//#define CALIBRATE

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
volatile uint8_t isReady[AMOUNT_SENSOR] = {false, false, false,false,false};
volatile uint8_t hasRead[AMOUNT_SENSOR] = {false, false, false, false, false};

#ifdef DATACOLLECTION
long timerDataCollection = 0;
int timerDataCollectionTimeout = 20; // aantal milliseconden per meeting
#endif

// Aanmaken sensor definities
//
Sensor_Definition_t center = {XSHUT_2, 0};
Sensor_Definition_t left = {XSHUT_1, 1};
Sensor_Definition_t right = {XSHUT_3, 2};

// Resultaat van de meetingen die de afstand, status en timestamp bevat voor amountSensorUsed aantal keer aangemaakt
struct resultaat resultaat[AMOUNT_SENSOR_USED];

bool objectPresent = false;
bool prevObjectPresent = false;

// Commando enum waarmee we de commando's opslaan
commands commando = NONE;

// Timer die het commando voor timerCommandTimeout seconden aanhoud
static float timerCommand = 0;
static bool timerCommandSet = false;   // Start in false state
static int timerCommandTimeout = 2000; // 2 seconden

//Mean values
int leftDistance = 0;
int centerDistance = 0;
int rightDistance = 0;

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
  #pragma region initializing
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
  VL53L3CX_Object_t sensor[AMOUNT_SENSOR_USED];
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();

  MX_I2C2_Init();

  MX_USART1_UART_Init();

  /* USER CODE BEGIN 2 */
  HAL_GPIO_WritePin(XSHUT_0_GPIO_Port, XSHUT_0_Pin, 0);
  HAL_GPIO_WritePin(XSHUT_1_GPIO_Port, XSHUT_1_Pin, 0);
  HAL_GPIO_WritePin(XSHUT_2_GPIO_Port, XSHUT_2_Pin, 0);
  HAL_GPIO_WritePin(XSHUT_3_GPIO_Port, XSHUT_3_Pin, 0);
  HAL_GPIO_WritePin(XSHUT_4_GPIO_Port, XSHUT_4_Pin, 0);

  HAL_Delay(20);

  // Omdat we in RAM de objecten aanmaken (en niet initializeren) gaat er random waardes insteken.
  // Isinitialized moet 0 zijn om verder te kunnen.
  sensor[left.id].IsInitialized = 0;
  sensor[center.id].IsInitialized = 0;
  sensor[right.id].IsInitialized = 0;

  CUSTOM_VL53L3CX_I2C_Init();

  //De sensoren initialiseren
  Init_Sensor(&sensor[center.id], center.gpioPin);
  HAL_Delay(2);
  Init_Sensor(&sensor[left.id], left.gpioPin);
  HAL_Delay(2);
  Init_Sensor(&sensor[right.id], right.gpioPin);
  HAL_Delay(2);

  #pragma endregion

  #pragma region kalibratie
  //Als de drukknop SW_1 actief is, wordt er gekalibreerd
  if (HAL_GPIO_ReadPin(SW_1_GPIO_Port, SW_1_Pin))
  //if(true)
  {
    getCalibrate(&sensor[center.id], center.id);
    getCalibrate(&sensor[left.id], left.id);
    getCalibrate(&sensor[right.id], right.id);

    Start_Sensor(&sensor[center.id], center.gpioPin);
    Start_Sensor(&sensor[left.id], left.gpioPin);
    Start_Sensor(&sensor[right.id], right.gpioPin);
    while (1)
    {
      getData(&sensor[left.id], &left, resultaat, (uint8_t *)isReady);
      HAL_Delay(1);
      getData(&sensor[center.id], &center, resultaat, (uint8_t *)isReady);
      HAL_Delay(1);
      getData(&sensor[right.id], &right, resultaat, (uint8_t *)isReady);
      HAL_Delay(1);
      HAL_Delay(200);
      printf("left %5d, %2d,center %5d, %2d,right %5d, %2d \r\n", (int)resultaat[left.id].distance, resultaat[left.id].status, (int)resultaat[center.id].distance, resultaat[center.id].status, (int)resultaat[right.id].distance, resultaat[right.id].status);
    }
  }
  else
  {
    setCalibrate(&sensor[center.id], center.id);;
    setCalibrate(&sensor[left.id], left.id);
    setCalibrate(&sensor[right.id], right.id);

    // Start_Sensor(&sensor[center.id], center.gpioPin);
    // Start_Sensor(&sensor[left.id], left.gpioPin);
    // Start_Sensor(&sensor[right.id], right.gpioPin);
    // while (1)
    // {
    //   getData(&sensor[left.id], &left, resultaat, (uint8_t *)isReady);
    //   HAL_Delay(1);
    //   getData(&sensor[center.id], &center, resultaat, (uint8_t *)isReady);
    //   HAL_Delay(1);
    //   getData(&sensor[right.id], &right, resultaat, (uint8_t *)isReady);
    //   HAL_Delay(1);
    //   HAL_Delay(200);
    //   printf("left %5d, %2d,center %5d, %2d,right %5d, %2d \r\n", (int)resultaat[left.id].distance, resultaat[left.id].status, (int)resultaat[center.id].distance, resultaat[center.id].status, (int)resultaat[right.id].distance, resultaat[right.id].status);
    // }
  }

  #pragma endregion

  Start_Sensor(&sensor[left.id], left.gpioPin);
  // Start_Sensor(&sensor[left.id], left.gpioPin);
  // Start_Sensor(&sensor[right.id], right.gpioPin);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  initObjectPresent(-1, -1, -1);


  while (1)
  {

    #pragma region collectData
    isReady[left.id] = getData(&sensor[left.id], &left, resultaat, (uint8_t *)isReady);;
    setMeanVal(left.id, resultaat[left.id].distance);

    if (objectPresent)
    {
      isReady[center.id] = getData(&sensor[center.id], &center, resultaat, (uint8_t *)isReady);
      setMeanVal(center.id, resultaat[center.id].distance);

      isReady[right.id] = getData(&sensor[right.id], &right, resultaat, (uint8_t *)isReady);
      setMeanVal(right.id, resultaat[right.id].distance);
    }

    #pragma endregion
    
    objectPresent = ckeckObjectPresent(&resultaat[left.id], &objectPresent, &resultaat[left.id].distance);
    
    #pragma region calcMean
    // Wanneer er geen commando aanwezig is, kijken ofdat er een gesture is
    if (commando == NONE)
    {
      leftDistance = getMean(left.id);
      centerDistance = getMean(center.id);
      rightDistance = getMean(right.id);
      int8_t val = detectgesture(leftDistance, resultaat[left.id].status, centerDistance, resultaat[center.id].status, rightDistance, resultaat[right.id].status);
      if (val != -1)
        commando = val;
    }
    #pragma endregion

    checkResetTimer();

    HAL_GPIO_WritePin(LED_3_GPIO_Port, LED_3_Pin, objectPresent);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */


    #pragma region start-stopSensor
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

    #pragma endregion


#pragma region commando
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
    #pragma endregion

    HAL_GPIO_TogglePin(LED_4_GPIO_Port, LED_4_Pin);

#ifdef DATACOLLECTION
    // DataCollection
    if (((HAL_GetTick() - timerDataCollection) > timerDataCollectionTimeout))
    {
      //printf("L%d, C%d, R%d\r\n", leftDistance, centerDistance, rightDistance);
      timerDataCollection = HAL_GetTick();
    }
#endif
    printf("%d,%d\t%d,%d\t%d,%d\r\n", resultaat[left.id].distance, resultaat[left.id].status
                                    , resultaat[center.id].distance, resultaat[center.id].status
                                    , resultaat[right.id].distance, resultaat[right.id].status);
    //  printf("L%d, C%d, R%d\r\n", leftDistance, centerDistance, rightDistance);
    
    uint8_t buf;
    HAL_I2C_Slave_Receive_IT(&hi2c2, &buf, sizeof(buf));
    
    //I2C aanzetten om iets te ontvangen in interrupt modus.
    
    HAL_Delay(1);
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
