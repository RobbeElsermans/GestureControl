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
volatile bool isReady[amountSensor] = {false, false, false,false,false};
volatile bool hasRead[amountSensor] = {false, false, false, false, false};

#ifdef DATACOLLECTION
long timerDataCollection = 0;
int timerDataCollectionTimeout = 20; // aantal milliseconden per meeting
#endif

// Aanmaken sensor definities
//
Sensor_Definition_t ToF_sensor = {XSHUT_3, 0};


// Resultaat van de meetingen die de afstand, status en timestamp bevat voor amountSensorUsed aantal keer aangemaakt
struct resultaat resultaat[amountSensorUsed];

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
int ToF_sensorDistance = 0;
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
  VL53L3CX_Object_t sensor[amountSensorUsed];
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
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

  // Omdat we in RAM de objecten aanmaken (en niet initializeren) gaat er random waardes insteken.
  // Isinitialized moet 0 zijn om verder te kunnen.
  sensor[ToF_sensor.id].IsInitialized = 0;

  CUSTOM_VL53L3CX_I2C_Init();

  //De sensoren initialiseren
  Init_Sensor(&sensor[ToF_sensor.id], ToF_sensor.gpioPin);
  HAL_Delay(2);

  #pragma endregion

  #pragma region kalibratie
  //Als de drukknop SW_1 actief is, wordt er gekalibreerd
  //if (HAL_GPIO_ReadPin(SW_1_GPIO_Port, SW_1_Pin))
  if(true)
  {
    getCalibrate(&sensor[ToF_sensor.id], ToF_sensor.id);

    //VL53L3CX_Result_t tempResult;
    Start_Sensor(&sensor[ToF_sensor.id], ToF_sensor.gpioPin);
    while (1)
    {
      getData(&sensor[ToF_sensor.id], &ToF_sensor, resultaat, (uint8_t *)isReady);
      HAL_Delay(1);

      HAL_Delay(200);
      printf("ToF_sensor %5d, %2d\r\n", (int)resultaat[ToF_sensor.id].distance, resultaat[ToF_sensor.id].status);
    }
  }
  else
  {
    setCalibrate(&sensor[ToF_sensor.id], ToF_sensor.id);;
  }

  #pragma endregion

  Start_Sensor(&sensor[ToF_sensor.id], ToF_sensor.gpioPin);
  // Start_Sensor(&sensor[left.id], left.gpioPin);
  // Start_Sensor(&sensor[right.id], right.gpioPin);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  while (1)
  {

    #pragma region collectData
    isReady[ToF_sensor.id] = getData(&sensor[ToF_sensor.id], &ToF_sensor, &resultaat[ToF_sensor.id], (uint8_t *)isReady);
    setMeanVal(ToF_sensor.id, resultaat[ToF_sensor.id].distance);

    #pragma endregion

    
    #pragma region calcMean
    // Wanneer er geen commando aanwezig is, kijken ofdat er een gesture is

     ToF_sensorDistance = getMean(ToF_sensor.id);

    #pragma endregion

    checkResetTimer();

    HAL_GPIO_WritePin(LED_3_GPIO_Port, LED_3_Pin, objectPresent);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

    HAL_GPIO_TogglePin(LED_4_GPIO_Port, LED_4_Pin);

#ifdef DATACOLLECTION
    // DataCollection
    if (((HAL_GetTick() - timerDataCollection) > timerDataCollectionTimeout))
    {
      printf("C%d\r\n", ToF_sensorDistance);
      timerDataCollection = HAL_GetTick();
    }
#endif
    // printf("%d,%d\r\n", leftDistance, resultaat[left.id].status);
    //  printf("L%d, C%d, R%d\r\n", leftDistance, ToF_sensorDistance, rightDistance);
    
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
