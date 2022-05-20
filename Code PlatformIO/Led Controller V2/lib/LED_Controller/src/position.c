#include "position.h"

#include "gpioMatrix.h"
#include "timer.h"

void set_position(position_t *_pos);

void position_initPosition(position_t *_pos)
{
    _pos->x = C1;
    _pos->y = R1;
    _pos->state = false;
}

void position_turnOn(position_t *_pos){
    _pos->state = true;
}

void position_turnOff(position_t *_pos){
    _pos->state = false;
}

void position_processPosition(position_t *_pos)
{
    if(_pos->state)
    {
    gpio_matrix_t temp;
    uint8_t i = 0;
    // clear de pinnen
    for (i = C1; i <= C5; i++)
    {
        temp.column = i;
        gpioMatrix_set_gpio_matrix(&temp, resetPin);
    }
    for (i = R1; i <= R7; i++)
    {
        temp.row = i;
        gpioMatrix_set_gpio_matrix(&temp, resetPin);
    }

    // Schrijf naar GPIO
    temp.column = _pos->x;
    temp.row = _pos->y;
    gpioMatrix_set_gpio_matrix(&temp, setPin);

    timer_delay(1);
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

void position_rowDown(position_t *_pos)
{
    _pos->y++;
    set_position(_pos);
}
void position_rowUp(position_t *_pos)
{
    _pos->y--;
    set_position(_pos);
}
void position_columnRight(position_t *_pos)
{
    _pos->x++;
    set_position(_pos);
}
void position_columnLeft(position_t *_pos)
{
    _pos->x--;
    set_position(_pos);
}