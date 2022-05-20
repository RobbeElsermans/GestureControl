#ifndef COMMAND_H
#define COMMAND_H

#include "stdint.h"
#include "stdbool.h"
#include "position.h"

typedef enum
{
    RL = 0x22,
    LR = 0x21,
    UD = 0x23,
    DU = 0x24,
    OBJ = 0x20,
    NONE = 0x10
} command_t;

void command_initCommand(command_t *_command);
void command_processCommand(command_t *_command, position_t *_pos);

#endif