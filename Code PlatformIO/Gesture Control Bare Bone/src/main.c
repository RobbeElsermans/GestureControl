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

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "gpio.h"
#include "i2c.h"
#include "usart.h"

/* Private includes ----------------------------------------------------------*/

#include <string.h>
#include <stdio.h>
#include "stdbool.h"    //Nodig om bool te kunnen gebruiken
#include <sys/unistd.h> // STDOUT_FILENO, STDERR_FI
#include <errno.h>
#include "vl53l3cx.h"
#include "stm32f4xx_nucleo_bus.h"
#include <vl53lx_platform.h>
#include "vl53lx_def.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c3;
TIM_HandleTypeDef htim3;
UART_HandleTypeDef huart2;
UART_HandleTypeDef huart3;
I2C_HandleTypeDef hi2c1;

/* Private variables ---------------------------------------------------------*/
static volatile uint8_t PushButtonDetected = 0;

/* Private function prototypes -----------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/* Private user code ---------------------------------------------------------*/

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{
  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  // MX_TIM3_Init();
  MX_I2C3_Init();

  if (HAL_I2C_EnableListen_IT(&hi2c3) != HAL_OK)
  {
    /* Transfer error in reception process */
    Error_Handler();
  }

  // Init
  VL53LX_DEV sensors[5];

  for (uint8_t i = 0; i < 5; i++)
  {
    sensors[i]->IO.Init = &BSP_I2C1_Init;
    sensors[i]->IO.DeInit = &BSP_I2C1_DeInit;
    sensors[i]->IO.GetTick = &BSP_GetTick;
    sensors[i]->IO.ReadReg = &BSP_I2C1_Recv;
    sensors[i]->IO.WriteReg = &BSP_I2C1_Send;
    sensors[i]->IO.Address = 0x50 + i;
  }

  // De sensoren allemaal afzetten
  HAL_GPIO_WritePin(XSHUT_0_GPIO_Port, XSHUT_0_Pin, 0);
  HAL_GPIO_WritePin(XSHUT_1_GPIO_Port, XSHUT_1_Pin, 0);
  HAL_GPIO_WritePin(XSHUT_2_GPIO_Port, XSHUT_2_Pin, 0);
  HAL_GPIO_WritePin(XSHUT_3_GPIO_Port, XSHUT_3_Pin, 0);
  HAL_GPIO_WritePin(XSHUT_4_GPIO_Port, XSHUT_4_Pin, 0);

  // 1 voor 1 opzetten en adress toewijzigen
  HAL_GPIO_WritePin(XSHUT_0_GPIO_Port, XSHUT_0_Pin, 1);
  VL53L3CX_SetAddress(sensors[0], sensors[0]->IO.Address);

  VL53L3CX_Init(sensors[0]);

  VL53L3CX_ProfileConfig_t Profile;

  Profile.RangingProfile = VL53LX_DISTANCEMODE_MEDIUM;
  Profile.TimingBudget = 100; /* 16 ms < TimingBudget < 500 ms */
  Profile.Frequency = 0;      /* not necessary in simple ranging */
  Profile.EnableAmbient = 1;  /* Enable: 1, Disable: 0 */
  Profile.EnableSignal = 1;   /* Enable: 1, Disable: 0 */

  VL53L3CX_ConfigProfile(sensors[0], &Profile);

  uint16_t pId = 0;
  VL53LX_RdWord(sensors[0], VL53L3CX_ID_REG, &pId);

  VL53L3CX_Start(sensors[0], VL53L3CX_MODE_BLOCKING_CONTINUOUS);

  VL53L3CX_Result_t result;

  // 1ste binnen halen en weg gooien
  VL53L3CX_GetDistance(sensors[0], &result);
  HAL_Delay(20);
  VL53L3CX_GetDistance(sensors[0], &result);
  printf("dist1:%4d \r\n", result.ZoneResult[0].Distance[0]);
  /**
   * BTN1 bepaald of dat er gekalibreerd wordt of niet.
   * True zal kalibratie opstarten en de gegevens dumpen naar serial monitor
   * False zal de opgeslagen (hardcoded) values doorvoeren naar de sensoren
   */
  bool BTN2_state = false;

  // TODO
  // BTN2_state = HAL_GPIO_ReadPin(SW_1_GPIO_Port, SW_1_Pin);

  if (!BTN2_state)
  {
    while (1)
    {
      printf("Starting  \r\n");
      VL53L3CX_GetDistance(sensors[0], &result);
      printf("dist1:%4d \r\n", result.ZoneResult[0].Distance[0]);
    }
  }
  else
  {
    // Stuur alle SMD leds aan en blink 8 om de seconden (16 seconden).
    // Na de 15 seconden wordt de kalibratie uitgevoerd
    // Calibratie uitvoeren en plotten in serial monitor

    for (size_t i = 0; i < 16; i++)
    {
      HAL_GPIO_TogglePin(LED_0_GPIO_Port, LED_0_Pin);
      HAL_GPIO_TogglePin(LED_1_GPIO_Port, LED_1_Pin);
      HAL_GPIO_TogglePin(LED_2_GPIO_Port, LED_2_Pin);
      HAL_Delay(1000);
    }
  }
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
   */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);
  /** Initializes the RCC Oscillators according to the specified parameters
   * in the RCC_OscInitTypeDef structure.
   */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
   */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
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
  HAL_StatusTypeDef status =
      HAL_UART_Transmit(&huart2, (uint8_t *)data, len, 1000);

  // return # of bytes written - as best we can tell
  return (status == HAL_OK ? len : 0);
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
