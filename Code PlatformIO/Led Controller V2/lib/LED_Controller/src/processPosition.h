#ifndef PROCESS_POSITION_H
#define PROCESS_POSITION_H


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
} position_t;

void processPosition_initPosition(position_t *_pos);
void processPosition_processPosition(position_t *_pos);
// void processPosition_set_position(position_t *_pos);
void processPosition_rowDown(position_t *_pos);
void processPosition_rowUp(position_t *_pos);
void processPosition_columnRight(position_t *_pos);
void processPosition_columnLeft(position_t *_pos);

#endif