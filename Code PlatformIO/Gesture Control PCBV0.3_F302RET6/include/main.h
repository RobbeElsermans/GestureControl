/* USER CODE BEGIN Header */
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
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f3xx_hal.h"

  /* Private includes ----------------------------------------------------------*/
  /* USER CODE BEGIN Includes */

  /* USER CODE END Includes */

  /* Exported types ------------------------------------------------------------*/
  /* USER CODE BEGIN ET */
  typedef enum SensorDef
  {
    CENTER = 0,
    LEFT = 4,
    RIGHT = 1,
    TOP = 2,
    BOTTOM = 3,
  } sensorDev;

  typedef enum commands
  {
    DIM = 0x25,
    RL = 0x22,
    LR = 0x21,
    UD = 0x23,
    DU = 0x24,
    NONE = 0x10
  } commands;

  typedef struct resultaat
  {
    long distance;
    int8_t status;
    long timestamp;
  } Resultaat_t;
  /* USER CODE END ET */

  /* Exported constants --------------------------------------------------------*/
  /* USER CODE BEGIN EC */
#define amountSensor 5
  /* USER CODE END EC */

  /* Exported macro ------------------------------------------------------------*/
  /* USER CODE BEGIN EM */

  /* USER CODE END EM */

  /* Exported functions prototypes ---------------------------------------------*/
  void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
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
  /* USER CODE BEGIN Private defines */

  /* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
