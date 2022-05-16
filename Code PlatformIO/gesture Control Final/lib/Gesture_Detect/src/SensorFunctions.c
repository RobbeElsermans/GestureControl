#include "SensorFunctions.h"

void Config_Sensor(VL53L3CX_Object_t *sensor, sensorDev index, uint8_t *address);
void Wait_For_GPIOI(VL53L3CX_Object_t *sensor, sensorDev index);

void Config_Sensor(VL53L3CX_Object_t *sensor, sensorDev index, uint8_t *address)
{
  sensor->IsInitialized = 0;
  sensor->IO.DeInit = CUSTOM_VL53L3CX_I2C_DeInit;
  sensor->IO.Init = CUSTOM_VL53L3CX_I2C_Init;
  sensor->IO.ReadReg = CUSTOM_VL53L3CX_I2C_ReadReg;
  sensor->IO.WriteReg = CUSTOM_VL53L3CX_I2C_WriteReg;
  sensor->IO.GetTick = CUSTOM_VL53L3CX_I2C_GetTick;
  sensor->IO.Address = 0x52;

  switch (index)
  {
  case 0:
    HAL_GPIO_WritePin(XSHUT_0_GPIO_Port, XSHUT_0_Pin, 1);
    break;
  case 1:
    HAL_GPIO_WritePin(XSHUT_1_GPIO_Port, XSHUT_1_Pin, 1);
    break;
  case 2:
    HAL_GPIO_WritePin(XSHUT_2_GPIO_Port, XSHUT_2_Pin, 1);
    break;
  case 3:
    HAL_GPIO_WritePin(XSHUT_3_GPIO_Port, XSHUT_3_Pin, 1);
    break;
  case 4:
    HAL_GPIO_WritePin(XSHUT_4_GPIO_Port, XSHUT_4_Pin, 1);
    break;
  default:
    break;
  }

  HAL_Delay(2);
  VL53L3CX_Init(sensor);
  // VL53LX_SetMeasurementTimingBudgetMicroSeconds(sensor, 8000);
  VL53L3CX_SetAddress(sensor, (uint32_t)address);

  // Config profile
  VL53L3CX_ProfileConfig_t Profile;

  Profile.RangingProfile = VL53LX_DISTANCEMODE_MEDIUM;
  Profile.TimingBudget = 8 * 3; /* 8 ms < TimingBudget < 500 ms */
  Profile.Frequency = 0;        /* not necessary in simple ranging */
  Profile.EnableAmbient = 1;    /* Enable: 1, Disable: 0 */
  Profile.EnableSignal = 1;     /* Enable: 1, Disable: 0 */

  VL53L3CX_ConfigProfile(sensor, &Profile);
}

uint8_t Sensor_Ready(VL53L3CX_Object_t *sensor, sensorDev index, uint8_t* isReady)
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

void Init_Sensor(VL53L3CX_Object_t *sensor, sensorDev index)
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
  // printf("%d\r\n", ret);
}

void Start_Sensor(VL53L3CX_Object_t *sensor, sensorDev index)
{
  VL53L3CX_Start(sensor, VL53L3CX_MODE_ASYNC_CONTINUOUS); // Sensor staren met meten
  Wait_For_GPIOI(sensor, index);
}

void Stop_Sensor(VL53L3CX_Object_t *sensor)
{
  VL53L3CX_Stop(sensor); // Sensor staren met meten
}

bool getData(VL53L3CX_Object_t *sensor, Sensor_Definition_t *device, Resultaat_t *resultaat, uint8_t* isReadySens)
{
  VL53L3CX_Result_t tempResult;
  bool trigger = false;
  if (Sensor_Ready(sensor, device->gpioPin, isReadySens))
  {
    trigger = true;
    VL53L3CX_GetDistance(sensor, &tempResult);
    // HAL_Delay(2);
      resultaat[device->id].distance = (long)tempResult.ZoneResult[0].Distance[0];
      resultaat[device->id].status = tempResult.ZoneResult[0].Status[0];
      resultaat[device->id].timestamp = HAL_GetTick();
    // HAL_Delay(2);
  }

  if (trigger)
    return false;
  return true;
}
