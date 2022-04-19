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
void setCalibrationData(VL53L3CX_Object_t *dev, sensorDev index, VL53LX_CalibrationData_t *data)
{
    int xtalk_kcps[amountSensor][6] = {
        {2549, 5182, 7815, 10448, 13081, 15715},
        {4062, 8006, 11950, 15894, 19838, 23784},
        {9767, 19686, 29605, 39524, 49443, 59366},
        {5957, 11919, 17881, 23843, 29805, 35769},
        {6185, 12293, 18401, 24509, 0, 134276756}};

    int xtalk_bin_data[amountSensor][12] = {
        {1, 339, 484, 200, 0, 0, 0, 0, 0, 0, 0, 0},
        {2, 345, 473, 204, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 342, 485, 196, 0, 0, 0, 0, 0, 0, 0, 0},
        {3, 354, 490, 177, 0, 0, 0, 0, 0, 0, 0, 0},
        {11, 413, 471, 129, 0, 0, 0, 0, 0, 0, 0, 0}};

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

        data->xtalkhisto.xtalk_shape.zero_distance_phase = 4602;
        data->xtalkhisto.xtalk_shape.phasecal_result__reference_phase = 10746;
        data->xtalkhisto.xtalk_shape.cal_config__vcsel_start = 9;
        data->xtalkhisto.xtalk_shape.zone_id = 0;
        data->xtalkhisto.xtalk_shape.vcsel_width = 40;
        data->xtalkhisto.xtalk_shape.VL53LX_p_015 = 48322;

        // data->per_vcsel_cal_data.short_a_offset_mm = -16;
        // data->per_vcsel_cal_data.short_b_offset_mm = -15;
        // data->per_vcsel_cal_data.medium_a_offset_mm = -11;
        // data->per_vcsel_cal_data.medium_b_offset_mm = -15;
        // data->per_vcsel_cal_data.long_a_offset_mm = -10;
        // data->per_vcsel_cal_data.long_b_offset_mm = -11;

        data->customer.global_config__spad_enables_ref_0 = 123;
        data->customer.global_config__spad_enables_ref_1 = 255;
        data->customer.global_config__spad_enables_ref_2 = 255;
        data->customer.global_config__spad_enables_ref_3 = 255;
        data->customer.global_config__spad_enables_ref_4 = 255;
        data->customer.global_config__spad_enables_ref_5 = 13;
        data->customer.ref_spad_man__num_requested_ref_spads = 11;
        data->customer.ref_spad_man__ref_location = 2;
        data->customer.algo__crosstalk_compensation_plane_offset_kcps = 2634;
        data->customer.ref_spad_char__total_rate_target_mcps = 2560;
        data->customer.mm_config__inner_offset_mm = 17;
        data->customer.mm_config__outer_offset_mm = 17;

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

        data->xtalkhisto.xtalk_shape.zero_distance_phase = 4628;
        data->xtalkhisto.xtalk_shape.phasecal_result__reference_phase = 10772;
        data->xtalkhisto.xtalk_shape.cal_config__vcsel_start = 6;
        data->xtalkhisto.xtalk_shape.zone_id = 0;
        data->xtalkhisto.xtalk_shape.vcsel_width = 40;
        data->xtalkhisto.xtalk_shape.VL53LX_p_015 = 48332;

        // data->per_vcsel_cal_data.short_a_offset_mm = -16;
        // data->per_vcsel_cal_data.short_b_offset_mm = -15;
        // data->per_vcsel_cal_data.medium_a_offset_mm = -11;
        // data->per_vcsel_cal_data.medium_b_offset_mm = -15;
        // data->per_vcsel_cal_data.long_a_offset_mm = -10;
        // data->per_vcsel_cal_data.long_b_offset_mm = -11;

        data->customer.global_config__spad_enables_ref_0 = 255;
        data->customer.global_config__spad_enables_ref_1 = 127;
        data->customer.global_config__spad_enables_ref_2 = 247;
        data->customer.global_config__spad_enables_ref_3 = 251;
        data->customer.global_config__spad_enables_ref_4 = 247;
        data->customer.global_config__spad_enables_ref_5 = 15;
        data->customer.ref_spad_man__num_requested_ref_spads = 10;
        data->customer.ref_spad_man__ref_location = 2;
        data->customer.algo__crosstalk_compensation_plane_offset_kcps = 4053;
        data->customer.ref_spad_char__total_rate_target_mcps = 2560;
        data->customer.mm_config__inner_offset_mm = 23;
        data->customer.mm_config__outer_offset_mm = 23;
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

        data->xtalkhisto.xtalk_shape.zero_distance_phase = 4575;
        data->xtalkhisto.xtalk_shape.phasecal_result__reference_phase = 10719;
        data->xtalkhisto.xtalk_shape.cal_config__vcsel_start = 6;
        data->xtalkhisto.xtalk_shape.zone_id = 0;
        data->xtalkhisto.xtalk_shape.vcsel_width = 40;
        data->xtalkhisto.xtalk_shape.VL53LX_p_015 = 48373;

        // data->per_vcsel_cal_data.short_a_offset_mm = -16;
        // data->per_vcsel_cal_data.short_b_offset_mm = -15;
        // data->per_vcsel_cal_data.medium_a_offset_mm = -11;
        // data->per_vcsel_cal_data.medium_b_offset_mm = -15;
        // data->per_vcsel_cal_data.long_a_offset_mm = -10;
        // data->per_vcsel_cal_data.long_b_offset_mm = -11;

        data->customer.global_config__spad_enables_ref_0 = 191;
        data->customer.global_config__spad_enables_ref_1 = 247;
        data->customer.global_config__spad_enables_ref_2 = 255;
        data->customer.global_config__spad_enables_ref_3 = 223;
        data->customer.global_config__spad_enables_ref_4 = 251;
        data->customer.global_config__spad_enables_ref_5 = 15;
        data->customer.ref_spad_man__num_requested_ref_spads = 12;
        data->customer.ref_spad_man__ref_location = 2;
        data->customer.algo__crosstalk_compensation_plane_offset_kcps = 9870;
        data->customer.ref_spad_char__total_rate_target_mcps = 2560;
        data->customer.mm_config__inner_offset_mm = 25;
        data->customer.mm_config__outer_offset_mm = 25;
        break;

    case 3:
        for (uint8_t i = 0; i < 6; i++)
        {
            data->algo__xtalk_cpo_HistoMerge_kcps[i] = xtalk_kcps[index][i];
        }

        for (uint8_t i = 0; i < 12; i++)
        {
            data->xtalkhisto.xtalk_shape.bin_data[i] = xtalk_bin_data[index][i];
        }

        data->xtalkhisto.xtalk_shape.zero_distance_phase = 4441;
        data->xtalkhisto.xtalk_shape.phasecal_result__reference_phase = 10585;
        data->xtalkhisto.xtalk_shape.cal_config__vcsel_start = 9;
        data->xtalkhisto.xtalk_shape.zone_id = 0;
        data->xtalkhisto.xtalk_shape.vcsel_width = 40;
        data->xtalkhisto.xtalk_shape.VL53LX_p_015 = 48414;

        // data->per_vcsel_cal_data.short_a_offset_mm = -16;
        // data->per_vcsel_cal_data.short_b_offset_mm = -15;
        // data->per_vcsel_cal_data.medium_a_offset_mm = -11;
        // data->per_vcsel_cal_data.medium_b_offset_mm = -15;
        // data->per_vcsel_cal_data.long_a_offset_mm = -10;
        // data->per_vcsel_cal_data.long_b_offset_mm = -11;

        data->customer.global_config__spad_enables_ref_0 = 255;
        data->customer.global_config__spad_enables_ref_1 = 255;
        data->customer.global_config__spad_enables_ref_2 = 255;
        data->customer.global_config__spad_enables_ref_3 = 255;
        data->customer.global_config__spad_enables_ref_4 = 253;
        data->customer.global_config__spad_enables_ref_5 = 5;
        data->customer.ref_spad_man__num_requested_ref_spads = 11;
        data->customer.ref_spad_man__ref_location = 2;
        data->customer.algo__crosstalk_compensation_plane_offset_kcps = 5957;
        data->customer.ref_spad_char__total_rate_target_mcps = 2560;
        data->customer.mm_config__inner_offset_mm = 17;
        data->customer.mm_config__outer_offset_mm = 17;
        break;

    case 4:
        for (uint8_t i = 0; i < 6; i++)
        {
            data->algo__xtalk_cpo_HistoMerge_kcps[i] = xtalk_kcps[index][i];
        }

        for (uint8_t i = 0; i < 12; i++)
        {
            data->xtalkhisto.xtalk_shape.bin_data[i] = xtalk_bin_data[index][i];
        }

        data->xtalkhisto.xtalk_shape.zero_distance_phase = 4219;
        data->xtalkhisto.xtalk_shape.phasecal_result__reference_phase = 10363;
        data->xtalkhisto.xtalk_shape.cal_config__vcsel_start = 9;
        data->xtalkhisto.xtalk_shape.zone_id = 0;
        data->xtalkhisto.xtalk_shape.vcsel_width = 40;
        data->xtalkhisto.xtalk_shape.VL53LX_p_015 = 48250;

        // data->per_vcsel_cal_data.short_a_offset_mm = -16;
        // data->per_vcsel_cal_data.short_b_offset_mm = -15;
        // data->per_vcsel_cal_data.medium_a_offset_mm = -11;
        // data->per_vcsel_cal_data.medium_b_offset_mm = -15;
        // data->per_vcsel_cal_data.long_a_offset_mm = -10;
        // data->per_vcsel_cal_data.long_b_offset_mm = -11;

        data->customer.global_config__spad_enables_ref_0 = 255;
        data->customer.global_config__spad_enables_ref_1 = 239;
        data->customer.global_config__spad_enables_ref_2 = 251;
        data->customer.global_config__spad_enables_ref_3 = 247;
        data->customer.global_config__spad_enables_ref_4 = 175;
        data->customer.global_config__spad_enables_ref_5 = 14;
        data->customer.ref_spad_man__num_requested_ref_spads = 10;
        data->customer.ref_spad_man__ref_location = 2;
        data->customer.algo__crosstalk_compensation_plane_offset_kcps = 6185;
        data->customer.ref_spad_char__total_rate_target_mcps = 2560;
        data->customer.mm_config__inner_offset_mm = 25;
        data->customer.mm_config__outer_offset_mm = 25;
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