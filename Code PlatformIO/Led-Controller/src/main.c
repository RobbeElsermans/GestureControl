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
#include "dma.h"
#include "i2c.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>      //Om printf te gebruiken
#include <stdlib.h>     //Bibliotheken om met string conversies te werken
#include <string.h>     //Om met strings te kunnen werken
#include "stdbool.h"    //Nodig om bool te kunnen gebruiken
#include <sys/unistd.h> // STDOUT_FILENO, STDERR_FI _wirte onderdeel
#include <errno.h>      //_wirte onderdeel
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
#define LED_MATRIX_WIDTH 5  // 0->4
#define LED_MATRIX_HEIGHT 7 // 0->6

int led_matrix[LED_MATRIX_HEIGHT][LED_MATRIX_WIDTH] =
    {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}};

int led_rows[LED_MATRIX_HEIGHT][2] = {
    {R1_GPIO_Port, R1_Pin},
    {R2_GPIO_Port, R2_Pin},
    {R3_GPIO_Port, R3_Pin},
    {R4_GPIO_Port, R4_Pin},
    {R5_GPIO_Port, R5_Pin},
    {R6_GPIO_Port, R6_Pin},
    {R7_GPIO_Port, R7_Pin}};

int led_columns[LED_MATRIX_WIDTH][2] = {
    {C1_GPIO_Port, C1_Pin},
    {C2_GPIO_Port, C2_Pin},
    {C3_GPIO_Port, C3_Pin},
    {C4_GPIO_Port, C4_Pin},
    {C5_GPIO_Port, C5_Pin}};

int posx = 0;
int posy = 0;

typedef enum
{
  DIM = 0x25,
  RL = 0x22,
  LR = 0x21,
  UD = 0x23,
  DU = 0x24,
  OBJ = 0x20,
  NONE = 0x10
} commands_t;

commands_t commando = NONE;
commands_t prevCommando = NONE;

HAL_StatusTypeDef status = HAL_ERROR;
uint8_t buf = 0;
uint8_t counter = 0;
uint8_t addrs = 0x20 << 1;

volatile bool isSend = false;
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
  MX_USART2_UART_Init();
  MX_DMA_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */

  bool hasReset = false;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    counter++;

    // I2C stuff
    // HAL_I2C_Master_Transmit_IT(&hi2c1, addrs, &counter, 1);

    status = HAL_I2C_Master_Transmit_IT(&hi2c1, addrs, &counter, 1);

    printf("buf: %3d \r\n", buf);
    commando = (commands_t)buf;
    // int x = 0;
    // while (x < 50)
    // {

    if (commando >= OBJ)
    {
      if (hasReset)
        hasReset = false;
      uint8_t i = 0;
      uint8_t j = 0;
      for (i = 0; i < LED_MATRIX_HEIGHT; i++)
      {
        for (j = 0; j < LED_MATRIX_WIDTH; j++)
        {
          HAL_GPIO_WritePin((GPIO_TypeDef *)led_columns[j][0], led_columns[j][1], led_matrix[i][j]);
          HAL_GPIO_WritePin((GPIO_TypeDef *)led_rows[i][0], led_rows[i][1], led_matrix[i][j]);

          if (led_matrix[i][j])
            HAL_Delay(1);
        }
      }
    }
    else
    {
      HAL_Delay(500);
      HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);

      if (hasReset == false)
      {
        hasReset = true;
        for (uint8_t col = 0; col < LED_MATRIX_WIDTH; col++)
        {
          HAL_GPIO_WritePin((GPIO_TypeDef *)led_columns[col][0], led_columns[col][1], 0);
        }
      }
    }

    if (commando == OBJ)
    {
      HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, 1);
    }
    else if (commando > OBJ)
    {
      HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, 0);
    }

    //   x++;
    // }
    led_matrix[posy][posx] = 0;

    // Ontvang data
    if (commando == RL && prevCommando == OBJ)
      posx--;

    if (commando == LR && prevCommando == OBJ)
      posx++;

    if (posx >= LED_MATRIX_WIDTH)
      posx = 0;
    if (posx < 0)
      posx = LED_MATRIX_WIDTH - 1;

    if (commando == UD && prevCommando == OBJ)
      posy++;

    if (commando == DU && prevCommando == OBJ)
      posy--;

    if (posy >= LED_MATRIX_HEIGHT)
      posy = 0;
    if (posy < 0)
      posy = LED_MATRIX_HEIGHT - 1;

    led_matrix[posy][posx] = 1;

    prevCommando = commando;
    HAL_Delay(10);
    /* USER CODE END WHILE */

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
void HAL_I2C_MasterTxCpltCallback(I2C_HandleTypeDef *hi2c)
{
  status = HAL_I2C_Master_Receive(&hi2c1, addrs, &buf, 1, 100);
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
