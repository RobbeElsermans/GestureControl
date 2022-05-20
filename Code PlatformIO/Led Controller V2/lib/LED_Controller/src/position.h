#ifndef POSITION_H
#define POSITION_H


#include "stdint.h"
#include "stdbool.h"

#define MAX_X_POS 5
#define MAX_Y_POS 7

/**
 * @brief Struct die de positie onderhoud van de led controller
 * 
 */
typedef struct{
    int8_t x;
    int8_t y;
    bool state;
} position_t;

void position_initPosition(position_t *_pos);
void position_turnOn(position_t *_pos);
void position_turnOff(position_t *_pos);
void position_processPosition(position_t *_pos);
// void processPosition_set_position(position_t *_pos);
void position_rowDown(position_t *_pos);
void position_rowUp(position_t *_pos);
void position_columnRight(position_t *_pos);
void position_columnLeft(position_t *_pos);

#endif