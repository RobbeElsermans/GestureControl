#include "GestureDetectDimming.h"

static int maxDistanceObject = 490;
static float timerMeasurment = 0;
static bool timerMeasurementSet = false;
static int timerMeasurmentTimeout = 2000; // 2 seconden

	bool CheckDimmingCommand(bool *_dimming,bool *_objectPresent, int *_dis)
	{
		if (*_objectPresent && (*_dis <= maxDistanceObject) && !*_dimming)
		{
			if (!timerMeasurementSet)
			{
				timerMeasurementSet = true;
				timerMeasurment = HAL_GetTick();
			}
			if ((HAL_GetTick() - timerMeasurment) >= timerMeasurmentTimeout)
			{
				timerMeasurementSet = false;
				return  true;
			}
		}
		else
		{
			if (timerMeasurementSet)
			{
				timerMeasurementSet = false;
			}
		}
		return *_dimming;
	}

	int getDimmingValue(bool *_dimming, int *_prevVal, int *_dis){
			if (*_dimming && (*_dis <= maxDistanceObject))
			{
				if (_prevVal != 0)
				{
					if ((_prevVal + 30) > *_dis || (_prevVal - 30) < *_dis)
					{
						return *_dis;
					}
					else
					{
						*_dimming = false;
					}
				}
				else
				{
					return *_dis;
				}
			}
			else
			{
				*_dimming = false;
                return *_prevVal;
			}
	}