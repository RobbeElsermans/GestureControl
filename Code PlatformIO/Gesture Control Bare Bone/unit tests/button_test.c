#include <unity.h>
#include "gpio.h"
#include "stdbool.h" //Nodig om bool te kunnen gebruiken
#include "stm32f4xx_hal.h"
#include "main.h"
#include <stdio.h>
#include "../test/unittest_transport.h"

static void tearDown_button(void)
{
    HAL_GPIO_DeInit(SW_1_GPIO_Port, SW_1_Pin);
    HAL_GPIO_DeInit(SW_2_GPIO_Port, SW_2_Pin);
}

void test_button_pin_number(void)
{
    TEST_ASSERT_EQUAL(GPIO_PIN_1, SW_1_Pin);
    TEST_ASSERT_EQUAL(GPIOC, SW_1_GPIO_Port);

    TEST_ASSERT_EQUAL(GPIO_PIN_0, SW_2_Pin);
    TEST_ASSERT_EQUAL(GPIOC, SW_2_GPIO_Port);
}

void test_button_1_state_low(void)
{
    TEST_ASSERT_EQUAL(0, HAL_GPIO_ReadPin(SW_1_GPIO_Port, SW_1_Pin));
}

void test_button_1_state_high(void)
{
    while (!HAL_GPIO_ReadPin(SW_1_GPIO_Port, SW_1_Pin))
        ;
    TEST_ASSERT_EQUAL(1, HAL_GPIO_ReadPin(SW_1_GPIO_Port, SW_1_Pin));
}

void test_button_2_state_low(void)
{
    TEST_ASSERT_EQUAL(0, HAL_GPIO_ReadPin(SW_2_GPIO_Port, SW_2_Pin));
}

void test_button_2_state_high(void)
{
    while (!HAL_GPIO_ReadPin(SW_2_GPIO_Port, SW_2_Pin))
        ;
    TEST_ASSERT_EQUAL(1, HAL_GPIO_ReadPin(SW_2_GPIO_Port, SW_2_Pin));
}

void run_button_test()
{
    RUN_TEST(test_button_pin_number);

    RUN_TEST(test_button_1_state_low);
    RUN_TEST(test_button_1_state_high);
    HAL_Delay(500);
    RUN_TEST(test_button_2_state_low);
    RUN_TEST(test_button_2_state_high);
    HAL_Delay(500);

    tearDown_button();
}