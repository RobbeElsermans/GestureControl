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
#include "i2c.h"
#include "usart.h"
#include "gpio.h"
#include "stm32f3xx_hal.h"
#include <sys/unistd.h> // STDOUT_FILENO, STDERR_FI
#include <errno.h>
#include "stdbool.h"
#include "vl53lx_api.h"
#include "calibrationData.h" //bevat methodes en instellingen om de sensoren te calibreren.
#include "GestureDetectObject.h"
#include "GestureDetect.h"
#include "SensorFunctions.h"
#include "calculations.h"

// Toggle for data collection
#define DATACOLLECTION

// Main states
static mainStates_t mainState = STATE_INIT;

// gesture Control states
static gestureControlStates_t gestureControlState = STATE_GC_SAMPLE;

// Sensor define
static sensorData_t sensoren[AMOUNT_SENSOR_USED];

#ifdef DATACOLLECTION
static long timerDataCollection = 0;
#define TIMER_DATA_COLLECTION_TIMEOUT 20 // aantal milliseconden per meeting
#endif

bool objectPresent = false;
bool prevObjectPresent = false;

// Commando enum waarmee we de commando's opslaan
commands_t commando = NONE;

// Timer die het commando voor TIMER_COMMAND_TIMEOUT seconden aanhoud
static float timerCommand = 0;
static bool timerCommandSet = false;   // Start in false state
#define TIMER_COMMAND_TIMEOUT 2000 // 2 seconden

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void handle_led();
void handle_commandTimer();
void handle_data(uint8_t id);
void perform_calibration();
void perform_init();

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

    MX_I2C2_Init();

    MX_USART1_UART_Init();

    //main while loop
    while (1)
    {
        switch (mainState)
        {
        case STATE_INIT:

            perform_init();

            mainState = STATE_CALIBRATE;
            break;
        case STATE_CALIBRATE:

            perform_calibration();

            mainState = STATE_START;
            break;
        case STATE_START:
            if (!sensoren[CENTER].sensor.IsRanging)
                sensorFunctions_startSensor(&sensoren[CENTER]);
            mainState = STATE_GESTURE_CONTROL;
            /* code */
            break;
        case STATE_GESTURE_CONTROL:
            // Doe alles van meetingen, detectie, commands

            switch (gestureControlState)
            {
            case STATE_GC_SAMPLE:
                handle_data(CENTER);

                if (objectPresent)
                {
                    handle_data(LEFT);
                    handle_data(RIGHT);
                }

                gestureControlState = STATE_GC_OBJECT;
                break;
            case STATE_GC_OBJECT:
                objectPresent = gestureDetectObject_ckeckObjectPresent(&sensoren[CENTER], &objectPresent);

                if (objectPresent && !prevObjectPresent)
                {
                    gestureControlState = STATE_GC_START;
                }
                else if (!objectPresent && prevObjectPresent)
                {
                    gestureControlState = STATE_GC_STOP;
                }
                else if (objectPresent && prevObjectPresent)
                {
                    gestureControlState = STATE_GC_DETECT;
                }
                else
                {
                    gestureControlState = STATE_GC_SAMPLE;
                }

                prevObjectPresent = objectPresent;
                break;
            case STATE_GC_START:
                sensorFunctions_startSensor(&sensoren[LEFT]);
                sensorFunctions_startSensor(&sensoren[RIGHT]);

                gestureControlState = STATE_GC_SAMPLE;
                /* code */
                break;
            case STATE_GC_DETECT:
                if (commando == OBJ)
                {
                    int8_t val = gestureDetect_detectgesture(sensoren);
                    if (val != -1)
                    {
                        commando = val;
                    }
                }
                gestureControlState = STATE_GC_SAMPLE;
                /* code */
                break;
            case STATE_GC_STOP:
                sensorFunctions_stopSensor(&sensoren[LEFT]);
                sensorFunctions_stopSensor(&sensoren[RIGHT]);

                gestureControlState = STATE_GC_SAMPLE;
                /* code */
                break;
            default:
                break;
            }

            gestureDetect_checkResetTimerGesture();

            handle_commandTimer();
            // Commando's uitsturen
            handle_led();

#ifdef DATACOLLECTION
            // DataCollection
            if (((HAL_GetTick() - timerDataCollection) > TIMER_DATA_COLLECTION_TIMEOUT))
            {
                // printf("L%d, C%d, R%d\r\n", leftDistance, centerDistance, rightDistance);
                timerDataCollection = HAL_GetTick();
                //printf("%d,%d\t%d,%d\t%d,%d\r\n", (int)sensoren[LEFT].resultaat.distance, (int)sensoren[LEFT].resultaat.status, (int)sensoren[CENTER].resultaat.distance, (int)sensoren[CENTER].resultaat.status, (int)sensoren[RIGHT].resultaat.distance, (int)sensoren[RIGHT].resultaat.status);
                printf("L%d, C%d, R%d\r\n", (int)sensoren[LEFT].resultaat.meanDistance, (int)sensoren[CENTER].resultaat.meanDistance, (int)sensoren[RIGHT].resultaat.meanDistance);
                //printf("%2d\r\n", commando);
            }
#endif

            int8_t buf;
            HAL_I2C_Slave_Receive_IT(&hi2c2, &buf, sizeof(buf));
            // I2C aanzetten om iets te ontvangen in interrupt modus.
            
            break;
        case STATE_STOP:
            sensorFunctions_stopSensor(&sensoren[CENTER]);
            while (1)
                ;
            break;

        default:
            break;
        }
        HAL_Delay(1);
    }
}

void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1|RCC_PERIPHCLK_I2C1
                              |RCC_PERIPHCLK_I2C2;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_SYSCLK;
  PeriphClkInit.I2c2ClockSelection = RCC_I2C2CLKSOURCE_SYSCLK;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
  HAL_RCC_MCOConfig(RCC_MCO, RCC_MCO1SOURCE_SYSCLK, RCC_MCODIV_1);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    for (uint8_t i = 0; i < AMOUNT_SENSOR_USED; i++)
    {
        if (sensoren[i].sensorPorts.gpioi_pin == GPIO_Pin)
        {
            sensoren[i].isReady = true;
        }
    }
}

int _write(int file, char *data, int len)
{
    if ((file != STDOUT_FILENO) && (file != STDERR_FILENO))
    {
        errno = EBADF;
        return -1;
    }

    // arbitrary timeout 1000
    HAL_StatusTypeDef status = HAL_UART_Transmit(&huart1, (uint8_t *)data, len, 1000);

    // return # of bytes written - as best we can tell
    return (status == HAL_OK ? len : 0);
}

void HAL_I2C_SlaveRxCpltCallback(I2C_HandleTypeDef *hi2c)
{
    //HAL_I2C_Slave_Transmit_IT(&hi2c2, (uint8_t *)commando, sizeof(commando));
    HAL_I2C_Slave_Transmit_IT(&hi2c2, (uint8_t *)&commando, sizeof(commando));
}

void perform_init()
{
    sensoren[CENTER].sensorPorts.gpioi_pin = (uint16_t)GPIOI_2_Pin;
    sensoren[CENTER].sensorPorts.gpioi_port = GPIOI_2_GPIO_Port;
    sensoren[CENTER].sensorPorts.xshut_pin = XSHUT_2_Pin;
    sensoren[CENTER].sensorPorts.xshut_port = XSHUT_2_GPIO_Port;
    sensoren[CENTER].id = CENTER;

    // left -> 1
    sensoren[LEFT].sensorPorts.gpioi_pin = GPIOI_1_Pin;
    sensoren[LEFT].sensorPorts.gpioi_port = GPIOI_1_GPIO_Port;
    sensoren[LEFT].sensorPorts.xshut_pin = XSHUT_1_Pin;
    sensoren[LEFT].sensorPorts.xshut_port = XSHUT_1_GPIO_Port;
    sensoren[LEFT].id = LEFT;

    // right -> 2
    sensoren[RIGHT].sensorPorts.gpioi_pin = GPIOI_3_Pin;
    sensoren[RIGHT].sensorPorts.gpioi_port = GPIOI_3_GPIO_Port;
    sensoren[RIGHT].sensorPorts.xshut_pin = XSHUT_3_Pin;
    sensoren[RIGHT].sensorPorts.xshut_port = XSHUT_3_GPIO_Port;
    sensoren[RIGHT].id = RIGHT;

    HAL_GPIO_WritePin(XSHUT_0_GPIO_Port, XSHUT_0_Pin, 0);
    HAL_GPIO_WritePin(XSHUT_1_GPIO_Port, XSHUT_1_Pin, 0);
    HAL_GPIO_WritePin(XSHUT_2_GPIO_Port, XSHUT_2_Pin, 0);
    HAL_GPIO_WritePin(XSHUT_3_GPIO_Port, XSHUT_3_Pin, 0);
    HAL_GPIO_WritePin(XSHUT_4_GPIO_Port, XSHUT_4_Pin, 0);

    HAL_Delay(20);

    CUSTOM_VL53L3CX_I2C_Init();

    // De sensoren initialiseren
    sensorFunctions_initSensor(&sensoren[CENTER]);
    HAL_Delay(2);
    sensorFunctions_initSensor(&sensoren[LEFT]);
    HAL_Delay(2);
    sensorFunctions_initSensor(&sensoren[RIGHT]);
    HAL_Delay(2);
}

void perform_calibration()
{
    // Als de drukknop SW_1 actief is, wordt er gekalibreerd
    if (HAL_GPIO_ReadPin(SW_1_GPIO_Port, SW_1_Pin))
    // if(true)
    {
        calibrationData_getCalibrate(&sensoren[CENTER]);
        calibrationData_getCalibrate(&sensoren[LEFT]);
        calibrationData_getCalibrate(&sensoren[RIGHT]);

        sensorFunctions_startSensor(&sensoren[CENTER]);
        sensorFunctions_startSensor(&sensoren[LEFT]);
        sensorFunctions_startSensor(&sensoren[RIGHT]);
        while (1)
        {
            sensorFunctions_getData(&sensoren[CENTER]);
            HAL_Delay(1);
            sensorFunctions_getData(&sensoren[LEFT]);
            HAL_Delay(1);
            sensorFunctions_getData(&sensoren[RIGHT]);
            HAL_Delay(1);
            HAL_Delay(200);
            printf("%d,%d\t%d,%d\t%d,%d\r\n", (int)sensoren[LEFT].resultaat.distance, (int)sensoren[LEFT].resultaat.status, (int)sensoren[CENTER].resultaat.distance, (int)sensoren[CENTER].resultaat.status, (int)sensoren[RIGHT].resultaat.distance, (int)sensoren[RIGHT].resultaat.status);
        }
    }
    else
    {
        calibrationData_setCalibrate(&sensoren[CENTER]);
        calibrationData_setCalibrate(&sensoren[LEFT]);
        calibrationData_setCalibrate(&sensoren[RIGHT]);

        // sensorFunctions_startSensor(&sensoren[CENTER]);
        // sensorFunctions_startSensor(&sensoren[LEFT]);
        // sensorFunctions_startSensor(&sensoren[RIGHT]);
        // while (1)
        // {
        //   sensorFunctions_getData(&sensoren[CENTER]);
        //   HAL_Delay(1);
        //   sensorFunctions_getData(&sensoren[LEFT]);
        //   HAL_Delay(1);
        //   sensorFunctions_getData(&sensoren[RIGHT]);
        //   HAL_Delay(1);
        //   HAL_Delay(200);
        //   printf("%d,%d\t%d,%d\t%d,%d\r\n", (int)sensoren[LEFT].resultaat.distance, (int)sensoren[LEFT].resultaat.status, (int)sensoren[CENTER].resultaat.distance, (int)sensoren[CENTER].resultaat.status, (int)sensoren[RIGHT].resultaat.distance, (int)sensoren[RIGHT].resultaat.status);
        // }
    }
}

void handle_data(uint8_t id)
{
    sensoren[id].isReady = sensorFunctions_getData(&sensoren[id]);
    calculations_setMeanVal(&sensoren[id]);
    sensoren[id].resultaat.meanDistance = calculations_getMean(sensoren[id].id);
}

void handle_commandTimer()
{
    // Commando resetten
    if (!timerCommandSet && commando != NONE && commando != OBJ)
    {
        timerCommandSet = true;
        timerCommand = HAL_GetTick();
        // printf("command: %2d\r\n", commando);
    }
    if ((HAL_GetTick() - timerCommand) >= TIMER_COMMAND_TIMEOUT)
    {
        timerCommandSet = false;
        if(objectPresent)
            commando = OBJ;
        else
            commando = NONE;
    }
}

void handle_led()
{
    switch (commando)
    {
    case NONE:
        HAL_GPIO_WritePin(LED_0_GPIO_Port, LED_0_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(LED_1_GPIO_Port, LED_1_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(LED_2_GPIO_Port, LED_2_Pin, GPIO_PIN_RESET);
        break;
    case RL:
        HAL_GPIO_WritePin(LED_0_GPIO_Port, LED_0_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(LED_1_GPIO_Port, LED_1_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(LED_2_GPIO_Port, LED_2_Pin, GPIO_PIN_RESET);
        break;
    case LR:
        HAL_GPIO_WritePin(LED_0_GPIO_Port, LED_0_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(LED_1_GPIO_Port, LED_1_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(LED_2_GPIO_Port, LED_2_Pin, GPIO_PIN_RESET);
        break;
    case UD:
        HAL_GPIO_WritePin(LED_0_GPIO_Port, LED_0_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(LED_1_GPIO_Port, LED_1_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(LED_2_GPIO_Port, LED_2_Pin, GPIO_PIN_RESET);
        break;
    case DU:
        HAL_GPIO_WritePin(LED_0_GPIO_Port, LED_0_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(LED_1_GPIO_Port, LED_1_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(LED_2_GPIO_Port, LED_2_Pin, GPIO_PIN_SET);
        break;
    case DIM:
        HAL_GPIO_WritePin(LED_0_GPIO_Port, LED_0_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(LED_1_GPIO_Port, LED_1_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(LED_2_GPIO_Port, LED_2_Pin, GPIO_PIN_SET);
        break;

    default:
        HAL_GPIO_WritePin(LED_0_GPIO_Port, LED_0_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(LED_1_GPIO_Port, LED_1_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(LED_2_GPIO_Port, LED_2_Pin, GPIO_PIN_RESET);
        break;
    }

    HAL_GPIO_WritePin(LED_3_GPIO_Port, LED_3_Pin, objectPresent);
    HAL_GPIO_TogglePin(LED_4_GPIO_Port, LED_4_Pin);
}

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