#include "tof_test.h"

// Private functions
void Config_Sensor(VL53L3CX_Object_t *sensor, uint8_t index, uint8_t *address);

static void tearDown_led(void);
void test_tof_pin_number(void);
void test_tof_set_XSHUT(uint8_t index, bool type);

// Private global variables
uint8_t const amountSensors = 5;

static void tearDown_led(void)
{
    HAL_GPIO_DeInit(XSHUT_0_GPIO_Port, XSHUT_0_Pin);
    HAL_GPIO_DeInit(XSHUT_1_GPIO_Port, XSHUT_1_Pin);
    HAL_GPIO_DeInit(XSHUT_2_GPIO_Port, XSHUT_2_Pin);
    HAL_GPIO_DeInit(XSHUT_3_GPIO_Port, XSHUT_3_Pin);
    HAL_GPIO_DeInit(XSHUT_4_GPIO_Port, XSHUT_4_Pin);

    HAL_GPIO_DeInit(GPIOI_0_GPIO_Port, GPIOI_0_Pin);
    HAL_GPIO_DeInit(GPIOI_1_GPIO_Port, GPIOI_1_Pin);
    HAL_GPIO_DeInit(GPIOI_2_GPIO_Port, GPIOI_2_Pin);
    HAL_GPIO_DeInit(GPIOI_3_GPIO_Port, GPIOI_3_Pin);
    HAL_GPIO_DeInit(GPIOI_4_GPIO_Port, GPIOI_4_Pin);
}

void test_tof_pin_number(void)
{
    TEST_ASSERT_EQUAL(GPIO_PIN_0, XSHUT_0_Pin);
    TEST_ASSERT_EQUAL(GPIOC, XSHUT_0_GPIO_Port);

    TEST_ASSERT_EQUAL(GPIO_PIN_1, XSHUT_1_Pin);
    TEST_ASSERT_EQUAL(GPIOC, XSHUT_1_GPIO_Port);

    TEST_ASSERT_EQUAL(GPIO_PIN_2, XSHUT_2_Pin);
    TEST_ASSERT_EQUAL(GPIOC, XSHUT_2_GPIO_Port);

    TEST_ASSERT_EQUAL(GPIO_PIN_3, XSHUT_3_Pin);
    TEST_ASSERT_EQUAL(GPIOC, XSHUT_3_GPIO_Port);

    TEST_ASSERT_EQUAL(GPIO_PIN_4, XSHUT_4_Pin);
    TEST_ASSERT_EQUAL(GPIOC, XSHUT_4_GPIO_Port);

    TEST_ASSERT_EQUAL(GPIO_PIN_12, GPIOI_0_Pin);
    TEST_ASSERT_EQUAL(GPIOB, GPIOI_0_GPIO_Port);

    TEST_ASSERT_EQUAL(GPIO_PIN_13, GPIOI_1_Pin);
    TEST_ASSERT_EQUAL(GPIOB, GPIOI_1_GPIO_Port);

    TEST_ASSERT_EQUAL(GPIO_PIN_14, GPIOI_2_Pin);
    TEST_ASSERT_EQUAL(GPIOB, GPIOI_2_GPIO_Port);

    TEST_ASSERT_EQUAL(GPIO_PIN_15, GPIOI_3_Pin);
    TEST_ASSERT_EQUAL(GPIOB, GPIOI_3_GPIO_Port);

    TEST_ASSERT_EQUAL(GPIO_PIN_6, GPIOI_4_Pin);
    TEST_ASSERT_EQUAL(GPIOC, GPIOI_4_GPIO_Port);
}

/**
 * @brief Test de connectiviteit met elke sensor
 *
 */
void run_tof_connectivity()
{

    VL53L3CX_Object_t sensor[amountSensors];
    VL53L3CX_Result_t results[amountSensors];

    for (uint8_t i = 0; i < amountSensors; i++)
    {
        Config_Sensor(&sensor[i], i, (uint8_t*)0x52);
        test_tof_set_XSHUT(i, 0);
    }
}
void run_tof_range()
{
}
void run_all_tof_connectivity()
{
}
void run_all_tof_range()
{
}

void Config_Sensor(VL53L3CX_Object_t *sensor, uint8_t index, uint8_t *address)
{

    sensor->IO.DeInit = CUSTOM_VL53L3CX_I2C_DeInit;
    sensor->IO.Init = CUSTOM_VL53L3CX_I2C_Init;
    sensor->IO.ReadReg = CUSTOM_VL53L3CX_I2C_ReadReg;
    sensor->IO.WriteReg = CUSTOM_VL53L3CX_I2C_WriteReg;
    sensor->IO.GetTick = CUSTOM_VL53L3CX_I2C_GetTick;
    sensor->IO.Address = 0x52;

    test_tof_set_XSHUT(index, 1);

    HAL_Delay(2);
    VL53L3CX_Init(sensor);
    VL53L3CX_SetAddress(sensor, *address);

    // Config profile
    VL53L3CX_ProfileConfig_t Profile;

    Profile.RangingProfile = VL53LX_DISTANCEMODE_MEDIUM;
    Profile.TimingBudget = 100; /* 16 ms < TimingBudget < 500 ms */
    Profile.Frequency = 0;      /* not necessary in simple ranging */
    Profile.EnableAmbient = 1;  /* Enable: 1, Disable: 0 */
    Profile.EnableSignal = 1;   /* Enable: 1, Disable: 0 */

    VL53L3CX_ConfigProfile(sensor, &Profile);
}

void test_tof_set_XSHUT(uint8_t index, bool type)
{
    switch (index)
    {
    case 0: // Sensor CENTER
        HAL_GPIO_WritePin(XSHUT_0_GPIO_Port, XSHUT_0_Pin, type);
        TEST_ASSERT_EQUAL(type, HAL_GPIO_ReadPin(XSHUT_0_GPIO_Port, XSHUT_0_Pin));
        break;
    case 1: // Sensor CENTER
        HAL_GPIO_WritePin(XSHUT_1_GPIO_Port, XSHUT_1_Pin, type);
        TEST_ASSERT_EQUAL(type, HAL_GPIO_ReadPin(XSHUT_1_GPIO_Port, XSHUT_1_Pin));
        break;
    case 2: // Sensor CENTER
        HAL_GPIO_WritePin(XSHUT_2_GPIO_Port, XSHUT_2_Pin, type);
        TEST_ASSERT_EQUAL(type, HAL_GPIO_ReadPin(XSHUT_2_GPIO_Port, XSHUT_2_Pin));
        break;
    case 3: // Sensor CENTER
        HAL_GPIO_WritePin(XSHUT_3_GPIO_Port, XSHUT_3_Pin, type);
        TEST_ASSERT_EQUAL(type, HAL_GPIO_ReadPin(XSHUT_3_GPIO_Port, XSHUT_3_Pin));
        break;
    case 4: // Sensor CENTER
        HAL_GPIO_WritePin(XSHUT_4_GPIO_Port, XSHUT_4_Pin, type);
        TEST_ASSERT_EQUAL(type, HAL_GPIO_ReadPin(XSHUT_4_GPIO_Port, XSHUT_4_Pin));
        break;
    default:
        break;
    }
}
