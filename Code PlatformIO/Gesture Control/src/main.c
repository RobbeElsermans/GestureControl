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

/* Private includes ----------------------------------------------------------*/

#include <string.h>
#include "53l3a2_ranging_sensor.h"
#include <stdio.h>
#include "app_tof.h"
#include "stdbool.h"    //Nodig om bool te kunnen gebruiken
#include <sys/unistd.h> // STDOUT_FILENO, STDERR_FI
#include <errno.h>
#include "calibrationData.h" //bevat methodes en instellingen om de sensoren te calibreren.

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
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_TIM3_Init(void);
static void MX_I2C3_Init(void);

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
  MX_TIM3_Init();
  MX_I2C3_Init();

  if (HAL_I2C_EnableListen_IT(&hi2c3) != HAL_OK)
  {
    /* Transfer error in reception process */
    Error_Handler();
  }

  MX_TOF_Init();

  /**
   * BTN1 bepaald of dat er gekalibreerd wordt of niet.
   * True zal kalibratie opstarten en de gegevens dumpen naar serial monitor
   * False zal de opgeslagen (hardcoded) values doorvoeren naar de sensoren
   */
  bool BTN2_state = false;

  BTN2_state = HAL_GPIO_ReadPin(BTN2_GPIO_Port, BTN2_Pin);

  if (!BTN2_state)
  {
    while (1)
    {
      printf("Starting  \r\n");
      MX_TOF_Process(&htim3, &hi2c3);
    }
  }
  else
  {
    // Stuur alle SMD leds aan en blink 8 om de seconden (16 seconden).
    // Na de 15 seconden wordt de kalibratie uitgevoerd
    // Calibratie uitvoeren en plotten in serial monitor

    for (size_t i = 0; i < 16; i++)
    {
      HAL_GPIO_TogglePin(SMD1_Port, SMD1_Pin);
      HAL_GPIO_TogglePin(SMD2_Port, SMD2_Pin);
      HAL_GPIO_TogglePin(SMD3_Port, SMD3_Pin);
      HAL_Delay(1000);
    }

    // Calibraties uitvoeren
    VL53LX_CalibrationData_t callData[RANGING_SENSOR_INSTANCES_NBR];

    RefSpadCal(VL53L3A2_DEV_LEFT);
    RefSpadCal(VL53L3A2_DEV_CENTER);
    RefSpadCal(VL53L3A2_DEV_RIGHT);
    HAL_GPIO_WritePin(SMD1_Port, SMD1_Pin, 1);
    // Callibratie van crosstalk (coverglas)
    xTalkCal(VL53L3A2_DEV_LEFT);
    xTalkCal(VL53L3A2_DEV_CENTER);
    xTalkCal(VL53L3A2_DEV_RIGHT);
    HAL_GPIO_WritePin(SMD2_Port, SMD2_Pin, 1);
    // xTalkCal(VL53L3A2_DEV_TOP);
    // xTalkCal(VL53L3A2_DEV_BOTTOM);

    // De offset bepalen zodat deze juist is is.
    offsetPerVcselCal(VL53L3A2_DEV_LEFT, 600);
    offsetPerVcselCal(VL53L3A2_DEV_CENTER, 600);
    offsetPerVcselCal(VL53L3A2_DEV_RIGHT, 600);
    offsetPerVcselCal(VL53L3A2_DEV_TOP, 600);
    offsetPerVcselCal(VL53L3A2_DEV_BOTTOM, 600);
    HAL_GPIO_WritePin(SMD3_Port, SMD3_Pin, 1);
    // Waardes opvragen
    callData[VL53L3A2_DEV_LEFT] = getCalibrationData(VL53L3A2_DEV_LEFT);
    callData[VL53L3A2_DEV_CENTER] = getCalibrationData(VL53L3A2_DEV_CENTER);
    callData[VL53L3A2_DEV_RIGHT] = getCalibrationData(VL53L3A2_DEV_RIGHT);
    callData[VL53L3A2_DEV_TOP] = getCalibrationData(VL53L3A2_DEV_TOP);
    callData[VL53L3A2_DEV_BOTTOM] = getCalibrationData(VL53L3A2_DEV_BOTTOM);

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

    setCalibrationData(VL53L3A2_DEV_LEFT, callData[VL53L3A2_DEV_LEFT]);
    setCalibrationData(VL53L3A2_DEV_CENTER, callData[VL53L3A2_DEV_CENTER]);
    setCalibrationData(VL53L3A2_DEV_RIGHT, callData[VL53L3A2_DEV_RIGHT]);
    setCalibrationData(VL53L3A2_DEV_TOP, callData[VL53L3A2_DEV_TOP]);
    setCalibrationData(VL53L3A2_DEV_BOTTOM, callData[VL53L3A2_DEV_BOTTOM]);

    HAL_GPIO_WritePin(SMD1_Port, SMD1_Pin, 0);
    HAL_GPIO_WritePin(SMD2_Port, SMD2_Pin, 0);
    HAL_GPIO_WritePin(SMD3_Port, SMD3_Pin, 0);

    // Omzetten naar variabelen
    int xtalk_bin_data[RANGING_SENSOR_INSTANCES_NBR][12];
    int xtalk_kcps[RANGING_SENSOR_INSTANCES_NBR][6];
    int xtalk_zero_distance[RANGING_SENSOR_INSTANCES_NBR];
    int offset[RANGING_SENSOR_INSTANCES_NBR][6];

    for (uint8_t i = 0; i < RANGING_SENSOR_INSTANCES_NBR; i++)
    {
      for (uint8_t j = 0; j < 6; j++)
      {
        xtalk_kcps[i][j] = callData[i].algo__xtalk_cpo_HistoMerge_kcps[j];
      }
    }

    for (uint8_t i = 0; i < RANGING_SENSOR_INSTANCES_NBR; i++)
    {
      for (uint8_t j = 0; j < 12; j++)
      {
        xtalk_bin_data[i][j] = callData[i].xtalkhisto.xtalk_shape.bin_data[j];
      }
    }

    for (uint8_t i = 0; i < RANGING_SENSOR_INSTANCES_NBR; i++)
    {
      offset[i][0] = callData[i].per_vcsel_cal_data.short_a_offset_mm;
      offset[i][1] = callData[i].per_vcsel_cal_data.short_b_offset_mm;
      offset[i][2] = callData[i].per_vcsel_cal_data.medium_a_offset_mm;
      offset[i][3] = callData[i].per_vcsel_cal_data.medium_b_offset_mm;
      offset[i][4] = callData[i].per_vcsel_cal_data.long_a_offset_mm;
      offset[i][5] = callData[i].per_vcsel_cal_data.long_b_offset_mm;
    }

    for (uint8_t i = 0; i < RANGING_SENSOR_INSTANCES_NBR; i++)
    {
      xtalk_zero_distance[i] = callData[i].xtalkhisto.xtalk_shape.zero_distance_phase;
    }

    // plotten naar serial monitor

    for (uint8_t i = 0; i < RANGING_SENSOR_INSTANCES_NBR; i++)
    {
      printf("instance %1d \r\n", i);

      // xtalk_bin_data
      printf("\r\n\txtalk_bin_data \r\n");
      for (size_t j = 0; j < 12; j++)
      {
        printf("%2d: %5d\r\n", j, xtalk_bin_data[i][j]);
      }

      // xtalk_kcps
      printf("\r\n\t xtalk_kcps \r\n");
      for (size_t j = 0; j < 6; j++)
      {
        printf("%2d: %5d\r\n", j, xtalk_kcps[i][j]);
      }

      // offset
      printf("\r\n\t offset \r\n");
      for (size_t j = 0; j < 6; j++)
      {
        printf("%2d: %5d\r\n", j, offset[i][j]);
      }

      // xtalk_zero_distance
      printf("\r\n\t xtalk_zero_distance \r\n");
      printf("%5d\r\n", xtalk_zero_distance[i]);

      printf("---------------------------------------------\r\n");
    }

    printf(" \r\n");

    while (1)
      ;
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

/**
 * @brief I2C3 Initialization Function
 * @param None
 * @retval None
 */
static void MX_I2C3_Init(void)
{
  hi2c3.Instance = I2C3;
  hi2c3.Init.ClockSpeed = 100000;
  hi2c3.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c3.Init.OwnAddress1 = 64;
  hi2c3.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c3.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c3.Init.OwnAddress2 = 0;
  hi2c3.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c3.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c3) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
 * @brief TIM3 Initialization Function
 * @param None
 * @retval None
 */
static void MX_TIM3_Init(void)
{

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 0;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 1023;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_PWM_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }

  HAL_TIM_MspPostInit(&htim3);
}

/**
 * @brief USART2 Initialization Function
 * @param None
 * @retval None
 */
static void MX_USART2_UART_Init(void)
{
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_MultiProcessor_Init(&huart2, 0, UART_WAKEUPMETHOD_IDLELINE) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : BTN1_Pin */
  GPIO_InitStruct.Pin = BTN1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(BTN1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : BTN2_Pin */
  GPIO_InitStruct.Pin = BTN2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(BTN2_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : BTN3_Pin */
  GPIO_InitStruct.Pin = BTN3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(BTN3_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LD2_Pin */
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : L_Y_Pin */
  GPIO_InitStruct.Pin = L_Y_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(L_Y_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : XSHUT_0 */
  GPIO_InitStruct.Pin = XSHUT_0_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(XSHUT_0_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : XSHUT_1 */
  GPIO_InitStruct.Pin = XSHUT_1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(XSHUT_1_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : XSHUT_2 */
  GPIO_InitStruct.Pin = XSHUT_2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(XSHUT_2_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : XSHUT_3 */
  GPIO_InitStruct.Pin = XSHUT_3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(XSHUT_3_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : XSHUT_4 */
  GPIO_InitStruct.Pin = XSHUT_4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(XSHUT_4_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : SMD1 */
  GPIO_InitStruct.Pin = SMD1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(SMD1_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : SMD2 */
  GPIO_InitStruct.Pin = SMD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(SMD2_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : SMD3 */
  GPIO_InitStruct.Pin = SMD3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(SMD3_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : RED */
  GPIO_InitStruct.Pin = L_R_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(L_R_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin Output Level */

  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(L_Y_GPIO_Port, L_Y_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(XSHUT_0_Port, XSHUT_0_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(XSHUT_1_Port, XSHUT_1_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(XSHUT_2_Port, XSHUT_2_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(XSHUT_3_Port, XSHUT_3_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(XSHUT_4_Port, XSHUT_4_Pin, GPIO_PIN_RESET);

  HAL_GPIO_WritePin(SMD1_Port, SMD1_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(SMD2_Port, SMD2_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(SMD3_Port, SMD3_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(L_R_GPIO_Port, L_R_Pin, GPIO_PIN_RESET);
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
