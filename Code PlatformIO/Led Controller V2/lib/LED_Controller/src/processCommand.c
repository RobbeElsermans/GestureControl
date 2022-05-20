#include "processCommand.h"

static command_t *command;

void setCommand(command_t *_command){
    command = _command;
}

void processCommand(){
    if(*command == OBJ)
    {
        ;
        //doe iets
    }
}