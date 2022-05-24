#include "gpio.h"

#include "stm32f3xx_hal.h"

#define ENABLE_5V_Pin GPIO_PIN_13
#define ENABLE_5V_GPIO_Port GPIOC
#define XSHUT_0_Pin GPIO_PIN_0
#define XSHUT_0_GPIO_Port GPIOC
#define XSHUT_1_Pin GPIO_PIN_1
#define XSHUT_1_GPIO_Port GPIOC
#define XSHUT_2_Pin GPIO_PIN_2
#define XSHUT_2_GPIO_Port GPIOC
#define XSHUT_3_Pin GPIO_PIN_3
#define XSHUT_3_GPIO_Port GPIOC
#define LED_0_Pin GPIO_PIN_0
#define LED_0_GPIO_Port GPIOA
#define LED_1_Pin GPIO_PIN_1
#define LED_1_GPIO_Port GPIOA
#define LED_2_Pin GPIO_PIN_6
#define LED_2_GPIO_Port GPIOA
#define LED_3_Pin GPIO_PIN_7
#define LED_3_GPIO_Port GPIOA
#define XSHUT_4_Pin GPIO_PIN_4
#define XSHUT_4_GPIO_Port GPIOC
#define LED_4_Pin GPIO_PIN_0
#define LED_4_GPIO_Port GPIOB
#define SW_1_Pin GPIO_PIN_1
#define SW_1_GPIO_Port GPIOB
#define SW_2_Pin GPIO_PIN_2
#define SW_2_GPIO_Port GPIOB
#define GPIOI_0_Pin GPIO_PIN_12
#define GPIOI_0_GPIO_Port GPIOB
#define GPIOI_0_EXTI_IRQn EXTI15_10_IRQn
#define GPIOI_1_Pin GPIO_PIN_13
#define GPIOI_1_GPIO_Port GPIOB
#define GPIOI_1_EXTI_IRQn EXTI15_10_IRQn
#define GPIOI_2_Pin GPIO_PIN_14
#define GPIOI_2_GPIO_Port GPIOB
#define GPIOI_2_EXTI_IRQn EXTI15_10_IRQn
#define GPIOI_3_Pin GPIO_PIN_15
#define GPIOI_3_GPIO_Port GPIOB
#define GPIOI_3_EXTI_IRQn EXTI15_10_IRQn
#define GPIOI_4_Pin GPIO_PIN_6
#define GPIOI_4_GPIO_Port GPIOC
#define GPIOI_4_EXTI_IRQn EXTI9_5_IRQn

void gpio_initGpio(){

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, ENABLE_5V_Pin|XSHUT_0_Pin|XSHUT_1_Pin|XSHUT_2_Pin
                          |XSHUT_3_Pin|XSHUT_4_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LED_0_Pin|LED_1_Pin|LED_2_Pin|LED_3_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED_4_GPIO_Port, LED_4_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : PCPin PCPin PCPin PCPin
                           PCPin PCPin */
  GPIO_InitStruct.Pin = ENABLE_5V_Pin|XSHUT_0_Pin|XSHUT_1_Pin|XSHUT_2_Pin
                          |XSHUT_3_Pin|XSHUT_4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PAPin PAPin PAPin PAPin */
  GPIO_InitStruct.Pin = LED_0_Pin|LED_1_Pin|LED_2_Pin|LED_3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = LED_4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED_4_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PBPin PBPin */
  GPIO_InitStruct.Pin = SW_1_Pin|SW_2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PBPin PBPin PBPin PBPin */
  GPIO_InitStruct.Pin = GPIOI_0_Pin|GPIOI_1_Pin|GPIOI_2_Pin|GPIOI_3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = GPIOI_4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOI_4_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

}

state_t gpio_get_gpio(gpio_t gpio){
    if(gpio == SW0)
        return (state_t)HAL_GPIO_ReadPin(SW_1_GPIO_Port, SW_1_Pin);
    if(gpio == SW1)
        return (state_t)HAL_GPIO_ReadPin(SW_2_GPIO_Port, SW_2_Pin);
    if(gpio == LED0)
        return (state_t)HAL_GPIO_ReadPin(LED_0_GPIO_Port, LED_0_Pin);
    if(gpio == LED1)
        return (state_t)HAL_GPIO_ReadPin(LED_1_GPIO_Port, LED_1_Pin);
    if(gpio == LED2)
        return (state_t)HAL_GPIO_ReadPin(LED_2_GPIO_Port, LED_2_Pin);
    if(gpio == LED3)
        return (state_t)HAL_GPIO_ReadPin(LED_3_GPIO_Port, LED_3_Pin);
    if(gpio == LED4)
        return (state_t)HAL_GPIO_ReadPin(LED_4_GPIO_Port, LED_4_Pin);
    if(gpio == XSHUT0)
        return (state_t)HAL_GPIO_ReadPin(XSHUT_0_GPIO_Port, XSHUT_0_Pin);
    if(gpio == XSHUT1)
        return (state_t)HAL_GPIO_ReadPin(XSHUT_1_GPIO_Port, XSHUT_1_Pin);
    if(gpio == XSHUT2)
        return (state_t)HAL_GPIO_ReadPin(XSHUT_2_GPIO_Port, XSHUT_2_Pin);
    if(gpio == XSHUT3)
        return (state_t)HAL_GPIO_ReadPin(XSHUT_3_GPIO_Port, XSHUT_3_Pin);
    if(gpio == XSHUT4)
        return (state_t)HAL_GPIO_ReadPin(XSHUT_4_GPIO_Port, XSHUT_4_Pin);
    if(gpio == GPIOI0)
        return (state_t)HAL_GPIO_ReadPin(GPIOI_0_GPIO_Port, GPIOI_0_Pin);
    if(gpio == GPIOI1)
        return (state_t)HAL_GPIO_ReadPin(GPIOI_1_GPIO_Port, GPIOI_1_Pin);
    if(gpio == GPIOI2)
        return (state_t)HAL_GPIO_ReadPin(GPIOI_2_GPIO_Port, GPIOI_2_Pin);
    if(gpio == GPIOI3)
        return (state_t)HAL_GPIO_ReadPin(GPIOI_3_GPIO_Port, GPIOI_3_Pin);
    if(gpio == GPIOI4)
        return (state_t)HAL_GPIO_ReadPin(GPIOI_4_GPIO_Port, GPIOI_4_Pin);
    if(gpio == EN5V)
        return (state_t)HAL_GPIO_ReadPin(ENABLE_5V_GPIO_Port, ENABLE_5V_Pin);
    return resetPin;
}

void gpio_set_gpio(gpio_t gpio ,state_t state){
    if(gpio == SW0)
        HAL_GPIO_WritePin(SW_1_GPIO_Port, SW_1_Pin, (GPIO_PinState)state);
    if(gpio == SW1)
        HAL_GPIO_WritePin(SW_2_GPIO_Port, SW_2_Pin, (GPIO_PinState)state);
    if(gpio == LED0)
        HAL_GPIO_WritePin(LED_0_GPIO_Port, LED_0_Pin, (GPIO_PinState)state);
    if(gpio == LED1)
        HAL_GPIO_WritePin(LED_1_GPIO_Port, LED_1_Pin, (GPIO_PinState)state);
    if(gpio == LED2)
        HAL_GPIO_WritePin(LED_2_GPIO_Port, LED_2_Pin, (GPIO_PinState)state);
    if(gpio == LED3)
        HAL_GPIO_WritePin(LED_3_GPIO_Port, LED_3_Pin, (GPIO_PinState)state);
    if(gpio == LED4)
        HAL_GPIO_WritePin(LED_4_GPIO_Port, LED_4_Pin, (GPIO_PinState)state);
    if(gpio == XSHUT0)
        HAL_GPIO_WritePin(XSHUT_0_GPIO_Port, XSHUT_0_Pin, (GPIO_PinState)state);
    if(gpio == XSHUT1)
        HAL_GPIO_WritePin(XSHUT_1_GPIO_Port, XSHUT_1_Pin, (GPIO_PinState)state);
    if(gpio == XSHUT2)
        HAL_GPIO_WritePin(XSHUT_2_GPIO_Port, XSHUT_2_Pin, (GPIO_PinState)state);
    if(gpio == XSHUT3)
        HAL_GPIO_WritePin(XSHUT_3_GPIO_Port, XSHUT_3_Pin, (GPIO_PinState)state);
    if(gpio == XSHUT4)
        HAL_GPIO_WritePin(XSHUT_4_GPIO_Port, XSHUT_4_Pin, (GPIO_PinState)state);
    if(gpio == GPIOI0)
        HAL_GPIO_WritePin(GPIOI_0_GPIO_Port, GPIOI_0_Pin, (GPIO_PinState)state);
    if(gpio == GPIOI1)
        HAL_GPIO_WritePin(GPIOI_1_GPIO_Port, GPIOI_1_Pin, (GPIO_PinState)state);
    if(gpio == GPIOI2)
        HAL_GPIO_WritePin(GPIOI_2_GPIO_Port, GPIOI_2_Pin, (GPIO_PinState)state);
    if(gpio == GPIOI3)
        HAL_GPIO_WritePin(GPIOI_3_GPIO_Port, GPIOI_3_Pin, (GPIO_PinState)state);
    if(gpio == GPIOI4)
        HAL_GPIO_WritePin(GPIOI_4_GPIO_Port, GPIOI_4_Pin, (GPIO_PinState)state);
    if(gpio == EN5V)
        HAL_GPIO_WritePin(ENABLE_5V_GPIO_Port, ENABLE_5V_Pin, (GPIO_PinState)state);

}

void gpio_toggle_gpio(gpio_t gpio){
    
    gpio_set_gpio(gpio, !gpio_get_gpio(gpio));
}

gpio_t gpio_callBack_gpio(uint16_t gpio){
    if(gpio == GPIOI_0_Pin)
        return GPIOI0;
    if(gpio == GPIOI_1_Pin)
        return GPIOI1;
    if(gpio == GPIOI_2_Pin)
        return GPIOI2;
    if(gpio == GPIOI_3_Pin)
        return GPIOI3;
    if(gpio == GPIOI_4_Pin)
        return GPIOI4;
    
    return GPIOI0;
}