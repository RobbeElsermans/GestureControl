#include "GestureDetect.h"

int16_t tempMean = 0;

commands detectgesture(int16_t left, int16_t center, int16_t right)
{
    
}

int16_t getMean(uint8_t id, int16_t distance)
{
        disMean[id][disMeanindex[id]] = distance;
        if (disMeanindex[id] < maxMean - 1)
            disMeanindex[id]++;
        else
            disMeanindex[id] = 0;

        tempMean = 0;
        for (size_t i = 0; i < maxMean; i++)
        {
            tempMean += disMean[id][i];
        }
        tempMean /= maxMean;
        return tempMean;
}
int getCountMeans(uint8_t id){
    return disMeanindex[id];
}
int * getMeans(uint8_t id){
    return disMean[id];
}
uint8_t getMaxMean(){
    return maxMean;
}
uint8_t getMaxDis(){
    return maxDistance;
}