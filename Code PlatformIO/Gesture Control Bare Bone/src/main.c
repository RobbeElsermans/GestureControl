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
#include "custom_tof_conf.h"
#include "vl53l3cx.h"
#include <sys/unistd.h> // STDOUT_FILENO, STDERR_FI
#include <errno.h>
#include "stm32f3xx_hal_rcc_ex.h"
#include "vl53lx_api.h"
#include "stdbool.h"
#include <stdio.h>
#include <string.h>
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


long distance[5] = {0,0,0,0,0};
volatile bool isReady[5] = {false, false, false, false, false};
volatile bool hasRead[5] = {false, false, false, false, false};
VL53L3CX_Result_t results;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
 VL53L3CX_Object_t sensor[];
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
  HAL_Delay(20);
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();
  HAL_Delay(20);
  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_I2C2_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */

  sensor->IO.DeInit = CUSTOM_VL53L3CX_I2C_DeInit;
  sensor->IO.Init = CUSTOM_VL53L3CX_I2C_Init;
  sensor->IO.ReadReg = CUSTOM_VL53L3CX_I2C_ReadReg;
  sensor->IO.WriteReg = CUSTOM_VL53L3CX_I2C_WriteReg;
  sensor->IO.GetTick = CUSTOM_VL53L3CX_I2C_GetTick;
  sensor->IO.Address = VL53L3CX_DEVICE_ADDRESS; // Default adres

  // Config profile
  VL53L3CX_ProfileConfig_t Profile;

  Profile.RangingProfile = VL53LX_DISTANCEMODE_MEDIUM;
  Profile.TimingBudget = 100; /* 16 ms < TimingBudget < 500 ms */
  Profile.Frequency = 0;      /* not necessary in simple ranging */
  Profile.EnableAmbient = 1;  /* Enable: 1, Disable: 0 */
  Profile.EnableSignal = 1;   /* Enable: 1, Disable: 0 */

  HAL_GPIO_WritePin(XSHUT_0_GPIO_Port, XSHUT_0_Pin, 0);
  HAL_GPIO_WritePin(XSHUT_1_GPIO_Port, XSHUT_1_Pin, 0);
  HAL_GPIO_WritePin(XSHUT_2_GPIO_Port, XSHUT_2_Pin, 0);
  HAL_GPIO_WritePin(XSHUT_3_GPIO_Port, XSHUT_3_Pin, 0);
  HAL_GPIO_WritePin(XSHUT_4_GPIO_Port, XSHUT_4_Pin, 0);

  CUSTOM_VL53L3CX_I2C_Init();

  HAL_Delay(20);
  HAL_GPIO_WritePin(XSHUT_0_GPIO_Port, XSHUT_0_Pin, 1);
  HAL_Delay(20);
  VL53L3CX_Init(&sensor[0]);
  HAL_Delay(20);
  VL53L3CX_SetAddress(&sensor[0], 0x53);
  VL53L3CX_ConfigProfile(&sensor[0], &Profile);

  // Starten sensor 0
  VL53L3CX_Start(&sensor[0], VL53L3CX_MODE_ASYNC_CONTINUOUS);
  HAL_Delay(20);
  VL53L3CX_GetDistance(&sensor[0], &results);
  HAL_Delay(20);

  // HAL_GPIO_WritePin(XSHUT_1_GPIO_Port, XSHUT_1_Pin, 1);
  // HAL_Delay(20);
  // VL53L3CX_Init(&sensor[1]);
  // HAL_Delay(20);
  // VL53L3CX_SetAddress(&sensor[1], 0x54);

      // HAL_Delay(20);

      // sensor.IO.Address = address[1];
      // VL53L3CX_ConfigProfile(&sensor, &Profile);

      // // Starten sensor 1
      // sensor.IO.Address = address[1];
      // sensor.IsRanging = (uint8_t)isRanging[1];
      // VL53L3CX_Start(&sensor, VL53L3CX_MODE_ASYNC_CONTINUOUS);
      // isRanging[1] = true;
      // HAL_Delay(20);
      // VL53L3CX_GetDistance(&sensor, &results);
      // HAL_Delay(1000);
      // VL53L3CX_GetDistance(&sensor, &results);

      /* USER CODE END 2 */

      /* Infinite loop */
      /* USER CODE BEGIN WHILE */
      // VL53LX_ClearInterruptAndStartMeasurement(&sensor);
      while (1)
  {
    /* USER CODE END WHILE */
    // VL53L3CX_GetDistance(&sensor, &results);
    HAL_Delay(5);
    if (isReady[0] || (!isReady[0] && !HAL_GPIO_ReadPin(GPIOI_0_GPIO_Port, GPIOI_0_Pin)))
    {
      HAL_Delay(1);
      isReady[0] = false;

      VL53L3CX_GetDistance(&sensor[0], &results);
      HAL_Delay(1);
      distance[0] = (long)results.ZoneResult[0].Distance[0];
    }
    if (isReady[1] || (!isReady[1] && !HAL_GPIO_ReadPin(GPIOI_1_GPIO_Port, GPIOI_1_Pin)))
    {
      HAL_Delay(1);
      isReady[1] = false;
      VL53L3CX_GetDistance(&sensor[1], &results);
      HAL_Delay(1);
      distance[1] = (long)results.ZoneResult[0].Distance[0];
    }

    if (distance[0] >= 50 && distance[0] <= 300)
    {
      HAL_GPIO_WritePin(LED_0_GPIO_Port, LED_0_Pin, 1);
      HAL_Delay(200);
    }

    if (distance[0] > 300 && distance[0] <= 600)
    {
      HAL_GPIO_WritePin(LED_1_GPIO_Port, LED_1_Pin, 1);
      HAL_Delay(200);
    }

    if (distance[0] > 600 && distance[0] <= 800)
    {
      HAL_GPIO_WritePin(LED_2_GPIO_Port, LED_2_Pin, 1);
      HAL_Delay(200);
    }

    if (distance[0] > 800 && distance[0] <= 1200)
    {
      HAL_GPIO_WritePin(LED_3_GPIO_Port, LED_3_Pin, 1);
      HAL_Delay(200);
    }
    if (distance[0] > 1200)
    {
      HAL_GPIO_WritePin(LED_4_GPIO_Port, LED_4_Pin, 1);
      HAL_Delay(200);
    }

    HAL_Delay(2);
    HAL_GPIO_WritePin(LED_0_GPIO_Port, LED_0_Pin, 0);
    HAL_GPIO_WritePin(LED_1_GPIO_Port, LED_1_Pin, 0);
    HAL_GPIO_WritePin(LED_2_GPIO_Port, LED_2_Pin, 0);
    HAL_GPIO_WritePin(LED_3_GPIO_Port, LED_3_Pin, 0);
    HAL_GPIO_WritePin(LED_4_GPIO_Port, LED_4_Pin, 0);

    printf("distance 0: %4d\tdistance 1: %4d\r\n", distance[0], distance[1]);
    /* USER CODE BEGIN 3 */
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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
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
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  // PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1|RCC_PERIPHCLK_USART2|RCC_PERIPHCLK_I2C1|RCC_PERIPHCLK_I2C2;
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1 | RCC_PERIPHCLK_I2C1 | RCC_PERIPHCLK_I2C2;
  PeriphClkInit.Usart1ClockSelection = (0x00000000U);
  // PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_HSI;
  PeriphClkInit.I2c2ClockSelection = RCC_I2C2CLKSOURCE_HSI;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
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

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  switch (GPIO_Pin)
  {
  case GPIOI_0_Pin:
    if (!hasRead[0])
    {
      hasRead[0] = true;
      // sensor.IO.Address = address[0];
      // VL53L3CX_GetDistance(&sensor, &results);
    }
    else
      isReady[0] = true;
    break;

  case GPIOI_1_Pin:
    if (!hasRead[1])
    {
      hasRead[1] = true;
      // sensor.IO.Address = address[1];
      // VL53L3CX_GetDistance(&sensor, &results);
    }
    else
      isReady[1] = true;
    break;

  case GPIOI_2_Pin:
    if (!hasRead[2])
    {
      hasRead[2] = true;
      // sensor.IO.Address = address[2];
      // VL53L3CX_GetDistance(&sensor, &results);
    }
    else
      isReady[2] = true;
    break;

  case GPIOI_3_Pin:
    if (!hasRead[3])
    {
      hasRead[3] = true;
      // sensor.IO.Address = address[3];
      // VL53L3CX_GetDistance(&sensor, &results);
    }
    else
      isReady[3] = true;
    break;

  case GPIOI_4_Pin:
    if (!hasRead[4])
    {
      hasRead[4] = true;
      // sensor.IO.Address = address[4];
      // VL53L3CX_GetDistance(&sensor, &results);
    }
    else
      isReady[4] = true;
    break;
  default:
    break;
  }
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
