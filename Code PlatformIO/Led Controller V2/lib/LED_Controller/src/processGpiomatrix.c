#include "processGpiomatrix.h"

void processGpio_set_gpio_matrix(gpio_matrix_t *gpio, state_t state){
    processGpio_set_gpio(gpio->column, state);
    processGpio_set_gpio(gpio->row, state);
}