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
#include "custom_tof_conf.h"
#include "vl53l3cx.h"
#include <sys/unistd.h> // STDOUT_FILENO, STDERR_FI
#include <errno.h>
#include "stdbool.h"
#include "vl53lx_api.h"
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
long distance[5] = {0,0,0,0,0};
long status[5] = {0,0,0,0,0};
volatile bool isReady[5] = {false,false,false,false,false};
volatile bool hasRead[5] = {false,false,false,false,false};
VL53L3CX_Result_t results[5];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void Config_Sensor(VL53L3CX_Object_t * sensor, uint8_t index, uint8_t *address);
uint8_t Sensor_Ready(VL53L3CX_Object_t * sensor, uint8_t index, uint8_t* isReady);
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

   uint8_t device;
   uint32_t id;
   int ret;

   Config_Sensor(&sensor[0], 0, (uint8_t *) 2);
   ret = VL53L3CX_ReadID(&sensor[0], &id);
   printf("%d\r\n", ret);
   VL53L3CX_Start(&sensor[0], VL53L3CX_MODE_ASYNC_CONTINUOUS);	//Sensor staren met meten
   while(HAL_GPIO_ReadPin(GPIOI_0_GPIO_Port, GPIOI_0_Pin)); 			//Zolang wachten totdat de GPIOI is af gegaan
   VL53L3CX_GetDistance(&sensor[0], &results[0]);					//1ste meeting weg gooien

   Config_Sensor(&sensor[1], 1, (uint8_t *) 4);
   ret = VL53L3CX_ReadID(&sensor[1], &id);
   printf("%d\r\n", ret);
   VL53L3CX_Start(&sensor[1], VL53L3CX_MODE_ASYNC_CONTINUOUS);	//Sensor staren met meten
   while(HAL_GPIO_ReadPin(GPIOI_1_GPIO_Port, GPIOI_1_Pin)); 			//Zolang wachten totdat de GPIOI is af gegaan								//De tijd geven voor te meten
   VL53L3CX_GetDistance(&sensor[1], &results[1]);					//1ste meeting weg gooien

   Config_Sensor(&sensor[2], 2, (uint8_t *) 6);
   ret = VL53L3CX_ReadID(&sensor[2], &id);
   printf("%d\r\n", ret);
   VL53L3CX_Start(&sensor[2], VL53L3CX_MODE_ASYNC_CONTINUOUS);	//Sensor staren met meten
   while(HAL_GPIO_ReadPin(GPIOI_2_GPIO_Port, GPIOI_2_Pin)); 			//Zolang wachten totdat de GPIOI is af gegaan												//De tijd geven voor te meten
   VL53L3CX_GetDistance(&sensor[2], &results[2]);					//1ste meeting weg gooien

   Config_Sensor(&sensor[3], 3, (uint8_t *) 8);
   ret = VL53L3CX_ReadID(&sensor[3], &id);
   printf("%d\r\n", ret);
   VL53L3CX_Start(&sensor[3], VL53L3CX_MODE_ASYNC_CONTINUOUS);	//Sensor staren met meten
   while(HAL_GPIO_ReadPin(GPIOI_3_GPIO_Port, GPIOI_3_Pin)); 			//Zolang wachten totdat de GPIOI is af gegaan													//De tijd geven voor te meten
   VL53L3CX_GetDistance(&sensor[3], &results[3]);					//1ste meeting weg gooien

   Config_Sensor(&sensor[4], 4, (uint8_t *) 10);
   ret = VL53L3CX_ReadID(&sensor[4], &id);
   printf("%d\r\n", ret);
   VL53L3CX_Start(&sensor[4], VL53L3CX_MODE_ASYNC_CONTINUOUS);	//Sensor staren met meten
   while(HAL_GPIO_ReadPin(GPIOI_4_GPIO_Port, GPIOI_4_Pin)); 			//Zolang wachten totdat de GPIOI is af gegaan													//De tijd geven voor te meten
   VL53L3CX_GetDistance(&sensor[4], &results[4]);					//1ste meeting weg gooien

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  if (Sensor_Ready(&sensor[0], 0, (uint8_t *)isReady))
	     {
	       isReady[0] = false;
	       VL53L3CX_GetDistance(&sensor[0], &results[0]);
	       HAL_Delay(2);
	       distance[0] = (long)results[0].ZoneResult[0].Distance[0];
	       status[0] = results[0].ZoneResult[0].Status[0];
	       HAL_Delay(2);
	     }

	     if (Sensor_Ready(&sensor[1], 1, (uint8_t *)isReady))
	     {
	       isReady[1] = false;
	       VL53L3CX_GetDistance(&sensor[1], &results[1]);
	       HAL_Delay(2);
	       distance[1] = (long)results[1].ZoneResult[0].Distance[0];
	       status[1] = results[1].ZoneResult[0].Status[0];
	       HAL_Delay(2);
	     }

	     if (Sensor_Ready(&sensor[2], 2, (uint8_t *)isReady))
	     {
	       isReady[2] = false;
	       VL53L3CX_GetDistance(&sensor[2], &results[2]);
	       HAL_Delay(2);
	       distance[2] = (long)results[2].ZoneResult[0].Distance[0];
	       status[2] = results[2].ZoneResult[0].Status[0];
	       HAL_Delay(2);
	     }

	     if (Sensor_Ready(&sensor[3], 3, (uint8_t *)isReady))
	     {
	       isReady[3] = false;
	       VL53L3CX_GetDistance(&sensor[3], &results[3]);
	       HAL_Delay(2);
	       distance[3] = (long)results[3].ZoneResult[0].Distance[0];
	       status[3] = results[3].ZoneResult[0].Status[0];
	       HAL_Delay(2);
	     }

	     if (Sensor_Ready(&sensor[4], 4, (uint8_t *)isReady))
	     {
	       isReady[4] = false;
	       VL53L3CX_GetDistance(&sensor[4], &results[4]);
	       HAL_Delay(2);
	       distance[4] = (long)results[4].ZoneResult[0].Distance[0];
	       status[4] = results[4].ZoneResult[0].Status[0];
	       HAL_Delay(2);
	     }

	     if (distance[1] >= 50 && distance[1] <= 300)
	     {
	       HAL_GPIO_WritePin(LED_0_GPIO_Port, LED_0_Pin, 1);
	       HAL_Delay(50);
	     }

	     if (distance[1] > 300 && distance[1] <= 600)
	     {
	       HAL_GPIO_WritePin(LED_1_GPIO_Port, LED_1_Pin, 1);
	       HAL_Delay(50);
	     }

	     if (distance[1] > 600 && distance[1] <= 800)
	     {
	       HAL_GPIO_WritePin(LED_2_GPIO_Port, LED_2_Pin, 1);
	       HAL_Delay(50);
	     }

	     if (distance[1] > 800 && distance[1] <= 1200)
	     {
	       HAL_GPIO_WritePin(LED_3_GPIO_Port, LED_3_Pin, 1);
	       HAL_Delay(50);
	     }
	     if (distance[1] > 1200)
	     {
	       HAL_GPIO_WritePin(LED_4_GPIO_Port, LED_4_Pin, 1);
	       HAL_Delay(50);
	     }

	     HAL_Delay(200);
	     HAL_GPIO_WritePin(LED_0_GPIO_Port, LED_0_Pin, 0);
	     HAL_GPIO_WritePin(LED_1_GPIO_Port, LED_1_Pin, 0);
	     HAL_GPIO_WritePin(LED_2_GPIO_Port, LED_2_Pin, 0);
	     HAL_GPIO_WritePin(LED_3_GPIO_Port, LED_3_Pin, 0);
	     HAL_GPIO_WritePin(LED_4_GPIO_Port, LED_4_Pin, 0);
	     printf("distance 0: %4d %3d\t distance 1: %4d %3d\t distance 2: %4d %3d\t distance 3: %4d %3d\t distance 4: %4d %3d\r\n", (int)distance[0],status[0], (int)distance[1],status[1], (int)distance[2],status[2], (int)distance[3],status[3], (int)distance[4],status[4]);
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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSE;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1|RCC_PERIPHCLK_I2C1
                              |RCC_PERIPHCLK_I2C3;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_HSI;
  PeriphClkInit.I2c3ClockSelection = RCC_I2C3CLKSOURCE_HSI;
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
void Config_Sensor(VL53L3CX_Object_t * sensor, uint8_t index, uint8_t *address){

	sensor->IO.DeInit = CUSTOM_VL53L3CX_I2C_DeInit;
	sensor->IO.Init = CUSTOM_VL53L3CX_I2C_Init;
	sensor->IO.ReadReg = CUSTOM_VL53L3CX_I2C_ReadReg;
	sensor->IO.WriteReg = CUSTOM_VL53L3CX_I2C_WriteReg;
	sensor->IO.GetTick = CUSTOM_VL53L3CX_I2C_GetTick;
	sensor->IO.Address = 0x52;

	switch(index){
	case 0: //Sensor CENTER
			HAL_GPIO_WritePin(XSHUT_0_GPIO_Port, XSHUT_0_Pin, 1);
			break;
	case 1: //Sensor CENTER
			HAL_GPIO_WritePin(XSHUT_1_GPIO_Port, XSHUT_1_Pin, 1);
			break;
	case 2: //Sensor CENTER
			HAL_GPIO_WritePin(XSHUT_2_GPIO_Port, XSHUT_2_Pin, 1);
			break;
	case 3: //Sensor CENTER
			HAL_GPIO_WritePin(XSHUT_3_GPIO_Port, XSHUT_3_Pin, 1);
			break;
	case 4: //Sensor CENTER
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

uint8_t Sensor_Ready(VL53L3CX_Object_t * sensor, uint8_t index, uint8_t* isReady){
	switch(index){
	case 0:
		if(isReady[index] || (!isReady[index]  && !HAL_GPIO_ReadPin(GPIOI_0_GPIO_Port, GPIOI_0_Pin)))
			return 1;
		break;
	case 1:
		if(isReady[index] || (!isReady[index]  && !HAL_GPIO_ReadPin(GPIOI_1_GPIO_Port, GPIOI_1_Pin)))
			return 1;
		break;
	case 2:
		if(isReady[index] || (!isReady[index]  && !HAL_GPIO_ReadPin(GPIOI_2_GPIO_Port, GPIOI_2_Pin)))
			return 1;
		break;
	case 3:
		if(isReady[index] || (!isReady[index]  && !HAL_GPIO_ReadPin(GPIOI_3_GPIO_Port, GPIOI_3_Pin)))
			return 1;
		break;
	case 4:
		if(isReady[index] || (!isReady[index] && !HAL_GPIO_ReadPin(GPIOI_4_GPIO_Port, GPIOI_4_Pin)))
			return 1;
		break;
	default:
		return 0;
		break;
	}
	return 0;
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

#ifdef  USE_FULL_ASSERT
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

