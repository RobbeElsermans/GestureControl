/**
 ******************************************************************************
 * @file          : GestureDetectDimming.c
 * @author        : Robbe Elsermans
 * @brief         : Dit bestand bevat de methodes om het dimmen te 
 * 					detecteren en de waarde hiervan op te vragen.
 ******************************************************************************
 *
 * @attention
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include "GestureDetectDimming.h"

static int maxDistanceObject = 400;
static float timerMeasurment = 0;
static bool timerMeasurementSet = false;
static int timerMeasurmentTimeout = 4000; // 2 seconden


	bool CheckDimmingCommand(bool *_dimming,bool *_objectPresent, int *_dis, int* _status)
	{
		if (*_objectPresent && (*_dis <= maxDistanceObject) && !*_dimming && (*_status == 0))
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
		else if((*_dis >= maxDistanceObject) && *_objectPresent){
			return false;
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
			return *_prevVal;
	}