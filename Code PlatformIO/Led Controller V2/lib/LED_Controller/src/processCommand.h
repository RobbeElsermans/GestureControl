#ifndef PROCESS_COMMAND_H
#define PROCESS_COMMAND_H

#include "stdint.h"
#include "stdbool.h"

typedef enum
{
    RL = 0x22,
    LR = 0x21,
    UD = 0x23,
    DU = 0x24,
    OBJ = 0x20,
    NONE = 0x10
} command_t;

void setCommand(command_t *command);
void processCommand();

#endif