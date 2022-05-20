#ifndef PROCESS_TIMER_H
#define PROCESS_TIMER_H

#include "stdint.h"
#include "stdbool.h"

void timer_delay(int time);
long timer_getTicks();

#endif