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

void RefSpadCal(VL53L3CX_Object_t *dev);
void xTalkCal(VL53L3CX_Object_t *dev);
void offsetPerVcselCal(VL53L3CX_Object_t *dev, uint16_t distance);
VL53LX_CalibrationData_t getCalibrationData(VL53L3CX_Object_t *dev);
void setCalibrationData(VL53L3CX_Object_t *dev, uint8_t index, VL53LX_CalibrationData_t *data);
void setXTalkCompensation(VL53L3CX_Object_t *dev, bool state);
void setOffsetCorrectionMode(VL53L3CX_Object_t *dev, VL53LX_OffsetCorrectionModes state);
void convertCalibrationData(VL53LX_CalibrationData_t *data, int16_t *xtalk_bin_data, int16_t *xtalk_kcps, int16_t *xtalk_zero_distance, int16_t *offset);

void getCalibrate(VL53L3CX_Object_t *dev, uint8_t id)
{
    VL53LX_CalibrationData_t callData;

    printf("Calibrating sensor %2d in 20 seconds... \r\n\r\n", id);
    for (uint8_t i = 0; i < 20; i++)
    {
        HAL_GPIO_TogglePin(LED_0_GPIO_Port, LED_0_Pin);
        HAL_Delay(1000);
    }
    HAL_GPIO_WritePin(LED_0_GPIO_Port, LED_0_Pin, 0);

    // printf("Sensor %2d\r\n", center.gpioPin);
    printf("refspad\r\n");
    RefSpadCal(dev);
    // HAL_GPIO_WritePin(LED_4_GPIO_Port, LED_4_Pin, 1);
    printf("xtalk\r\n");
    xTalkCal(dev);
    // HAL_GPIO_WritePin(LED_3_GPIO_Port, LED_3_Pin, 1);
    printf("offset\r\n");
    offsetPerVcselCal(dev, 600);
    HAL_Delay(2);
    // HAL_GPIO_WritePin(LED_2_GPIO_Port, LED_2_Pin, 1);
    callData = getCalibrationData(dev);

    /* code */
    printf("sensor: %2d\r\n", id);
    printf("XTalk_kps\r\n");
    for (uint8_t j = 0; j < 6; j++)
    {
        printf(j);
        printf("%2d: %5d \r\n", j, callData.algo__xtalk_cpo_HistoMerge_kcps[j]);
    }
    printf("\r\n");
    printf("xtalk_bin_data\r\n");
    for (uint8_t j = 0; j < 12; j++)
    {
        printf(j);
        printf("%2d: %5d \r\n", j, callData.xtalkhisto.xtalk_shape.bin_data[j]);
    }
    printf("\r\n");
    printf("zero_distance_phase: %5d\r\n", callData.xtalkhisto.xtalk_shape.zero_distance_phase);
    printf("phasecal_result__reference_phase: %5d\r\n", callData.xtalkhisto.xtalk_shape.phasecal_result__reference_phase);
    printf("cal_config__vcsel_start: %5d\r\n", callData.xtalkhisto.xtalk_shape.cal_config__vcsel_start);
    printf("zone_id: %5d\r\n", callData.xtalkhisto.xtalk_shape.zone_id);
    printf("vcsel_width: %5d\r\n", callData.xtalkhisto.xtalk_shape.vcsel_width);
    printf("VL53LX_p_015: %5d\r\n", callData.xtalkhisto.xtalk_shape.VL53LX_p_015);
    printf("\r\n");
    printf("short_a_offset_mm: %5d\r\n", callData.per_vcsel_cal_data.short_a_offset_mm);
    printf("short_b_offset_mm: %5d\r\n", callData.per_vcsel_cal_data.short_b_offset_mm);
    printf("medium_a_offset_mm: %5d\r\n", callData.per_vcsel_cal_data.medium_a_offset_mm);
    printf("medium_b_offset_mm: %5d\r\n", callData.per_vcsel_cal_data.medium_b_offset_mm);
    printf("long_a_offset_mm: %5d\r\n", callData.per_vcsel_cal_data.long_a_offset_mm);
    printf("long_b_offset_mm: %5d\r\n", callData.per_vcsel_cal_data.long_b_offset_mm);
    printf("\r\n");
    printf("global_config__spad_enables_ref_0: %5d\r\n", callData.customer.global_config__spad_enables_ref_0);
    printf("global_config__spad_enables_ref_1: %5d\r\n", callData.customer.global_config__spad_enables_ref_1);
    printf("global_config__spad_enables_ref_2: %5d\r\n", callData.customer.global_config__spad_enables_ref_2);
    printf("global_config__spad_enables_ref_3: %5d\r\n", callData.customer.global_config__spad_enables_ref_3);
    printf("global_config__spad_enables_ref_4: %5d\r\n", callData.customer.global_config__spad_enables_ref_4);
    printf("global_config__spad_enables_ref_5: %5d\r\n", callData.customer.global_config__spad_enables_ref_5);
    printf("ref_spad_man__num_requested_ref_spads: %5d\r\n", callData.customer.ref_spad_man__num_requested_ref_spads);
    printf("ref_spad_man__ref_location: %5d\r\n", callData.customer.ref_spad_man__ref_location);
    printf("algo__crosstalk_compensation_plane_offset_kcps: %5d\r\n", callData.customer.algo__crosstalk_compensation_plane_offset_kcps);
    printf("ref_spad_char__total_rate_target_mcps: %5d\r\n", callData.customer.ref_spad_char__total_rate_target_mcps);
    printf("mm_config__inner_offset_mm: %5d\r\n", callData.customer.mm_config__inner_offset_mm);
    printf("mm_config__outer_offset_mm: %5d\r\n", callData.customer.mm_config__outer_offset_mm);

    setCalibrationData(dev, id, &callData);

    setOffsetCorrectionMode(dev, (VL53LX_OffsetCorrectionModes)VL53LX_OFFSETCORRECTIONMODE_PERVCSEL);
    setXTalkCompensation(dev, 1);
}

void setCalibrate(VL53L3CX_Object_t *dev, uint8_t id)
{
    VL53LX_CalibrationData_t callData;
    callData = getCalibrationData(dev);

    setCalibrationData(dev, id, &callData);

    setOffsetCorrectionMode(dev, (VL53LX_OffsetCorrectionModes)VL53LX_OFFSETCORRECTIONMODE_PERVCSEL);
    setXTalkCompensation(dev, 1);

    // Smudge detectie
    if (id == 1)
        VL53LX_SmudgeCorrectionEnable(dev, VL53LX_SMUDGE_CORRECTION_CONTINUOUS); // Deze sensor zal bij elke meeting de smudge toepassen
    else
        VL53LX_SmudgeCorrectionEnable(dev, VL53LX_SMUDGE_CORRECTION_SINGLE); // Deze sensor zal bij elke start de correctie toepassen
}

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
        {8673, 17283, 25893, 34503, 43113, 51724},
        {3045, 6060, 9075, 12090, 15105, 18122}};

    int xtalk_bin_data[amountSensorUsed][12] = {
        {9, 428, 470, 117, 0, 0, 0, 0, 0, 0, 0, 0},
        {15, 422, 471, 116, 0, 0, 0, 0, 0, 0, 0, 0},
        {16, 418, 481, 109, 0, 0, 0, 0, 0, 0, 0, 0}};

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

        data->xtalkhisto.xtalk_shape.zero_distance_phase = 4164;
        data->xtalkhisto.xtalk_shape.phasecal_result__reference_phase = 10308;
        data->xtalkhisto.xtalk_shape.cal_config__vcsel_start = 9;
        data->xtalkhisto.xtalk_shape.zone_id = 0;
        data->xtalkhisto.xtalk_shape.vcsel_width = 40;
        data->xtalkhisto.xtalk_shape.VL53LX_p_015 = 48250;

        data->per_vcsel_cal_data.short_a_offset_mm = -26;
        data->per_vcsel_cal_data.short_b_offset_mm = -20;
        data->per_vcsel_cal_data.medium_a_offset_mm = -16;
        data->per_vcsel_cal_data.medium_b_offset_mm = -22;
        data->per_vcsel_cal_data.long_a_offset_mm = -13;
        data->per_vcsel_cal_data.long_b_offset_mm = -16;

        data->customer.global_config__spad_enables_ref_0 = 255;
        data->customer.global_config__spad_enables_ref_1 = 239;
        data->customer.global_config__spad_enables_ref_2 = 251;
        data->customer.global_config__spad_enables_ref_3 = 247;
        data->customer.global_config__spad_enables_ref_4 = 175;
        data->customer.global_config__spad_enables_ref_5 = 14;
        data->customer.ref_spad_man__num_requested_ref_spads = 10;
        data->customer.ref_spad_man__ref_location = 2;
        data->customer.algo__crosstalk_compensation_plane_offset_kcps = 8673;
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

        data->xtalkhisto.xtalk_shape.zero_distance_phase = 4131;
        data->xtalkhisto.xtalk_shape.phasecal_result__reference_phase = 10275;
        data->xtalkhisto.xtalk_shape.cal_config__vcsel_start = 9;
        data->xtalkhisto.xtalk_shape.zone_id = 0;
        data->xtalkhisto.xtalk_shape.vcsel_width = 40;
        data->xtalkhisto.xtalk_shape.VL53LX_p_015 = 48373;

        data->per_vcsel_cal_data.short_a_offset_mm = -52;
        data->per_vcsel_cal_data.short_b_offset_mm = -48;
        data->per_vcsel_cal_data.medium_a_offset_mm = -47;
        data->per_vcsel_cal_data.medium_b_offset_mm = -54;
        data->per_vcsel_cal_data.long_a_offset_mm = -43;
        data->per_vcsel_cal_data.long_b_offset_mm = -42;

        data->customer.global_config__spad_enables_ref_0 = 255;
        data->customer.global_config__spad_enables_ref_1 = 255;
        data->customer.global_config__spad_enables_ref_2 = 254;
        data->customer.global_config__spad_enables_ref_3 = 192;
        data->customer.global_config__spad_enables_ref_4 = 183;
        data->customer.global_config__spad_enables_ref_5 = 15;
        data->customer.ref_spad_man__num_requested_ref_spads = 12;
        data->customer.ref_spad_man__ref_location = 2;
        data->customer.algo__crosstalk_compensation_plane_offset_kcps = 3045;
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