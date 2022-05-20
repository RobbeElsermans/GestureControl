#include "processPosition.h"
#include "processGpiomatrix.h"
#include "processTimer.h"

void set_position(position_t *_pos);

void processPosition_initPosition(position_t *_pos)
{
    _pos->x = C1;
    _pos->y = R1;
    _pos->state = false;
}

void processPosition_turnOn(position_t *_pos){
    _pos->state = true;
}

void processPosition_turnOff(position_t *_pos){
    _pos->state = false;
}

void processPosition_processPosition(position_t *_pos)
{
    if(_pos->state)
    {
    gpio_matrix_t temp;
    uint8_t i = 0;
    // clear de pinnen
    for (i = C1; i <= C5; i++)
    {
        temp.column = i;
        processGpio_set_gpio_matrix(&temp, resetPin);
    }
    for (i = R1; i <= R7; i++)
    {
        temp.row = i;
        processGpio_set_gpio_matrix(&temp, resetPin);
    }

    // Schrijf naar GPIO
    temp.column = _pos->x;
    temp.row = _pos->y;
    processGpio_set_gpio_matrix(&temp, setPin);

    processTimer_delay(1);
    }
}
// position_t processPosition_get_position()
// {
// }
void set_position(position_t *_pos)
{
    if (_pos->x > C5)
        _pos->x = C1;
    else if (_pos->x < C1)
        _pos->x = C5;
    else
        _pos->x = _pos->x;

    if (_pos->y > R7)
        _pos->y = R1;
    else if (_pos->y < R1)
        _pos->y = R7;
    else
        _pos->y = _pos->y;
}

void processPosition_rowDown(position_t *_pos)
{
    _pos->y++;
    set_position(_pos);
}
void processPosition_rowUp(position_t *_pos)
{
    _pos->y--;
    set_position(_pos);
}
void processPosition_columnRight(position_t *_pos)
{
    _pos->x++;
    set_position(_pos);
}
void processPosition_columnLeft(position_t *_pos)
{
    _pos->x--;
    set_position(_pos);
}