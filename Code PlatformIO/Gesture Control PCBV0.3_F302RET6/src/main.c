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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
VL53L3CX_Object_t sensor[5];
long distance[5] = {0, 0, 0, 0, 0};
long status[5] = {0, 0, 0, 0, 0};
volatile bool isReady[5] = {false, false, false, false, false};
volatile bool hasRead[5] = {false, false, false, false, false};
VL53L3CX_Result_t results[5];

// typedef enum SensorDef
// {
//   CENTER = 0,
//   LEFT = 4,
//   RIGHT = 1,
//   TOP = 2,
//   BOTTOM = 3,
// } sensorDev;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void Config_Sensor(VL53L3CX_Object_t *sensor, sensorDev index, uint8_t *address);
uint8_t Sensor_Ready(VL53L3CX_Object_t *sensor, sensorDev index, uint8_t *isReady);
void Wait_For_GPIOI(VL53L3CX_Object_t *sensor, sensorDev index);
void Start_Sensor(VL53L3CX_Object_t *sensor, sensorDev index);
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C3_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
  HAL_GPIO_WritePin(XSHUT_0_GPIO_Port, XSHUT_0_Pin, 0);
  HAL_GPIO_WritePin(XSHUT_1_GPIO_Port, XSHUT_1_Pin, 0);
  HAL_GPIO_WritePin(XSHUT_2_GPIO_Port, XSHUT_2_Pin, 0);
  HAL_GPIO_WritePin(XSHUT_3_GPIO_Port, XSHUT_3_Pin, 0);
  HAL_GPIO_WritePin(XSHUT_4_GPIO_Port, XSHUT_4_Pin, 0);

  HAL_Delay(20);

  CUSTOM_VL53L3CX_I2C_Init();

  Start_Sensor(&sensor[CENTER], CENTER);
  Start_Sensor(&sensor[LEFT], LEFT);
  Start_Sensor(&sensor[RIGHT], RIGHT);
  Start_Sensor(&sensor[TOP], TOP);
  Start_Sensor(&sensor[BOTTOM], BOTTOM);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    if (Sensor_Ready(&sensor[CENTER], CENTER, (uint8_t *)isReady))
    {
      isReady[CENTER] = false;
      VL53L3CX_GetDistance(&sensor[CENTER], &results[CENTER]);
      HAL_Delay(2);
      distance[CENTER] = (long)results[CENTER].ZoneResult[0].Distance[0];
      status[CENTER] = results[CENTER].ZoneResult[0].Status[0];
      HAL_Delay(2);
    }

    if (Sensor_Ready(&sensor[LEFT], LEFT, (uint8_t *)isReady))
    {
      isReady[LEFT] = false;
      VL53L3CX_GetDistance(&sensor[LEFT], &results[LEFT]);
      HAL_Delay(2);
      distance[LEFT] = (long)results[LEFT].ZoneResult[0].Distance[0];
      status[LEFT] = results[LEFT].ZoneResult[0].Status[0];
      HAL_Delay(2);
    }

    if (Sensor_Ready(&sensor[RIGHT], RIGHT, (uint8_t *)isReady))
    {
      isReady[RIGHT] = false;
      VL53L3CX_GetDistance(&sensor[RIGHT], &results[RIGHT]);
      HAL_Delay(2);
      distance[RIGHT] = (long)results[RIGHT].ZoneResult[0].Distance[0];
      status[RIGHT] = results[RIGHT].ZoneResult[0].Status[0];
      HAL_Delay(2);
    }

    if (Sensor_Ready(&sensor[TOP], TOP, (uint8_t *)isReady))
    {
      isReady[TOP] = false;
      VL53L3CX_GetDistance(&sensor[TOP], &results[TOP]);
      HAL_Delay(2);
      distance[TOP] = (long)results[TOP].ZoneResult[0].Distance[0];
      status[TOP] = results[TOP].ZoneResult[0].Status[0];
      HAL_Delay(2);
    }

    if (Sensor_Ready(&sensor[BOTTOM], BOTTOM, (uint8_t *)isReady))
    {
      isReady[BOTTOM] = false;
      VL53L3CX_GetDistance(&sensor[BOTTOM], &results[BOTTOM]);
      HAL_Delay(2);
      distance[BOTTOM] = (long)results[BOTTOM].ZoneResult[0].Distance[0];
      status[BOTTOM] = results[BOTTOM].ZoneResult[0].Status[0];
      HAL_Delay(2);
    }

    if (distance[BOTTOM] >= 50 && distance[BOTTOM] <= 300)
    {
      HAL_GPIO_WritePin(LED_0_GPIO_Port, LED_0_Pin, 1);
      HAL_Delay(50);
    }

    if (distance[TOP] >= 50 && distance[TOP] <= 300)
    {
      HAL_GPIO_WritePin(LED_1_GPIO_Port, LED_1_Pin, 1);
      HAL_Delay(50);
    }

    if (distance[LEFT] >= 50 && distance[LEFT] <= 300)
    {
      HAL_GPIO_WritePin(LED_3_GPIO_Port, LED_3_Pin, 1);
      HAL_Delay(50);
    }

    if (distance[RIGHT] >= 50 && distance[RIGHT] <= 300)
    {
      HAL_GPIO_WritePin(LED_4_GPIO_Port, LED_4_Pin, 1);
      HAL_Delay(50);
    }

    if (distance[CENTER] >= 50 && distance[CENTER] <= 300)
    {
      HAL_GPIO_WritePin(LED_2_GPIO_Port, LED_2_Pin, 1);
      HAL_Delay(50);
    }

    HAL_Delay(2);
    HAL_GPIO_WritePin(LED_0_GPIO_Port, LED_0_Pin, 0);
    HAL_GPIO_WritePin(LED_1_GPIO_Port, LED_1_Pin, 0);
    HAL_GPIO_WritePin(LED_2_GPIO_Port, LED_2_Pin, 0);
    HAL_GPIO_WritePin(LED_3_GPIO_Port, LED_3_Pin, 0);
    HAL_GPIO_WritePin(LED_4_GPIO_Port, LED_4_Pin, 0);
    printf("distance CENTER: %4d %3d\t distance LEFT: %4d %3d\t distance RIGHT: %4d %3d\t distance TOP: %4d %3d\t distance BOTTOM: %4d %3d\r\n",
     (int)distance[CENTER], status[CENTER], (int)distance[LEFT], status[LEFT], (int)distance[RIGHT], status[RIGHT], (int)distance[TOP], status[TOP], (int)distance[BOTTOM], status[BOTTOM]);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
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
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
   */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSE;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1 | RCC_PERIPHCLK_I2C1 | RCC_PERIPHCLK_I2C3;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_SYSCLK;
  PeriphClkInit.I2c3ClockSelection = RCC_I2C3CLKSOURCE_SYSCLK;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  switch (GPIO_Pin)
  {
  case GPIOI_0_Pin:
    if (!hasRead[0])
    {
      hasRead[0] = true;
    }
    else
      isReady[0] = true;
    break;

  case GPIOI_1_Pin:
    if (!hasRead[1])
    {
      hasRead[1] = true;
    }
    else
      isReady[1] = true;
    break;

  case GPIOI_2_Pin:
    if (!hasRead[2])
    {
      hasRead[2] = true;
    }
    else
      isReady[2] = true;
    break;

  case GPIOI_3_Pin:
    if (!hasRead[3])
    {
      hasRead[3] = true;
    }
    else
      isReady[3] = true;
    break;

  case GPIOI_4_Pin:
    if (!hasRead[4])
    {
      hasRead[4] = true;
    }
    else
      isReady[4] = true;
    break;
  default:
    break;
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
void Config_Sensor(VL53L3CX_Object_t *sensor, sensorDev index, uint8_t *address)
{

  sensor->IO.DeInit = CUSTOM_VL53L3CX_I2C_DeInit;
  sensor->IO.Init = CUSTOM_VL53L3CX_I2C_Init;
  sensor->IO.ReadReg = CUSTOM_VL53L3CX_I2C_ReadReg;
  sensor->IO.WriteReg = CUSTOM_VL53L3CX_I2C_WriteReg;
  sensor->IO.GetTick = CUSTOM_VL53L3CX_I2C_GetTick;
  sensor->IO.Address = 0x52;

  switch (index)
  {
  case 0: // Sensor CENTER
    HAL_GPIO_WritePin(XSHUT_0_GPIO_Port, XSHUT_0_Pin, 1);
    break;
  case 1: // Sensor LEFT
    HAL_GPIO_WritePin(XSHUT_1_GPIO_Port, XSHUT_1_Pin, 1);
    break;
  case 2: // Sensor RIGHT
    HAL_GPIO_WritePin(XSHUT_2_GPIO_Port, XSHUT_2_Pin, 1);
    break;
  case 3: // Sensor TOP
    HAL_GPIO_WritePin(XSHUT_3_GPIO_Port, XSHUT_3_Pin, 1);
    break;
  case 4: // Sensor BOTTOM
    HAL_GPIO_WritePin(XSHUT_4_GPIO_Port, XSHUT_4_Pin, 1);
    break;
  default:
    break;
  }
  HAL_Delay(2);
  VL53L3CX_Init(sensor);
  VL53L3CX_SetAddress(sensor, address);

  // Config profile
  VL53L3CX_ProfileConfig_t Profile;

  Profile.RangingProfile = VL53LX_DISTANCEMODE_MEDIUM;
  Profile.TimingBudget = 100; /* 16 ms < TimingBudget < 500 ms */
  Profile.Frequency = 0;      /* not necessary in simple ranging */
  Profile.EnableAmbient = 1;  /* Enable: 1, Disable: 0 */
  Profile.EnableSignal = 1;   /* Enable: 1, Disable: 0 */

  VL53L3CX_ConfigProfile(sensor, &Profile);
}

uint8_t Sensor_Ready(VL53L3CX_Object_t *sensor, sensorDev index, uint8_t *isReady)
{
  switch (index)
  {
  case 0:
    if (isReady[index] || (!isReady[index] && !HAL_GPIO_ReadPin(GPIOI_0_GPIO_Port, GPIOI_0_Pin)))
      return 1;
    break;
  case 1:
    if (isReady[index] || (!isReady[index] && !HAL_GPIO_ReadPin(GPIOI_1_GPIO_Port, GPIOI_1_Pin)))
      return 1;
    break;
  case 2:
    if (isReady[index] || (!isReady[index] && !HAL_GPIO_ReadPin(GPIOI_2_GPIO_Port, GPIOI_2_Pin)))
      return 1;
    break;
  case 3:
    if (isReady[index] || (!isReady[index] && !HAL_GPIO_ReadPin(GPIOI_3_GPIO_Port, GPIOI_3_Pin)))
      return 1;
    break;
  case 4:
    if (isReady[index] || (!isReady[index] && !HAL_GPIO_ReadPin(GPIOI_4_GPIO_Port, GPIOI_4_Pin)))
      return 1;
    break;
  default:
    return 0;
    break;
  }
  return 0;
}

void Wait_For_GPIOI(VL53L3CX_Object_t *sensor, sensorDev index)
{
  VL53L3CX_Result_t results;

  switch (index)
  {
  case 0:
    while (HAL_GPIO_ReadPin(GPIOI_0_GPIO_Port, GPIOI_0_Pin))
      ; // Zolang wachten totdat de GPIOI is af gegaan
    /* code */
    break;
  case 1:
    while (HAL_GPIO_ReadPin(GPIOI_1_GPIO_Port, GPIOI_1_Pin))
      ; // Zolang wachten totdat de GPIOI is af gegaan
    /* code */
    break;
  case 2:
    while (HAL_GPIO_ReadPin(GPIOI_2_GPIO_Port, GPIOI_2_Pin))
      ; // Zolang wachten totdat de GPIOI is af gegaan
    /* code */
    break;
  case 3:
    while (HAL_GPIO_ReadPin(GPIOI_3_GPIO_Port, GPIOI_3_Pin))
      ; // Zolang wachten totdat de GPIOI is af gegaan
    /* code */
    break;
  case 4:
    while (HAL_GPIO_ReadPin(GPIOI_4_GPIO_Port, GPIOI_4_Pin))
      ; // Zolang wachten totdat de GPIOI is af gegaan
    /* code */
    break;

  default:
    break;
  }

  VL53L3CX_GetDistance(sensor, &results); // 1ste meeting weg gooien
}
void Start_Sensor(VL53L3CX_Object_t *sensor, sensorDev index)
{
  uint32_t id;
  int ret;

  switch (index)
  {
  case 0:
    Config_Sensor(sensor, index, (uint8_t *)2);
    break;
  case 1:
    Config_Sensor(sensor, index, (uint8_t *)4);
    break;
  case 2:
    Config_Sensor(sensor, index, (uint8_t *)6);
    break;
  case 3:
    Config_Sensor(sensor, index, (uint8_t *)8);
    break;
  case 4:
    Config_Sensor(sensor, index, (uint8_t *)10);
    break;

  default:
    break;
  }

  ret = VL53L3CX_ReadID(sensor, &id);
  printf("%d\r\n", ret);
  VL53L3CX_Start(sensor, VL53L3CX_MODE_ASYNC_CONTINUOUS); // Sensor staren met meten
  Wait_For_GPIOI(sensor, index);
}
/* USER CODE END 4 */

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