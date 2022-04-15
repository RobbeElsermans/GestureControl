#include "calibrationData.h"

// Crosstalk data voor coverglas
/**
 * Dit moeten we herhalen bij telkens een nieuw coverglas op verschillende afstanden
 * Kijk hier file:///C:/Users/robel/Desktop/testing%20Nucleo/um2778-vl53l3cx-timeofflight-ranging-module-with-multi-object-detection-stmicroelectronics.pdf
 * voor meer uitleg (Voor mezelf)
 *
 */

void RefSpadCal(VL53L3CX_Object_t* dev)
{
    VL53LX_PerformRefSpadManagement(dev);
}
void xTalkCal(VL53L3CX_Object_t* dev)
{
    VL53LX_PerformXTalkCalibration(dev);
}
void offsetPerVcselCal(VL53L3CX_Object_t* dev, uint16_t distance)
{
    VL53LX_PerformOffsetPerVcselCalibration(dev, distance);
}
VL53LX_CalibrationData_t getCalibrationData(VL53L3CX_Object_t* dev)
{
    VL53LX_CalibrationData_t callData;
    VL53LX_GetCalibrationData(dev, &callData);
    return callData;
}
void setCalibrationData(VL53L3CX_Object_t* dev,sensorDev index, VL53LX_CalibrationData_t data)
{
    int xtalk_kcps[amountSensor][6] = {
        {754, 1533, 2312, 3091, 3870, 4651},
        {1385, 2823, 4261, 5699, 7137, 8578},
        {839, 1644, 2449, 3254, 4059, 4865},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0}};

    int xtalk_bin_data[amountSensor][12] = {
        {14, 435, 450, 125, 0, 0, 0, 0, 0, 0, 0, 0},
        {22, 432, 451, 119, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 376, 481, 167, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

    switch (index)
    {
    case 0: // LEFT

        for (uint8_t i = 0; i < 6; i++)
        {
           data.algo__xtalk_cpo_HistoMerge_kcps[i] = xtalk_kcps[index][i];
        }

        for (uint8_t i = 0; i < 12; i++)
        {
           data.xtalkhisto.xtalk_shape.bin_data[i] = xtalk_bin_data[index][i];
        }

       data.xtalkhisto.xtalk_shape.zero_distance_phase = 4208;
        
       data.per_vcsel_cal_data.short_a_offset_mm = -27;
       data.per_vcsel_cal_data.short_b_offset_mm = -28;
       data.per_vcsel_cal_data.medium_a_offset_mm = -24;
       data.per_vcsel_cal_data.medium_b_offset_mm = -26;
       data.per_vcsel_cal_data.long_a_offset_mm = -18;
       data.per_vcsel_cal_data.long_b_offset_mm = -21;
        
        break;
    case 1: // CENTER

        for (uint8_t i = 0; i < 6; i++)
        {
           data.algo__xtalk_cpo_HistoMerge_kcps[i] = xtalk_kcps[index][i];
        }

        for (uint8_t i = 0; i < 12; i++)
        {
           data.xtalkhisto.xtalk_shape.bin_data[i] = xtalk_bin_data[index][i];
        }

       data.xtalkhisto.xtalk_shape.zero_distance_phase = 4177;
       data.per_vcsel_cal_data.short_a_offset_mm = -31;
       data.per_vcsel_cal_data.short_b_offset_mm = -27;
       data.per_vcsel_cal_data.medium_a_offset_mm = -21;
       data.per_vcsel_cal_data.medium_b_offset_mm = -26;
       data.per_vcsel_cal_data.long_a_offset_mm = -23;
       data.per_vcsel_cal_data.long_b_offset_mm = -24;
        break;
    case 2: // RIGHT
        for (uint8_t i = 0; i < 6; i++)
        {
           data.algo__xtalk_cpo_HistoMerge_kcps[i] = xtalk_kcps[index][i];
        }

        for (uint8_t i = 0; i < 12; i++)
        {
           data.xtalkhisto.xtalk_shape.bin_data[i] = xtalk_bin_data[index][i];
        }

       data.xtalkhisto.xtalk_shape.zero_distance_phase = 4446;
       data.per_vcsel_cal_data.short_a_offset_mm = -27;
       data.per_vcsel_cal_data.short_b_offset_mm = -27;
       data.per_vcsel_cal_data.medium_a_offset_mm = -24;
       data.per_vcsel_cal_data.medium_b_offset_mm = -25;
       data.per_vcsel_cal_data.long_a_offset_mm = -19;
       data.per_vcsel_cal_data.long_b_offset_mm = -20;
        break;

    case 3: // TOP
        for (uint8_t i = 0; i < 6; i++)
        {
           data.algo__xtalk_cpo_HistoMerge_kcps[i] = xtalk_kcps[index][i];
        }

        for (uint8_t i = 0; i < 12; i++)
        {
           data.xtalkhisto.xtalk_shape.bin_data[i] = xtalk_bin_data[index][i];
        }

       data.xtalkhisto.xtalk_shape.zero_distance_phase = 0;
       data.per_vcsel_cal_data.short_a_offset_mm = -37;
       data.per_vcsel_cal_data.short_b_offset_mm = -40;
       data.per_vcsel_cal_data.medium_a_offset_mm = -48;
       data.per_vcsel_cal_data.medium_b_offset_mm = -48;
       data.per_vcsel_cal_data.long_a_offset_mm = -33;
       data.per_vcsel_cal_data.long_b_offset_mm = -35;
        break;

    case 4: // BOTTOM
        for (uint8_t i = 0; i < 6; i++)
        {
           data.algo__xtalk_cpo_HistoMerge_kcps[i] = xtalk_kcps[index][i];
        }

        for (uint8_t i = 0; i < 12; i++)
        {
           data.xtalkhisto.xtalk_shape.bin_data[i] = xtalk_bin_data[index][i];
        }

       data.xtalkhisto.xtalk_shape.zero_distance_phase = 0;
       data.per_vcsel_cal_data.short_a_offset_mm = -68;
       data.per_vcsel_cal_data.short_b_offset_mm = -70;
       data.per_vcsel_cal_data.medium_a_offset_mm = -56;
       data.per_vcsel_cal_data.medium_b_offset_mm = -58;
       data.per_vcsel_cal_data.long_a_offset_mm = -58;
       data.per_vcsel_cal_data.long_b_offset_mm = -61;
        break;

    default:
        break;
    }

    VL53LX_SetCalibrationData(dev, &data);
}

void setXTalkCompensation(VL53L3CX_Object_t* dev, bool state)
{
    VL53LX_SetXTalkCompensationEnable(dev, state);
}
void setOffsetCorrectionMode(VL53L3CX_Object_t* dev, VL53LX_OffsetCorrectionModes state)
{
    VL53LX_SetOffsetCorrectionMode(dev, state);
}