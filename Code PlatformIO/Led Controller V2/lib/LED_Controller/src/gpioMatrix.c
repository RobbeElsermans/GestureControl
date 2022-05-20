#include "gpioMatrix.h"

void gpioMatrix_set_gpio_matrix(gpio_matrix_t *gpio, state_t state){
    gpio_set_gpio(gpio->column, state);
    gpio_set_gpio(gpio->row, state);
}