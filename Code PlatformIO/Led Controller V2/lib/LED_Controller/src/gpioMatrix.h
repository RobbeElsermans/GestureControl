#ifndef GPIO_MATRIX_H
#define GPIO_MATRIX_H

#include "gpio.h"

typedef struct{
gpio_t column;
gpio_t row;
}gpio_matrix_t;

void gpioMatrix_set_gpio_matrix(gpio_matrix_t *gpio, state_t state);

#endif