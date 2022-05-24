#include "SensorFunctions.h"

void Config_Sensor(sensorData_t* sensor, uint8_t *address);

void Wait_For_GPIOI(sensorData_t* sensor);

void Config_Sensor(sensorData_t* sensor, uint8_t *address){
// Omdat we in RAM de objecten aanmaken (en niet initialiseren) gaat er random waardes insteken.
  // Isinitialized moet 0 zijn om verder te kunnen.
  sensor->sensor.IsInitialized = 0;
  sensor->sensor.IO.DeInit = CUSTOM_VL53L3CX_I2C_DeInit;
  sensor->sensor.IO.Init = CUSTOM_VL53L3CX_I2C_Init;
  sensor->sensor.IO.ReadReg = CUSTOM_VL53L3CX_I2C_ReadReg;
  sensor->sensor.IO.WriteReg = CUSTOM_VL53L3CX_I2C_WriteReg;
  sensor->sensor.IO.GetTick = CUSTOM_VL53L3CX_I2C_GetTick;
  sensor->sensor.IO.Address = 0x52;

  gpio_set_gpio(sensor->sensorPorts.xshut, setPin);

  timer_delay(2);
  VL53L3CX_Init(&sensor->sensor);
  // VL53LX_SetMeasurementTimingBudgetMicroSeconds(sensor, 8000);
  VL53L3CX_SetAddress(&sensor->sensor, (uint32_t)address);

  // Config profile
  VL53L3CX_ProfileConfig_t Profile;

  Profile.RangingProfile = VL53LX_DISTANCEMODE_MEDIUM;
  Profile.TimingBudget = 8 * 3; /* 8 ms < TimingBudget < 500 ms */
  Profile.Frequency = 0;        /* not necessary in simple ranging */
  Profile.EnableAmbient = 1;    /* Enable: 1, Disable: 0 */
  Profile.EnableSignal = 1;     /* Enable: 1, Disable: 0 */

  VL53L3CX_ConfigProfile(&sensor->sensor, &Profile);
}

uint8_t sensorFunctions_sensorReady(sensorData_t* sensor)
{
  if (sensor->isReady || !gpio_get_gpio(sensor->sensorPorts.gpioi))
    return 1;
  return 0;
}

void Wait_For_GPIOI(sensorData_t* sensor)
{
  VL53L3CX_Result_t results;

  while (gpio_get_gpio(sensor->sensorPorts.gpioi)); // Zolang wachten totdat de GPIOI is af gegaan

  VL53L3CX_GetDistance(&sensor->sensor, &results); // 1ste meeting weg gooien
}

void sensorFunctions_initSensor(sensorData_t* sensor){

  switch (sensor->id)
  {
  case 0:
    Config_Sensor(sensor, (uint8_t *)2);
    break;
  case 1:
    Config_Sensor(sensor, (uint8_t *)4);
    break;
  case 2:
    Config_Sensor(sensor, (uint8_t *)6);
    break;
  case 3:
    Config_Sensor(sensor, (uint8_t *)8);
    break;
  case 4:
    Config_Sensor(sensor, (uint8_t *)10);
    break;

  default:
    break;
  }
}


void sensorFunctions_startSensor(sensorData_t* sensor)
{
  VL53L3CX_Start(&sensor->sensor, VL53L3CX_MODE_ASYNC_CONTINUOUS); // Sensor staren met meten
  Wait_For_GPIOI(sensor);
}

void sensorFunctions_stopSensor(sensorData_t* sensor)
{
  VL53L3CX_Stop(&sensor->sensor); // Sensor staren met meten
}

bool sensorFunctions_getData(sensorData_t* sensor)
{
  VL53L3CX_Result_t tempResult;
  bool trigger = false;
  if (sensorFunctions_sensorReady(sensor))
  {
    trigger = true;
    VL53L3CX_GetDistance(&sensor->sensor, &tempResult);
      sensor->resultaat.distance = (long)tempResult.ZoneResult[0].Distance[0];
      sensor->resultaat.status = tempResult.ZoneResult[0].Status[0];
      sensor->resultaat.timestamp = timer_getTicks();
  }

  if (trigger)
    return false;
  return true;
}
