/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* Private defines -----------------------------------------------------------*/

#define DEBUGGING

#define USART_TX_Pin GPIO_PIN_2
#define USART_TX_GPIO_Port GPIOA

#define USART_RX_Pin GPIO_PIN_3
#define USART_RX_GPIO_Port GPIOA

#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA

#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA

/** drukknoppen **/

#define B1_Pin GPIO_PIN_13
#define B1_GPIO_Port GPIOC

#define BTN1_Pin GPIO_PIN_6
#define BTN1_GPIO_Port GPIOB

#define BTN2_Pin GPIO_PIN_5
#define BTN2_GPIO_Port GPIOB

#define BTN3_Pin GPIO_PIN_2
#define BTN3_GPIO_Port GPIOA


/** LED PINNEN **/

#define LD2_Pin GPIO_PIN_5
#define LD2_GPIO_Port GPIOA

#define L_Y_Pin GPIO_PIN_7
#define L_Y_GPIO_Port GPIOA

#define L_R_Pin GPIO_PIN_3
#define L_R_GPIO_Port GPIOB

#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB

#define SMD1_Pin GPIO_PIN_10
#define SMD1_Port GPIOA

#define SMD2_Pin GPIO_PIN_5
#define SMD2_Port GPIOA

#define SMD3_Pin GPIO_PIN_6
#define SMD3_Port GPIOA

/** XSHUT PINNEN **/

#define XSHUT_0_Pin GPIO_PIN_0
#define XSHUT_0_Port GPIOA

#define XSHUT_1_Pin GPIO_PIN_1
#define XSHUT_1_Port GPIOA

#define XSHUT_2_Pin GPIO_PIN_10
#define XSHUT_2_Port GPIOB

#define XSHUT_3_Pin GPIO_PIN_0
#define XSHUT_3_Port GPIOB

#define XSHUT_4_Pin GPIO_PIN_1
#define XSHUT_4_Port GPIOC

/** GPIOI PINNEN **/

#define GPIOI_1_Pin GPIO_PIN_4
#define GPIOI_1_Port GPIOA
#define GPIOI_1_EXTI_IRQn EXTI4_IRQn

#define GPIOI_3_Pin GPIO_PIN_12
#define GPIOI_3_Port GPIOB
#define GPIOI_3_EXTI_IRQn EXTI15_10_IRQn

#define GPIOI_0_Pin GPIO_PIN_13
#define GPIOI_0_Port GPIOB
#define GPIOI_0_EXTI_IRQn EXTI15_10_IRQn

#define GPIOI_2_Pin GPIO_PIN_14
#define GPIOI_2_Port GPIOB
#define GPIOI_2_EXTI_IRQn EXTI15_10_IRQn

#define GPIOI_4_Pin GPIO_PIN_15
#define GPIOI_4_Port GPIOB
#define GPIOI_4_EXTI_IRQn EXTI15_10_IRQn


#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
