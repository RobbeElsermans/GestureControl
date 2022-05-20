#ifndef PROCESS_GPIO_H
#define PROCESS_GPIO_H

#include "stdint.h"
#include "stdbool.h"

// typedef enum{
//     R1,
//     R2,
//     R3,
//     R4,
//     R5,
//     R6,
//     R7,
// } gpio_row_t;

// typedef enum{
//     C1,
//     C2,
//     C3,
//     C4,
//     C5,
// } gpio_col_t;

typedef enum{
    led1,
    btn1,
     R1,
    R2,
    R3,
    R4,
    R5,
    R6,
    R7,
    C1,
    C2,
    C3,
    C4,
    C5,
} gpio_t;

typedef enum{
    resetPin,
    setPin,
} state_t;

void processGpio_initGpio();
void processGpio_set_gpio(gpio_t gpio ,int state);
void processGpio_get_gpio(gpio_t gpio);

#endif