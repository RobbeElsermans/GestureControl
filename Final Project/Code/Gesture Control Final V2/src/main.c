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
#include "calibrationData.h" //bevat methodes en instellingen om de sensoren te calibreren.
#include "GestureDetectObject.h"
#include "GestureDetect.h"
#include "SensorFunctions.h"
#include "calculations.h"

/**
 * @brief Deze define wordt gebruikt om de data te plotten over seriële communicatie. Dit kan dan nadien gebruikt worden
 * met de gemaakte python scripts om de data op te slaan en te visualiseren.
 */
#define DATACOLLECTION

/**
 * @brief Deze mainStates_t enum bevat de statussen die de main loop kan bevatten
 *
 */
static mainStates_t mainState = STATE_INIT;

/**
 * @brief Deze gestureControlStates_t enum bevat de statussen die binnenin de status STATE_GESTURE_CONTROL worden overlopen
 *
 */
static gestureControlStates_t gestureControlState = STATE_GC_SAMPLE;

/**
 * @brief Sensor definitie
 *
 */
static sensorData_t sensoren[AMOUNT_SENSOR_USED];

#ifdef DATACOLLECTION
static long timerDataCollection = 0;
#define TIMER_DATA_COLLECTION_TIMEOUT 20 // aantal milliseconden per meeting
#endif

/**
 * @brief flag dat bijhoud of dat er een object aanwezig is
 *
 */
bool objectPresent = false;
bool prevObjectPresent = false;

/**
 * @brief command_t enum waarmee we de huidige commando bewaren
 *
 */
commands_t commando = NONE;
uint8_t buf;

/**
 * @brief Timer die het commando voor TIMER_COMMAND_TIMEOUT seconden aanhoud
 *
 */
static float timerCommand = 0;
static bool timerCommandSet = false; // Start in false state
#define TIMER_COMMAND_TIMEOUT 1500   // 2 seconden

/**
 * @brief handles de led aansturingen d.m.v. het commando
 *
 */
void handle_led();

/**
 * @brief Zal het commando resetten wanneer deze voor x milliseconden actief was.
 *
 */
void handle_commandTimer();

/**
 * @brief De data opvragen + opslaan en het gemiddelden berekenen + opslaan
 *
 * @param id dat het id voorstelt van de sensor. (CENTER, LEFT, RIGHT)
 */
void handle_data(uint8_t id);

/**
 * @brief Kalibratie uitvoeren van de sensoren
 *
 */
void perform_calibration();

/**
 * @brief initialiseren van de sensor
 *
 */
void perform_initSensor();

/**
 * @brief De state van gestureControlState bekijken in functie van het objectpresent boolean
 *
 */
void handle_stateGc();

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{
    /* MCU Configuration--------------------------------------------------------*/

    /* Reset of all peripherals, Initializes all pheripherals. */
    BSP_initBSP();

    // main while loop
    while (1)
    {
        switch (mainState)
        {
        case STATE_INIT:

            perform_initSensor();

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
            break;
        case STATE_GESTURE_CONTROL:
            // Doe alles van metingen, detectie, commands

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

                handle_stateGc();
                break;
            case STATE_GC_START:
                sensorFunctions_startSensor(&sensoren[LEFT]);
                sensorFunctions_startSensor(&sensoren[RIGHT]);

                gestureControlState = STATE_GC_SAMPLE;
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
                break;
            case STATE_GC_STOP:
                sensorFunctions_stopSensor(&sensoren[LEFT]);
                sensorFunctions_stopSensor(&sensoren[RIGHT]);

                gestureControlState = STATE_GC_SAMPLE;
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
            if (((timer_getTicks() - timerDataCollection) > TIMER_DATA_COLLECTION_TIMEOUT))
            {
                // printf("L%d, C%d, R%d\r\n", leftDistance, centerDistance, rightDistance);
                timerDataCollection = timer_getTicks();
                printf("%d,%d\t%d,%d\t%d,%d\r\n", (int)sensoren[LEFT].resultaat.distance, (int)sensoren[LEFT].resultaat.status, (int)sensoren[CENTER].resultaat.distance, (int)sensoren[CENTER].resultaat.status, (int)sensoren[RIGHT].resultaat.distance, (int)sensoren[RIGHT].resultaat.status);
                // printf("L%d, C%d, R%d\r\n", (int)sensoren[LEFT].resultaat.meanDistance, (int)sensoren[CENTER].resultaat.meanDistance, (int)sensoren[RIGHT].resultaat.meanDistance);
                // printf("D%d, S%d, \r\n", (int)sensoren[CENTER].resultaat.meanDistance, (int)sensoren[CENTER].resultaat.status);
                //  printf("%2d\r\n", commando);
            }
#endif

            I2C2_readIt(&buf);
            // I2C aanzetten om iets te ontvangen in interrupt modus.

            break;
        case STATE_STOP:
            sensorFunctions_stopSensor(&sensoren[CENTER]);
            while (1)
                ;
            return 1;
            break;

        default:
            break;
        }
        timer_delay(1);
    }
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    //Wanneer er een interrupt gegenereerd is door een GPIO, kijken we welke GPIO dit was en plaatsen we de respectievelijke flag op true.
    for (uint8_t i = 0; i < AMOUNT_SENSOR_USED; i++)
    {
        if (sensoren[i].sensorPorts.gpioi == gpio_callBack_gpio(GPIO_Pin))
        {
            sensoren[i].isReady = true;
        }
    }
}

int _write(int file, char *data, int len)
{
    return Usart1_send(file, data, len);
}

void HAL_I2C_SlaveRxCpltCallback(I2C_HandleTypeDef *hi2c)
{
    //Bij een RX (receive) callback gaan we het commando terug sturen.
    I2C2_writeIt((uint8_t *)&commando);
}

void handle_stateGc()
{
    /* Wanneer er een object aanwezig is en in de vorige loop was er nog geen object dan gaan we naar STATE_GC_START.
     * Of wanneer er geen object meer aanwezig is en in vorige loop was er nog een object aanwezig, gaan we naar STATE_GC_STOP.
     * Of wanneer er een object aanwezig is en in vorige loop was dit ook, dan gaan we naar STATE_GC_DETECT.
     * Wanneer alles niet waar is, gaan we naar STATE_GC_SAMPLE.
     */
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

    //De huidige warade in de vorige waarden steken.
    prevObjectPresent = objectPresent;
}

void perform_initSensor()
{
    //De sensoren koppelen aan hun pinnen en id.
    // center -> 0
    sensoren[CENTER].sensorPorts.gpioi = GPIOI2;
    sensoren[CENTER].sensorPorts.xshut = XSHUT2;
    sensoren[CENTER].id = CENTER;

    // left -> 1
    sensoren[LEFT].sensorPorts.gpioi = GPIOI1;
    sensoren[LEFT].sensorPorts.xshut = XSHUT1;
    sensoren[LEFT].id = LEFT;

    // right -> 2
    sensoren[RIGHT].sensorPorts.gpioi = GPIOI3;
    sensoren[RIGHT].sensorPorts.xshut = XSHUT3;
    sensoren[RIGHT].id = RIGHT;

    // Al de XSHUTS op 0 plaatsen. Dit zet alle sensoren op Hardware Standby.
    gpio_set_gpio(XSHUT0, resetPin);
    gpio_set_gpio(XSHUT1, resetPin);
    gpio_set_gpio(XSHUT2, resetPin);
    gpio_set_gpio(XSHUT3, resetPin);
    gpio_set_gpio(XSHUT4, resetPin);

    timer_delay(20);

    // De sensoren initialiseren
    sensorFunctions_initSensor(&sensoren[CENTER]);
    timer_delay(2);
    sensorFunctions_initSensor(&sensoren[LEFT]);
    timer_delay(2);
    sensorFunctions_initSensor(&sensoren[RIGHT]);
    timer_delay(2);
}

void perform_calibration()
{
    // Als de drukknop SW_1 actief is, wordt er gekalibreerd
    if (gpio_get_gpio(SW1))
    // if(true)
    {
        // de sensoren kalibreren en dit plotten naar seriële monitor
        calibrationData_getCalibrate(&sensoren[CENTER]);
        calibrationData_getCalibrate(&sensoren[LEFT]);
        calibrationData_getCalibrate(&sensoren[RIGHT]);

        // de sensoren opstarten
        sensorFunctions_startSensor(&sensoren[CENTER]);
        sensorFunctions_startSensor(&sensoren[LEFT]);
        sensorFunctions_startSensor(&sensoren[RIGHT]);

        // Oneindige loop waarbij we kunnen kijken of dat de nieuwe kalibratie parameters een succes zijn
        while (1)
        {
            sensorFunctions_getData(&sensoren[CENTER]);
            timer_delay(10);
            sensorFunctions_getData(&sensoren[LEFT]);
            timer_delay(10);
            sensorFunctions_getData(&sensoren[RIGHT]);
            timer_delay(10);
            timer_delay(200);
            printf("%d,%d\t%d,%d\t%d,%d\r\n", (int)sensoren[CENTER].resultaat.distance, (int)sensoren[CENTER].resultaat.status, (int)sensoren[LEFT].resultaat.distance, (int)sensoren[LEFT].resultaat.status, (int)sensoren[RIGHT].resultaat.distance, (int)sensoren[RIGHT].resultaat.status);
        }
    }
    else
    {
        // De hardcoded parameters importeren in de sensor
        calibrationData_setCalibrate(&sensoren[CENTER]);
        calibrationData_setCalibrate(&sensoren[LEFT]);
        calibrationData_setCalibrate(&sensoren[RIGHT]);
        
        /* DEBUG CODE WANNEER WE DE SENSOR KALIBREREN */
        /* op deze manier kunnen we snel kijken of dat de kalibratie een succes was  */

        // sensorFunctions_startSensor(&sensoren[CENTER]);
        // sensorFunctions_startSensor(&sensoren[LEFT]);
        // sensorFunctions_startSensor(&sensoren[RIGHT]);
        // uint8_t x = 0;
        // while (x < 20)
        // {
        //     sensorFunctions_getData(&sensoren[CENTER]);
        //     timer_delay(10);
        //     sensorFunctions_getData(&sensoren[LEFT]);
        //     timer_delay(10);
        //     sensorFunctions_getData(&sensoren[RIGHT]);
        //     timer_delay(10);
        //     timer_delay(200);
        //     printf("%d,%d\t%d,%d\t%d,%d\r\n", (int)sensoren[CENTER].resultaat.distance, (int)sensoren[CENTER].resultaat.status, (int)sensoren[LEFT].resultaat.distance, (int)sensoren[LEFT].resultaat.status, (int)sensoren[RIGHT].resultaat.distance, (int)sensoren[RIGHT].resultaat.status);
        //     x++;
        // }

        // sensorFunctions_stopSensor(&sensoren[CENTER]);
        // sensorFunctions_stopSensor(&sensoren[LEFT]);
        // sensorFunctions_stopSensor(&sensoren[RIGHT]);

        /* DEBUG CODE WANNEER WE DE SENSOR KALIBREREN */
    }
}

void handle_data(uint8_t id)
{
    //De data opvragen en opslaan in het gegeven sensor object.
    sensoren[id].isReady = sensorFunctions_getData(&sensoren[id]);

    //Bereken het gemiddelde van het gegeven sensor object
    calculations_setMeanVal(&sensoren[id]);

    //sla het gemiddelde op van het gegeven sensor object
    sensoren[id].resultaat.meanDistance = calculations_getMean(sensoren[id].id);
}

void handle_commandTimer()
{
    // timerCommandSet setten wanneer er een ander commando is gegeven dan NONE en OBJ en als timerCommandSet niet geset is 
    // Commando resetten wanneer timer_getTicks() - timerCommand boven TIMER_COMMAND_TIMEOUT valt.

    if (!timerCommandSet && commando != NONE && commando != OBJ)
    {
        timerCommandSet = true;
        timerCommand = timer_getTicks();
    }
    if ((timer_getTicks() - timerCommand) >= TIMER_COMMAND_TIMEOUT)
    {
        timerCommandSet = false;
        if (objectPresent)
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
        gpio_set_gpio(LED0, resetPin);
        gpio_set_gpio(LED1, resetPin);
        gpio_set_gpio(LED2, resetPin);
        break;
    case RL:
        gpio_set_gpio(LED0, setPin);
        gpio_set_gpio(LED1, resetPin);
        gpio_set_gpio(LED2, resetPin);
        break;
    case LR:
        gpio_set_gpio(LED0, resetPin);
        gpio_set_gpio(LED1, setPin);
        gpio_set_gpio(LED2, resetPin);
        break;
    case UD:
        gpio_set_gpio(LED0, setPin);
        gpio_set_gpio(LED1, setPin);
        gpio_set_gpio(LED2, resetPin);
        break;
    case DU:
        gpio_set_gpio(LED0, resetPin);
        gpio_set_gpio(LED1, resetPin);
        gpio_set_gpio(LED2, setPin);
        break;
    case DIM:
        gpio_set_gpio(LED0, setPin);
        gpio_set_gpio(LED1, resetPin);
        gpio_set_gpio(LED2, setPin);
        break;

    default:
        gpio_set_gpio(LED0, resetPin);
        gpio_set_gpio(LED1, resetPin);
        gpio_set_gpio(LED2, resetPin);
        break;
    }

    gpio_set_gpio(LED3, (state_t)objectPresent);
    gpio_toggle_gpio(LED4);
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