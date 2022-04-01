#include <unity.h>
#include "i2c.h"
#include "usart.h"
#include "gpio.h"
#include "stdbool.h" //Nodig om bool te kunnen gebruiken
#include "stm32f4xx_hal.h"
#include "main.h"

void setUp(void)
{
    MX_GPIO_Init();
}

void tearDown(void)
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

int main()
{
    HAL_Init();
    HAL_Delay(2000);

    UNITY_BEGIN(); // IMPORTANT LINE!
    RUN_TEST(test_leds_pin_number);

    for (uint8_t x = 0; x < 2; x++)
    {
        HAL_Delay(500);
        RUN_TEST(test_led_0_state_high);
        HAL_Delay(500);
        RUN_TEST(test_led_0_state_low);
        HAL_Delay(500);
        RUN_TEST(test_led_1_state_high);
        HAL_Delay(500);
        RUN_TEST(test_led_1_state_low);
        HAL_Delay(500);
        RUN_TEST(test_led_2_state_high);
        HAL_Delay(500);
        RUN_TEST(test_led_2_state_low);
        HAL_Delay(500);
        RUN_TEST(test_led_3_state_high);
        HAL_Delay(500);
        RUN_TEST(test_led_3_state_low);
        HAL_Delay(500);
        RUN_TEST(test_led_4_state_high);
        HAL_Delay(500);
        RUN_TEST(test_led_4_state_low);
        HAL_Delay(500);
    }
    UNITY_END(); // stop unit testing
    while(true){}
}

void MX_GPIO_Init(void)
{

    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOH_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOA, XSHUT_1_Pin | XSHUT_2_Pin | XSHUT_3_Pin | XSHUT_0_Pin | LED_3_Pin | LED_4_Pin, GPIO_PIN_RESET);

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOB, XSHUT_4_Pin | LED_0_Pin | LED_1_Pin | LED_2_Pin, GPIO_PIN_RESET);

    /*Configure GPIO pins : PC13 PCPin PCPin */
    GPIO_InitStruct.Pin = GPIO_PIN_13 | SW_2_Pin | SW_1_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    /*Configure GPIO pins : PAPin PAPin PAPin PAPin
                             PAPin PAPin */
    GPIO_InitStruct.Pin = XSHUT_1_Pin | XSHUT_2_Pin | XSHUT_3_Pin | XSHUT_0_Pin | LED_3_Pin | LED_4_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /*Configure GPIO pins : PAPin PAPin */
    GPIO_InitStruct.Pin = GPIOI_4_Pin | GPIOI_1_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /*Configure GPIO pins : PBPin PBPin PBPin PBPin */
    GPIO_InitStruct.Pin = XSHUT_4_Pin | LED_0_Pin | LED_1_Pin | LED_2_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /*Configure GPIO pins : PCPin PCPin */
    GPIO_InitStruct.Pin = GPIOI_2_Pin | GPIOI_0_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    /*Configure GPIO pin : PtPin */
    GPIO_InitStruct.Pin = GPIOI_3_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOI_3_GPIO_Port, &GPIO_InitStruct);

    /* EXTI interrupt init*/
    HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
}

void SysTick_Handler(void)
{
    HAL_IncTick();
}