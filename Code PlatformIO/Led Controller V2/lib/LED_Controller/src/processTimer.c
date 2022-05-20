#include "processTimer.h"

#include "stm32f4xx_hal.h"

void processTimer_delay(int time){
    long prevTime = processTimer_getTicks();
    while(processTimer_getTicks() - prevTime < time);
}
long processTimer_getTicks()
{
    return HAL_GetTick();
}