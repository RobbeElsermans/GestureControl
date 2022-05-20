#include "command.h"

static command_t command;

void command_initCommand(command_t *_command)
{
    command = *_command;
}

void command_processCommand(command_t *_command, position_t *_pos)
{
    if (command >= OBJ)
    {
        // Ontvang data
        if (*_command == RL && (command == OBJ || command != *_command))
            position_columnLeft(_pos);
    
        if (*_command == LR && (command == OBJ || command != *_command))
            position_columnRight(_pos);

        if (*_command == UD && (command == OBJ || command != *_command))
            position_rowDown(_pos);

        if (*_command == DU && (command == OBJ || command != *_command))
            position_rowUp(_pos);
    
    }
    else if (*_command == NONE && command >= OBJ)
    {
        position_turnOff(_pos);
    }
    else if(*_command == OBJ && command == NONE)
    {
        position_turnOn(_pos);
    }
    
    if(*_command >= OBJ){
        position_processPosition(_pos);
    }

    command = *_command;
}