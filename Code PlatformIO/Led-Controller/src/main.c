
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/

#include <stdio.h>      //Om printf te gebruiken
#include <stdlib.h>     //Bibliotheken om met string conversies te werken
#include <string.h>     //Om met strings te kunnen werken
#include "stdbool.h"    //Nodig om bool te kunnen gebruiken
#include <sys/unistd.h> // STDOUT_FILENO, STDERR_FI _wirte onderdeel
#include <errno.h>      //_wirte onderdeel

I2C_HandleTypeDef hi2c1;

UART_HandleTypeDef huart2;

#define led_matrix_width 5  // 0->4
#define led_matrix_height 7 // 0->6

int led_matrix[led_matrix_height][led_matrix_width] =
    {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}};

int led_rows[led_matrix_height][2] = {
    {GPIOC, GPIO_PIN_2},
    {GPIOC, GPIO_PIN_0},
    {GPIOC, GPIO_PIN_11},
    {GPIOC, GPIO_PIN_13},
    {GPIOA, GPIO_PIN_4},
    {GPIOC, GPIO_PIN_1},
    {GPIOB, GPIO_PIN_0}};

int led_columns[led_matrix_width][2] = {
    {GPIOC, GPIO_PIN_10},
    {GPIOC, GPIO_PIN_12},
    {GPIOC, GPIO_PIN_3},
    {GPIOA, GPIO_PIN_15},
    {GPIOB, GPIO_PIN_7}};

int posx = 0;
int posy = 0;

enum commands
{
  DIM = 0x25,
  RL = 0x22,
  LR = 0x21,
  UD = 0x23,
  DU = 0x24,
  NONE = 0x10
};

typedef enum commands command_t;

command_t commando = NONE;
command_t prevCommando = NONE;

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_I2C1_Init(void);

int main()
{
  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_I2C1_Init();

  HAL_StatusTypeDef status = HAL_ERROR;
  uint8_t buf = 0;
  uint8_t counter = 0;
  uint8_t addrs = 0x20 << 1;

  for (uint8_t row = 0; row < led_matrix_height; row++)
  {
    HAL_GPIO_WritePin(led_rows[row][0], led_rows[row][1], 1);
  }
  for (uint8_t col = 0; col < led_matrix_width; col++)
  {
    HAL_GPIO_WritePin(led_columns[col][0], led_columns[col][1], 1);
    HAL_Delay(200);
  }
  HAL_Delay(200);
  for (uint8_t col = 0; col < led_matrix_width; col++)
  {
    HAL_GPIO_WritePin(led_columns[col][0], led_columns[col][1], 0);
  }

  while (1)
  {
    counter++;

    // I2C stuff
    status = HAL_I2C_Master_Transmit(&hi2c1, addrs, &counter, 1, 200);

    if (status == HAL_OK)
    {
      status = HAL_I2C_Master_Receive(&hi2c1, addrs, &buf, 1, 100);
    }

    HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
    printf("buf: %3d \r\n", buf);
    commando = (command_t)buf;
    // int x = 0;
    // while (x < 50)
    // {
    for (uint8_t col = 0; col < led_matrix_width; col++)
    {
      // Reset de rijen als commando veranderd is
      for (uint8_t col1 = 0; col1 < led_matrix_height; col1++)
      {
        HAL_GPIO_WritePin(led_columns[col1][0], led_columns[col1][1], 0);
      }
      // Zet de kolommen klaar
      for (uint8_t row = 0; row < led_matrix_height; row++)
      {
        HAL_GPIO_WritePin(led_rows[row][0], led_rows[row][1], led_matrix[row][col]);
      }

      // voer de rij door
      HAL_GPIO_WritePin(led_columns[col][0], led_columns[col][1], 1);
      HAL_Delay(1);
    }
    //   x++;
    // }
    led_matrix[posy][posx] = 0;

    // Ontvang data
    if (commando == RL && prevCommando == NONE)
      posx--;

    if (commando == LR && prevCommando == NONE)
      posx++;

    if (posx >= led_matrix_width)
      posx = 0;
    if (posx < 0)
      posx = led_matrix_width - 1;

    if (commando == UD && prevCommando == NONE)
      posy++;

    if (commando == DU && prevCommando == NONE)
      posy--;

    if (posy >= led_matrix_height)
      posy = 0;
    if (posy < 0)
      posy = led_matrix_height - 1;

    led_matrix[posy][posx] = 1;

    prevCommando = commando;
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
 * @brief I2C1 Initialization Function
 * @param None
 * @retval None
 */
static void MX_I2C1_Init(void)
{
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
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

  /*Configure GPIO pin Output Level */
  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13 | GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1 | LD2_Pin | GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0 | GPIO_PIN_7, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_RESET);

  /*Configure GPIO pins : PC13 PC0 PC1 PC2
                           PC3 PC10 PC11 PC12 */
  GPIO_InitStruct.Pin = GPIO_PIN_13 | GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PA1 PAPin PA15 */
  GPIO_InitStruct.Pin = GPIO_PIN_1 | LD2_Pin | GPIO_PIN_15 | GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0 PB7 */
  GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : GPIOD Matrix */
  GPIO_InitStruct.Pin = GPIO_PIN_2;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
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
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
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