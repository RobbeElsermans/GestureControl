#include "gpio.h"

#include "stm32f4xx_hal.h"

#define R4_Pin GPIO_PIN_13
#define R4_GPIO_Port GPIOC
#define R2_Pin GPIO_PIN_0
#define R2_GPIO_Port GPIOC
#define R6_Pin GPIO_PIN_1
#define R6_GPIO_Port GPIOC
#define R1_Pin GPIO_PIN_2
#define R1_GPIO_Port GPIOC
#define C3_Pin GPIO_PIN_3
#define C3_GPIO_Port GPIOC

#define R5_Pin GPIO_PIN_4
#define R5_GPIO_Port GPIOA

#define R7_Pin GPIO_PIN_0
#define R7_GPIO_Port GPIOB

#define C4_Pin GPIO_PIN_15
#define C4_GPIO_Port GPIOA
#define C1_Pin GPIO_PIN_10
#define C1_GPIO_Port GPIOC
#define R3_Pin GPIO_PIN_11
#define R3_GPIO_Port GPIOC
#define C2_Pin GPIO_PIN_12
#define C2_GPIO_Port GPIOC

#define C5_Pin GPIO_PIN_7
#define C5_GPIO_Port GPIOB

#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB
#define LD2_Pin GPIO_PIN_5
#define LD2_GPIO_Port GPIOA

void gpio_initGpio(){
    GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, R4_Pin|R2_Pin|R6_Pin|R1_Pin
                          |C3_Pin|C1_Pin|R3_Pin|C2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, R5_Pin|LD2_Pin|C4_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, R7_Pin|C5_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : PCPin PCPin PCPin PCPin
                           PCPin PCPin PCPin PCPin */
  GPIO_InitStruct.Pin = R4_Pin|R2_Pin|R6_Pin|R1_Pin
                          |C3_Pin|C1_Pin|R3_Pin|C2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PAPin PAPin PAPin */
  GPIO_InitStruct.Pin = R5_Pin|LD2_Pin|C4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PBPin PBPin */
  GPIO_InitStruct.Pin = R7_Pin|C5_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}
// void gpio_get_gpio(gpio_matrix_t *gpio){
// ;;
// }

void gpio_set_gpio(gpio_t gpio ,int state){
    if(gpio == led1)
        HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, (GPIO_PinState)state);
    if(gpio == C1)
        HAL_GPIO_WritePin(C1_GPIO_Port, C1_Pin, (GPIO_PinState)state);
    if(gpio == C2)
        HAL_GPIO_WritePin(C2_GPIO_Port, C2_Pin, (GPIO_PinState)state);
    if(gpio == C3)
        HAL_GPIO_WritePin(C3_GPIO_Port, C3_Pin, (GPIO_PinState)state);
    if(gpio == C4)
        HAL_GPIO_WritePin(C4_GPIO_Port, C4_Pin, (GPIO_PinState)state);
    if(gpio == C5)
        HAL_GPIO_WritePin(C5_GPIO_Port, C5_Pin, (GPIO_PinState)state);
    if(gpio == R1)
        HAL_GPIO_WritePin(R1_GPIO_Port, R1_Pin, (GPIO_PinState)state);
    if(gpio == R2)
        HAL_GPIO_WritePin(R2_GPIO_Port, R2_Pin, (GPIO_PinState)state);
    if(gpio == R3)
        HAL_GPIO_WritePin(R3_GPIO_Port, R3_Pin, (GPIO_PinState)state);
    if(gpio == R4)
        HAL_GPIO_WritePin(R4_GPIO_Port, R4_Pin, (GPIO_PinState)state);
    if(gpio == R5)
        HAL_GPIO_WritePin(R5_GPIO_Port, R5_Pin, (GPIO_PinState)state);
    if(gpio == R6)
        HAL_GPIO_WritePin(R6_GPIO_Port, R6_Pin, (GPIO_PinState)state);
    if(gpio == R7)
        HAL_GPIO_WritePin(R7_GPIO_Port, R7_Pin, (GPIO_PinState)state);

    
}