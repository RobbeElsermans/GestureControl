#include "timer.h"

#include "stm32f3xx_hal.h"

void timer_delay(int time){
    long prevTime = timer_getTicks();
    while(timer_getTicks() - prevTime < time);
}
long timer_getTicks()
{
    return HAL_GetTick();
}