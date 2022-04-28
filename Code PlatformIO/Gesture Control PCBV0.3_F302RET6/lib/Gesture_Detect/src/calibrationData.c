#include "calibrationData.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Crosstalk data voor coverglas
/**
 * Dit moeten we herhalen bij telkens een nieuw coverglas op verschillende afstanden
 * Kijk hier file:///C:/Users/robel/Desktop/testing%20Nucleo/um2778-vl53l3cx-timeofflight-ranging-module-with-multi-object-detection-stmicroelectronics.pdf
 * voor meer uitleg (Voor mezelf)
 *
 */

void RefSpadCal(VL53L3CX_Object_t *dev)
{
    VL53LX_PerformRefSpadManagement(dev);
}
void xTalkCal(VL53L3CX_Object_t *dev)
{
    VL53LX_PerformXTalkCalibration(dev);
}
void offsetPerVcselCal(VL53L3CX_Object_t *dev, uint16_t distance)
{
    VL53LX_PerformOffsetPerVcselCalibration(dev, distance);
}
VL53LX_CalibrationData_t getCalibrationData(VL53L3CX_Object_t *dev)
{
    VL53LX_CalibrationData_t data;
    VL53LX_GetCalibrationData(dev, &data);
    return data;
}
void setCalibrationData(VL53L3CX_Object_t *dev, uint8_t index, VL53LX_CalibrationData_t *data)
{
    int xtalk_kcps[amountSensorUsed][6] = {
        {9964, 19847, 29730, 39613, 49496, 59382},
        {8863, 17511, 26159, 34807, 43455, 52105},
        {2888, 5885, 8882, 11879, 14876, 17874}};

    int xtalk_bin_data[amountSensorUsed][12] = {
        {9, 428, 470, 117, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 388, 477, 158, 0, 0, 0, 0, 0, 0, 0, 0},
        {13, 416, 476, 119, 0, 0, 0, 0, 0, 0, 0, 0}};

    switch (index)
    {
    case 0:

        for (uint8_t i = 0; i < 6; i++)
        {
            data->algo__xtalk_cpo_HistoMerge_kcps[i] = xtalk_kcps[index][i];
        }

        for (uint8_t i = 0; i < 12; i++)
        {
            data->xtalkhisto.xtalk_shape.bin_data[i] = xtalk_bin_data[index][i];
        }

        data->xtalkhisto.xtalk_shape.zero_distance_phase = 4169;
        data->xtalkhisto.xtalk_shape.phasecal_result__reference_phase = 10313;
        data->xtalkhisto.xtalk_shape.cal_config__vcsel_start = 9;
        data->xtalkhisto.xtalk_shape.zone_id = 0;
        data->xtalkhisto.xtalk_shape.vcsel_width = 40;
        data->xtalkhisto.xtalk_shape.VL53LX_p_015 = 48250;

        data->per_vcsel_cal_data.short_a_offset_mm = -41;
        data->per_vcsel_cal_data.short_b_offset_mm = -36;
        data->per_vcsel_cal_data.medium_a_offset_mm = -34;
        data->per_vcsel_cal_data.medium_b_offset_mm = -41;
        data->per_vcsel_cal_data.long_a_offset_mm = -32;
        data->per_vcsel_cal_data.long_b_offset_mm = -34;

        data->customer.global_config__spad_enables_ref_0 = 255;
        data->customer.global_config__spad_enables_ref_1 = 239;
        data->customer.global_config__spad_enables_ref_2 = 251;
        data->customer.global_config__spad_enables_ref_3 = 247;
        data->customer.global_config__spad_enables_ref_4 = 175;
        data->customer.global_config__spad_enables_ref_5 = 14;
        data->customer.ref_spad_man__num_requested_ref_spads = 10;
        data->customer.ref_spad_man__ref_location = 2;
        data->customer.algo__crosstalk_compensation_plane_offset_kcps = 9964;
        data->customer.ref_spad_char__total_rate_target_mcps = 2560;
        data->customer.mm_config__inner_offset_mm = 0;
        data->customer.mm_config__outer_offset_mm = 0;

        break;
    case 1:

        for (uint8_t i = 0; i < 6; i++)
        {
            data->algo__xtalk_cpo_HistoMerge_kcps[i] = xtalk_kcps[index][i];
        }

        for (uint8_t i = 0; i < 12; i++)
        {
            data->xtalkhisto.xtalk_shape.bin_data[i] = xtalk_bin_data[index][i];
        }

        data->xtalkhisto.xtalk_shape.zero_distance_phase = 4377;
        data->xtalkhisto.xtalk_shape.phasecal_result__reference_phase = 10521;
        data->xtalkhisto.xtalk_shape.cal_config__vcsel_start = 9;
        data->xtalkhisto.xtalk_shape.zone_id = 0;
        data->xtalkhisto.xtalk_shape.vcsel_width = 40;
        data->xtalkhisto.xtalk_shape.VL53LX_p_015 = 48373;

        data->per_vcsel_cal_data.short_a_offset_mm = -62;
        data->per_vcsel_cal_data.short_b_offset_mm = -58;
        data->per_vcsel_cal_data.medium_a_offset_mm = -52;
        data->per_vcsel_cal_data.medium_b_offset_mm = -57;
        data->per_vcsel_cal_data.long_a_offset_mm = -46;
        data->per_vcsel_cal_data.long_b_offset_mm = -48;

        data->customer.global_config__spad_enables_ref_0 = 223;
        data->customer.global_config__spad_enables_ref_1 = 231;
        data->customer.global_config__spad_enables_ref_2 = 255;
        data->customer.global_config__spad_enables_ref_3 = 255;
        data->customer.global_config__spad_enables_ref_4 = 247;
        data->customer.global_config__spad_enables_ref_5 = 15;
        data->customer.ref_spad_man__num_requested_ref_spads = 11;
        data->customer.ref_spad_man__ref_location = 2;
        data->customer.algo__crosstalk_compensation_plane_offset_kcps = 8863;
        data->customer.ref_spad_char__total_rate_target_mcps = 2560;
        data->customer.mm_config__inner_offset_mm = 0;
        data->customer.mm_config__outer_offset_mm = 0;
        break;
    case 2:
        for (uint8_t i = 0; i < 6; i++)
        {
            data->algo__xtalk_cpo_HistoMerge_kcps[i] = xtalk_kcps[index][i];
        }

        for (uint8_t i = 0; i < 12; i++)
        {
            data->xtalkhisto.xtalk_shape.bin_data[i] = xtalk_bin_data[index][i];
        }

        data->xtalkhisto.xtalk_shape.zero_distance_phase = 4177;
        data->xtalkhisto.xtalk_shape.phasecal_result__reference_phase = 10321;
        data->xtalkhisto.xtalk_shape.cal_config__vcsel_start = 9;
        data->xtalkhisto.xtalk_shape.zone_id = 0;
        data->xtalkhisto.xtalk_shape.vcsel_width = 40;
        data->xtalkhisto.xtalk_shape.VL53LX_p_015 = 48373;

        data->per_vcsel_cal_data.short_a_offset_mm = -40;
        data->per_vcsel_cal_data.short_b_offset_mm = -36;
        data->per_vcsel_cal_data.medium_a_offset_mm = -30;
        data->per_vcsel_cal_data.medium_b_offset_mm = -37;
        data->per_vcsel_cal_data.long_a_offset_mm = -29;
        data->per_vcsel_cal_data.long_b_offset_mm = -33;

        data->customer.global_config__spad_enables_ref_0 = 255;
        data->customer.global_config__spad_enables_ref_1 = 255;
        data->customer.global_config__spad_enables_ref_2 = 254;
        data->customer.global_config__spad_enables_ref_3 = 182;
        data->customer.global_config__spad_enables_ref_4 = 183;
        data->customer.global_config__spad_enables_ref_5 = 15;
        data->customer.ref_spad_man__num_requested_ref_spads = 12;
        data->customer.ref_spad_man__ref_location = 2;
        data->customer.algo__crosstalk_compensation_plane_offset_kcps = 2888;
        data->customer.ref_spad_char__total_rate_target_mcps = 2560;
        data->customer.mm_config__inner_offset_mm = 0;
        data->customer.mm_config__outer_offset_mm = 0;
        break;
    default:
        break;
    }

    VL53LX_SetCalibrationData(dev, data);
}

void setXTalkCompensation(VL53L3CX_Object_t *dev, bool state)
{
    VL53LX_SetXTalkCompensationEnable(dev, state);
}
void setOffsetCorrectionMode(VL53L3CX_Object_t *dev, VL53LX_OffsetCorrectionModes state)
{
    VL53LX_SetOffsetCorrectionMode(dev, state);
}