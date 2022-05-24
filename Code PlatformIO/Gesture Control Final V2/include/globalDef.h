/**
 * @file globalDefines.h
 * @author Robbe Elsermans (robbe.elsermans@student.ap.be)
 * @brief Dit bestand bevat globaal gebruikte structs en enums
 * @version 1.0
 * @date 2022-05-20
 * 
 * This software is licensed under terms that can be found in the LICENSE file in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS and shared in the Public Domain
 * 
 */

#ifndef GLOBAL_DEF_H
#define GLOBAL_DEF_H


#include "stdint.h"
#include "stdbool.h"
#include "vl53l3cx.h"

#define LEFT 1
#define RIGHT 2
#define CENTER 0

    /**
   * @brief Enum die de statussen van de main loop onder handen neemt
   */
  typedef enum{
    STATE_INIT,
    STATE_CALIBRATE,
    STATE_START,
    STATE_GESTURE_CONTROL,
    STATE_STOP
  } mainStates_t;

    /**
   * @brief Enum die de statussen van de STATE_GESTURE_CONTROL loop onder handen neemt
   */
  typedef enum{
    STATE_GC_SAMPLE,
    STATE_GC_OBJECT,
    STATE_GC_START,
    STATE_GC_DETECT,
    STATE_GC_STOP
  } gestureControlStates_t;

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
 * @brief De mogelijke input en output pinnen die we gebruiken in dit project
 * 
 */
typedef enum{
    SW0,
    SW1,
    LED0,
    LED1,
    LED2,
    LED3,
    LED4,
    XSHUT0,
    XSHUT1,
    XSHUT2,
    XSHUT3,
    XSHUT4,
    GPIOI0,
    GPIOI1,
    GPIOI2,
    GPIOI3,
    GPIOI4,
    EN5V,
} gpio_t;

  /**
   * @brief Struct die de sensor pinout bijhoud
   * @param xshut De pin nummer de xshut pin staat
   * @param gpioi De pin nummer waarop de gpioi pin staat
   */
  typedef struct{
    gpio_t xshut;
    gpio_t gpioi;
  } senorPorts_t;

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
    OBJ = 0x20,
    NONE = 0x10
  } commands_t;

  /* USER CODE END ET */

  /* Exported constants --------------------------------------------------------*/
  /* USER CODE BEGIN EC */
#define AMOUNT_SENSOR 5
#define AMOUNT_SENSOR_USED 3

/**
 * @brief De mogelijke statussen die de output pinnen kunnen hebben
 * 
 */
typedef enum{
    resetPin = 0U,
    setPin,
} state_t;



#endif