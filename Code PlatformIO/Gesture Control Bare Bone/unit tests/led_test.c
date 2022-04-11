#include "led_test.h"

static void tearDown_led(void)
{
    HAL_GPIO_DeInit(LED_0_GPIO_Port, LED_0_Pin);
    HAL_GPIO_DeInit(LED_1_GPIO_Port, LED_1_Pin);
    HAL_GPIO_DeInit(LED_2_GPIO_Port, LED_2_Pin);
    HAL_GPIO_DeInit(LED_3_GPIO_Port, LED_3_Pin);
    HAL_GPIO_DeInit(LED_4_GPIO_Port, LED_4_Pin);
}

void test_leds_pin_number(void)
{
    TEST_ASSERT_EQUAL(GPIO_PIN_10, LED_0_Pin);
    TEST_ASSERT_EQUAL(GPIOB, LED_0_GPIO_Port);

    TEST_ASSERT_EQUAL(GPIO_PIN_4, LED_1_Pin);
    TEST_ASSERT_EQUAL(GPIOB, LED_1_GPIO_Port);

    TEST_ASSERT_EQUAL(GPIO_PIN_5, LED_2_Pin);
    TEST_ASSERT_EQUAL(GPIOB, LED_2_GPIO_Port);

    TEST_ASSERT_EQUAL(GPIO_PIN_7, LED_3_Pin);
    TEST_ASSERT_EQUAL(GPIOA, LED_3_GPIO_Port);

    TEST_ASSERT_EQUAL(GPIO_PIN_10, LED_4_Pin);
    TEST_ASSERT_EQUAL(GPIOA, LED_4_GPIO_Port);
}

void test_led_0_state_high(void)
{
    HAL_GPIO_WritePin(LED_0_GPIO_Port, LED_0_Pin, 1);
    HAL_Delay(200);
    TEST_ASSERT_EQUAL(1, HAL_GPIO_ReadPin(LED_0_GPIO_Port, LED_0_Pin));
}

void test_led_1_state_high(void)
{
    HAL_GPIO_WritePin(LED_1_GPIO_Port, LED_1_Pin, 1);
    HAL_Delay(200);
    TEST_ASSERT_EQUAL(1, HAL_GPIO_ReadPin(LED_1_GPIO_Port, LED_1_Pin));
}

void test_led_2_state_high(void)
{
    HAL_GPIO_WritePin(LED_2_GPIO_Port, LED_2_Pin, 1);
    HAL_Delay(200);
    TEST_ASSERT_EQUAL(1, HAL_GPIO_ReadPin(LED_2_GPIO_Port, LED_2_Pin));
}

void test_led_3_state_high(void)
{
    HAL_GPIO_WritePin(LED_3_GPIO_Port, LED_3_Pin, 1);
    HAL_Delay(200);
    TEST_ASSERT_EQUAL(1, HAL_GPIO_ReadPin(LED_3_GPIO_Port, LED_3_Pin));
}

void test_led_4_state_high(void)
{
    HAL_GPIO_WritePin(LED_4_GPIO_Port, LED_4_Pin, 1);
    HAL_Delay(200);
    TEST_ASSERT_EQUAL(1, HAL_GPIO_ReadPin(LED_4_GPIO_Port, LED_4_Pin));
}

void test_led_0_state_low(void)
{
    HAL_GPIO_WritePin(LED_0_GPIO_Port, LED_0_Pin, 0);
    TEST_ASSERT_EQUAL(0, HAL_GPIO_ReadPin(LED_0_GPIO_Port, LED_0_Pin));
}

void test_led_1_state_low(void)
{
    HAL_GPIO_WritePin(LED_1_GPIO_Port, LED_1_Pin, 0);
    TEST_ASSERT_EQUAL(0, HAL_GPIO_ReadPin(LED_1_GPIO_Port, LED_1_Pin));
}

void test_led_2_state_low(void)
{
    HAL_GPIO_WritePin(LED_2_GPIO_Port, LED_2_Pin, 0);
    TEST_ASSERT_EQUAL(0, HAL_GPIO_ReadPin(LED_2_GPIO_Port, LED_2_Pin));
}

void test_led_3_state_low(void)
{
    HAL_GPIO_WritePin(LED_3_GPIO_Port, LED_3_Pin, 0);
    TEST_ASSERT_EQUAL(0, HAL_GPIO_ReadPin(LED_3_GPIO_Port, LED_3_Pin));
}

void test_led_4_state_low(void)
{
    HAL_GPIO_WritePin(LED_4_GPIO_Port, LED_4_Pin, 0);
    TEST_ASSERT_EQUAL(0, HAL_GPIO_ReadPin(LED_4_GPIO_Port, LED_4_Pin));
}

void run_led_test(){
    
    RUN_TEST(test_leds_pin_number);

    for (uint8_t x = 0; x < 2; x++)
    {
        HAL_Delay(500);
        RUN_TEST(test_led_0_state_high);
        HAL_Delay(500);
        RUN_TEST(test_led_0_state_low);
        RUN_TEST(test_led_1_state_high);
        HAL_Delay(500);
        RUN_TEST(test_led_1_state_low);
        RUN_TEST(test_led_2_state_high);
        HAL_Delay(500);
        RUN_TEST(test_led_2_state_low);
        RUN_TEST(test_led_3_state_high);
        HAL_Delay(500);
        RUN_TEST(test_led_3_state_low);
        RUN_TEST(test_led_4_state_high);
        HAL_Delay(500);
        RUN_TEST(test_led_4_state_low);
    }

    tearDown_led();
    
}