#include "unittest_transport.h"
#include "stm32f3xx_hal.h"

static UART_HandleTypeDef uartHandle;

void unittest_uart_begin()
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* USER CODE BEGIN USART1_MspInit 0 */

  /* USER CODE END USART1_MspInit 0 */
  /* USART1 clock enable */
  __HAL_RCC_USART1_CLK_ENABLE();

  __HAL_RCC_GPIOB_CLK_ENABLE();
  /**USART1 GPIO Configuration
  PB6     ------> USART1_TX
  PB7     ------> USART1_RX
  */
  GPIO_InitStruct.Pin = GPIO_PIN_6 | GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  uartHandle.Instance = USART1;
  uartHandle.Init.BaudRate = 115200;
  uartHandle.Init.WordLength = UART_WORDLENGTH_8B;
  uartHandle.Init.StopBits = UART_STOPBITS_1;
  uartHandle.Init.Parity = UART_PARITY_NONE;
  uartHandle.Init.Mode = UART_MODE_TX_RX;
  uartHandle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  uartHandle.Init.OverSampling = UART_OVERSAMPLING_16;
  uartHandle.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  uartHandle.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_SWAP_INIT;
  uartHandle.AdvancedInit.Swap = UART_ADVFEATURE_SWAP_ENABLE;
  if (HAL_UART_Init(&uartHandle) != HAL_OK)
  {
    while(1){}
  }
}

  void unittest_uart_putchar(char c)
  {
    HAL_UART_Transmit(&uartHandle, (uint8_t *)(&c), 1, 1000);
  }

  void unittest_uart_flush() {}

  void unittest_uart_end()
  {
    __HAL_RCC_USART1_CLK_DISABLE();
    __HAL_RCC_GPIOB_CLK_DISABLE();
    __HAL_RCC_GPIOB_CLK_DISABLE();
  }