#include "calibrationData.h"

// Crosstalk data voor coverglas
/**
 * Dit moeten we herhalen bij telkens een nieuw coverglas op verschillende afstanden
 * Kijk hier file:///C:/Users/robel/Desktop/testing%20Nucleo/um2778-vl53l3cx-timeofflight-ranging-module-with-multi-object-detection-stmicroelectronics.pdf
 * voor meer uitleg (Voor mezelf)
 *
 */

void RefSpadCal(uint8_t dev)
{
    VL53LX_PerformRefSpadManagement(VL53L3A2_RANGING_SENSOR_CompObj[dev]);
}
void xTalkCal(uint8_t dev)
{
    VL53LX_PerformXTalkCalibration(VL53L3A2_RANGING_SENSOR_CompObj[dev]);
}
void offsetPerVcselCal(uint8_t dev, uint16_t distance)
{
    VL53LX_PerformOffsetPerVcselCalibration(VL53L3A2_RANGING_SENSOR_CompObj[dev], distance);
}
VL53LX_CalibrationData_t getCalibrationData(uint8_t dev)
{
    VL53LX_CalibrationData_t callData;
    VL53LX_GetCalibrationData(VL53L3A2_RANGING_SENSOR_CompObj[dev], &callData);
    return callData;
}
void setCalibrationData(uint8_t dev, VL53LX_CalibrationData_t data)
{
    int xtalk_kcps[5][6] = {
        {243, 493, 743, 993, 1243, 1494},
        {941, 1878, 2815, 3752, 4689, 5627},
        {611, 1209, 1807, 2405, 3003, 3601},
        {611, 1209, 1807, 2405, 3003, 3601},
        {611, 1209, 1807, 2405, 3003, 3601}};

    int xtalk_bin_data[5][12] = {
        {11, 327, 506, 180, 0, 0, 0, 0, 0, 0, 0, 0},
        {20, 429, 454, 121, 0, 0, 0, 0, 0, 0, 0, 0},
        {14, 425, 461, 124, 0, 0, 0, 0, 0, 0, 0, 0},
        {14, 425, 461, 124, 0, 0, 0, 0, 0, 0, 0, 0},
        {14, 425, 461, 124, 0, 0, 0, 0, 0, 0, 0, 0}};

    switch (dev)
    {
    case 0: // LEFT

        for (uint8_t i = 0; i < 6; i++)
        {
            data.algo__xtalk_cpo_HistoMerge_kcps[i] = xtalk_kcps[dev][i];
        }

        for (uint8_t i = 0; i < 12; i++)
        {
            data.xtalkhisto.xtalk_shape.bin_data[i] = xtalk_bin_data[dev][i];
        }

        data.xtalkhisto.xtalk_shape.zero_distance_phase = 4481;
        data.per_vcsel_cal_data.long_a_offset_mm = -33;
        data.per_vcsel_cal_data.long_b_offset_mm = 35;
        data.per_vcsel_cal_data.medium_a_offset_mm = -46;
        data.per_vcsel_cal_data.medium_b_offset_mm = -46;
        data.per_vcsel_cal_data.short_a_offset_mm = 43;
        data.per_vcsel_cal_data.short_b_offset_mm = -43;
        break;
    case 1: // CENTER

        for (uint8_t i = 0; i < 6; i++)
        {
            data.algo__xtalk_cpo_HistoMerge_kcps[i] = xtalk_kcps[dev][i];
        }

        for (uint8_t i = 0; i < 12; i++)
        {
            data.xtalkhisto.xtalk_shape.bin_data[i] = xtalk_bin_data[dev][i];
        }

        data.xtalkhisto.xtalk_shape.zero_distance_phase = 4186;
        data.per_vcsel_cal_data.long_a_offset_mm = -25;
        data.per_vcsel_cal_data.long_b_offset_mm = -25;
        data.per_vcsel_cal_data.medium_a_offset_mm = -28;
        data.per_vcsel_cal_data.medium_b_offset_mm = -30;
        data.per_vcsel_cal_data.short_a_offset_mm = -31;
        data.per_vcsel_cal_data.short_b_offset_mm = -27;
        break;
    case 2: // RIGHT
        for (uint8_t i = 0; i < 6; i++)
        {
            data.algo__xtalk_cpo_HistoMerge_kcps[i] = xtalk_kcps[dev][i];
        }

        for (uint8_t i = 0; i < 12; i++)
        {
            data.xtalkhisto.xtalk_shape.bin_data[i] = xtalk_bin_data[dev][i];
        }

        data.xtalkhisto.xtalk_shape.zero_distance_phase = 4204;
        data.per_vcsel_cal_data.long_a_offset_mm = -32;
        data.per_vcsel_cal_data.long_b_offset_mm = -34;
        data.per_vcsel_cal_data.medium_a_offset_mm = -34;
        data.per_vcsel_cal_data.medium_b_offset_mm = -38;
        data.per_vcsel_cal_data.short_a_offset_mm = -40;
        data.per_vcsel_cal_data.short_b_offset_mm = -40;
        break;

    case 3: // TOP
        for (uint8_t i = 0; i < 6; i++)
        {
            data.algo__xtalk_cpo_HistoMerge_kcps[i] = xtalk_kcps[dev][i];
        }

        for (uint8_t i = 0; i < 12; i++)
        {
            data.xtalkhisto.xtalk_shape.bin_data[i] = xtalk_bin_data[dev][i];
        }

        data.xtalkhisto.xtalk_shape.zero_distance_phase = 4204;
        data.per_vcsel_cal_data.long_a_offset_mm = -32;
        data.per_vcsel_cal_data.long_b_offset_mm = -34;
        data.per_vcsel_cal_data.medium_a_offset_mm = -34;
        data.per_vcsel_cal_data.medium_b_offset_mm = -38;
        data.per_vcsel_cal_data.short_a_offset_mm = -40;
        data.per_vcsel_cal_data.short_b_offset_mm = -40;
        break;

    case 4: // BOTTOM
        for (uint8_t i = 0; i < 6; i++)
        {
            data.algo__xtalk_cpo_HistoMerge_kcps[i] = xtalk_kcps[dev][i];
        }

        for (uint8_t i = 0; i < 12; i++)
        {
            data.xtalkhisto.xtalk_shape.bin_data[i] = xtalk_bin_data[dev][i];
        }

        data.xtalkhisto.xtalk_shape.zero_distance_phase = 4204;
        data.per_vcsel_cal_data.long_a_offset_mm = -32;
        data.per_vcsel_cal_data.long_b_offset_mm = -34;
        data.per_vcsel_cal_data.medium_a_offset_mm = -34;
        data.per_vcsel_cal_data.medium_b_offset_mm = -38;
        data.per_vcsel_cal_data.short_a_offset_mm = -40;
        data.per_vcsel_cal_data.short_b_offset_mm = -40;
        break;

    default:
        break;
    }

    VL53LX_SetCalibrationData(VL53L3A2_RANGING_SENSOR_CompObj[dev], &data);
}

void setXTalkCompensation(uint8_t dev, bool state)
{
    VL53LX_SetXTalkCompensationEnable(VL53L3A2_RANGING_SENSOR_CompObj[dev], state);
}
void setOffsetCorrectionMode(uint8_t dev, VL53LX_OffsetCorrectionModes state)
{
    VL53LX_SetOffsetCorrectionMode(VL53L3A2_RANGING_SENSOR_CompObj[dev], state);
}