#ifndef PROCESS_GPIO_MATRIX_H
#define PROCESS_GPIO_MATRIX_H

#include "processGpio.h"

typedef struct{
gpio_t column;
gpio_t row;
}gpio_matrix_t;

void processGpio_set_gpio_matrix(gpio_matrix_t *gpio, state_t state);

#endif