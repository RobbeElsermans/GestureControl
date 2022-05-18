#include "calculations.h"

//variabelen die niet mogen veranderen na weg gaan van methodes
static int disMean[AMOUNT_SENSOR_USED][MAX_MEAN];
static uint8_t disMeanindex[AMOUNT_SENSOR_USED];

//private functions
void checkIndex(uint8_t id);

int calculations_getMean(uint8_t id)
{
    int16_t tempMean = 0;
    for (size_t i = 0; i < MAX_MEAN; i++)
    {
        tempMean += disMean[id][i];
    }
    tempMean /= MAX_MEAN;
    return tempMean;
}
int calculations_getCountMean(uint8_t id)
{
    return disMeanindex[id];
}
int *calculations_getMeans(uint8_t id)
{
    return disMean[id];
}
void calculations_setMeanVal(sensorData_t* sensor)
{
    disMean[sensor->id][disMeanindex[sensor->id]] = sensor->resultaat.distance;
    checkIndex(sensor->id);
}
int calculations_getMaxMean()
{
    return MAX_MEAN;
}

void checkIndex(uint8_t id){
    if (disMeanindex[id] < MAX_MEAN - 1)
        disMeanindex[id]++;
    else
        disMeanindex[id] = 0;
}