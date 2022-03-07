#ifndef _GESTUREDETECTDIMMING_H
#define _GESTUREDETECTDIMMING_H

#include "stdbool.h" //Nodig om bool te kunnen gebruiken

/**
 * @brief  Detecteerd het dimming commando
 *
 * @param  _dimming pointer dat de huidige dimming state bevat
 * @param  _objectPresent pointer dat de huidige state van object present meegeeft (ofdat er een object aanwezig is of niet)
 * @param  _dis0 de huidige meeting van sensor X
 * @note   De maximale afstand dat een object mag hebben is de parameter maxDistanceObject.
 * @note   De tijd wanneer er een object gedetecteerd wordt is gedefinieerd in timerMeasurmentTimeout.
 * @note   Wanneer een object onder deze afstand + tijd komt, is het dimming command aanwezig
 * @retval  bool Dimming Command Active
 */
bool CheckDimmingCommand(bool *_dimming, bool *_objectPresent, int *_dis);

/**
 * @brief  Geeft de waarde terug die gebruikt kan worden als PWMVal tussen 0 - maxDistanceObject.
 *
 * @param  _dimming pointer dat de huidige dimming state bevat
 * @param  _prevVal De voorgaande value
 * @param  _dis0 de huidige meeting van sensor X
 * @note   De maximale afstand dat een object mag hebben is de parameter maxDistanceObject.
 * @note   De tijd wanneer er een object gedetecteerd wordt is gedefinieerd in timerMeasurmentTimeout.
 * @retval int waarde van 0 - 1023
 */
int getDimmingValue(bool *_dimming, int* _prevVal, int *_dis);

#endif