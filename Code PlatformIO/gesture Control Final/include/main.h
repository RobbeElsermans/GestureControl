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
#include "stdbool.h"
#include "vl53l3cx.h"
  /* USER CODE END Includes */

  /* Exported types ------------------------------------------------------------*/
  /* USER CODE BEGIN ET */
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

#define LEFT 1
#define RIGHT 2
#define CENTER 0
    /**
   * @brief Enum die de XSHUT en GPIOI pin bevat. Dit maakt de code duidelijker
   */
  typedef enum{
    XSHUT_4 = 4,
    XSHUT_3 = 3,
    XSHUT_2 = 2,
    XSHUT_1 = 1,
    XSHUT_0 = 0
  } sensorDev_t;

  /**
   * @brief Struct die de sensor pinout bijhoud
   * @param xshut_port De poort waarop de xshut pin staat
   * @param xshut_pin De pin nummer waarop de xshut pin staat
   * @param gpioi_port De poort waarop de gpioi pin staat
   * @param gpioi_pin De pin nummer waarop de xshut pin staat
   */
  typedef struct{
    GPIO_TypeDef* xshut_port;
    uint16_t xshut_pin;
    GPIO_TypeDef* gpioi_port;
    uint16_t gpioi_pin;
  } senorPorts_t;

    /**
   * @brief Struct die plaats en id van de sensor bijhoud 
   * @param gpioPin zal de XSHUT en GPIOI locatie definiëren
   * @param id Zal de nummer zijn van de sensor. Dit staat los van de gpioPin
   */
  typedef struct
  {
    sensorDev_t gpioPin;
    uint8_t id;
  } sensorDefinition_t;

  /**
   * @brief Struct die de meet waardes bijhoud
   * @param distance zal de ruwe afstand bewaren
   * @param status zal de ruwe status code bewaren
   * @param meanDistance zal een gemiddelde bijhouden van de afstand 
   * @param timestamp het tijdstip waarop de meeting is genomen
   */
  typedef struct
  {
    long distance;
    int8_t status;
    long meanDistance;
    long timestamp;
  } resultaat_t;

  /**
   * @brief Struct die al de sensor gegevens bijhoud
   * @param isReady De interrupt flag die op true zal staan bij een interrupt
   * @param hasRead De 1ste meeting overslaan bool
   * @param resultaat Struct die de meet waardes bijhoud
   * @param sensorPorts Struct die de sensor pinout bijhoud
   * @param sensor Struct die het sensor object bevat
   * @param id id van de sensor
   */
  typedef struct
  {
    volatile bool isReady;
    volatile bool hasRead;
    resultaat_t resultaat;
    senorPorts_t sensorPorts;
    VL53L3CX_Object_t sensor;
    uint8_t id;
  } sensorData_t;

    /**
   * @brief Enum die de mogelijke commando's bevat 
   */
  typedef enum
  {
    DIM = 0x25,
    RL = 0x22,
    LR = 0x21,
    UD = 0x23,
    DU = 0x24,
    NONE = 0x10
  } commands_t;

  /* USER CODE END ET */

  /* Exported constants --------------------------------------------------------*/
  /* USER CODE BEGIN EC */
#define AMOUNT_SENSOR 5
#define AMOUNT_SENSOR_USED 3
  /* USER CODE END EC */

  /* Exported macro ------------------------------------------------------------*/
  /* USER CODE BEGIN EM */

  /* USER CODE END EM */

  /* Exported functions prototypes ---------------------------------------------*/
  void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/

  /* USER CODE BEGIN Private defines */

  /* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
