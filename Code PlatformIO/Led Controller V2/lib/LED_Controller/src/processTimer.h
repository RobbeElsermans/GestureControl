#ifndef PROCESS_TIMER_H
#define PROCESS_TIMER_H

#include "stdint.h"
#include "stdbool.h"

void processTimer_delay(int time);
long processTimer_getTicks();

#endif