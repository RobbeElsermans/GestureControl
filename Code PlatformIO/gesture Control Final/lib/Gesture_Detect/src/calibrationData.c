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

void refSpadCal(VL53L3CX_Object_t *dev);
void xTalkCal(VL53L3CX_Object_t *dev);
void offsetPerVcselCal(VL53L3CX_Object_t *dev, uint16_t distance);
VL53LX_CalibrationData_t getCalibrationData(VL53L3CX_Object_t *dev);
void setCalibrationData(sensorData_t* sensor, VL53LX_CalibrationData_t *data);
void setXTalkCompensation(VL53L3CX_Object_t *dev, bool state);
void setOffsetCorrectionMode(VL53L3CX_Object_t *dev, VL53LX_OffsetCorrectionModes state);
void convertCalibrationData(VL53LX_CalibrationData_t *data, int16_t *xtalk_bin_data, int16_t *xtalk_kcps, int16_t *xtalk_zero_distance, int16_t *offset);

void calibrationData_getCalibrate(sensorData_t* sensor){
VL53LX_CalibrationData_t callData;

    printf("Calibrating sensor %2d in 16 seconds... \r\n\r\n", sensor->id);
    for (uint8_t i = 0; i < 16; i++)
    {
        HAL_GPIO_TogglePin(LED_0_GPIO_Port, LED_0_Pin);
        HAL_Delay(1000);
    }
    HAL_GPIO_WritePin(LED_0_GPIO_Port, LED_0_Pin, 0);

    // printf("Sensor %2d\r\n", center.gpioPin);
    printf("refspad\r\n");
    refSpadCal(&sensor->sensor);
    // HAL_GPIO_WritePin(LED_4_GPIO_Port, LED_4_Pin, 1);
    printf("xtalk\r\n");
    xTalkCal(&sensor->sensor);
    // HAL_GPIO_WritePin(LED_3_GPIO_Port, LED_3_Pin, 1);
    printf("offset\r\n");
    //offsetPerVcselCal(&sensor->sensor, 600);
    HAL_Delay(2);
    // HAL_GPIO_WritePin(LED_2_GPIO_Port, LED_2_Pin, 1);
    callData = getCalibrationData(&sensor->sensor);

    /* code */
    printf("sensor: %2d\r\n", sensor->id);
    printf("XTalk_kps\r\n");
    for (uint8_t j = 0; j < 6; j++)
    {
        printf("%2d",j);
        printf("%2d: %5d \r\n", (int)j, (int)callData.algo__xtalk_cpo_HistoMerge_kcps[j]);
    }
    printf("\r\n");
    printf("xtalk_bin_data\r\n");
    for (uint8_t j = 0; j < 12; j++)
    {
        printf("%2d",j);
        printf("%2d: %5d \r\n", j, (int)callData.xtalkhisto.xtalk_shape.bin_data[j]);
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
    printf("algo__crosstalk_compensation_plane_offset_kcps: %5d\r\n", (int)callData.customer.algo__crosstalk_compensation_plane_offset_kcps);
    printf("ref_spad_char__total_rate_target_mcps: %5d\r\n", callData.customer.ref_spad_char__total_rate_target_mcps);
    printf("mm_config__inner_offset_mm: %5d\r\n", callData.customer.mm_config__inner_offset_mm);
    printf("mm_config__outer_offset_mm: %5d\r\n", callData.customer.mm_config__outer_offset_mm);

    setCalibrationData(sensor, &callData);

    setOffsetCorrectionMode(&sensor->sensor, (VL53LX_OffsetCorrectionModes)VL53LX_OFFSETCORRECTIONMODE_PERVCSEL);
    setXTalkCompensation(&sensor->sensor, 1);
}

void calibrationData_setCalibrate(sensorData_t* sensor){
 VL53LX_CalibrationData_t callData;
    callData = getCalibrationData(&sensor->sensor);

    setCalibrationData(sensor, &callData);

    setOffsetCorrectionMode(&sensor->sensor, (VL53LX_OffsetCorrectionModes)VL53LX_OFFSETCORRECTIONMODE_PERVCSEL);
    setXTalkCompensation(&sensor->sensor, 1);

    // Smudge detectie
    VL53LX_SmudgeCorrectionEnable(&sensor->sensor, VL53LX_SMUDGE_CORRECTION_CONTINUOUS); // Deze sensor zal bij elke meeting de smudge toepassen
    
}

void refSpadCal(VL53L3CX_Object_t *dev)
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
void setCalibrationData(sensorData_t* sensor, VL53LX_CalibrationData_t *data)
{
    int xtalk_kcps[AMOUNT_SENSOR_USED][6] = {
        {8341, 16492, 24643, 32794, 40945, 49100},
        {3311, 6634, 9957, 13280, 16603, 19927},
        {2714, 5551, 8388, 11225, 14062, 16903}};

    int xtalk_bin_data[AMOUNT_SENSOR_USED][12] = {
        {2, 407, 471, 144, 0, 0, 0, 0, 0, 0, 0, 0},
        {4, 350, 501, 169, 0, 0, 0, 0, 0, 0, 0, 0},
        {22, 419, 474, 109, 0, 0, 0, 0, 0, 0, 0, 0}};

    switch (sensor->id)
    {
    case 0:

        for (uint8_t i = 0; i < 6; i++)
        {
            data->algo__xtalk_cpo_HistoMerge_kcps[i] = xtalk_kcps[sensor->id][i];
        }

        for (uint8_t i = 0; i < 12; i++)
        {
            data->xtalkhisto.xtalk_shape.bin_data[i] = xtalk_bin_data[sensor->id][i];
        }

        data->xtalkhisto.xtalk_shape.zero_distance_phase = 4307;
        data->xtalkhisto.xtalk_shape.phasecal_result__reference_phase = 10451;
        data->xtalkhisto.xtalk_shape.cal_config__vcsel_start = 9;
        data->xtalkhisto.xtalk_shape.zone_id = 0;
        data->xtalkhisto.xtalk_shape.vcsel_width = 40;
        data->xtalkhisto.xtalk_shape.VL53LX_p_015 = 48373;

        data->per_vcsel_cal_data.short_a_offset_mm = 0;
        data->per_vcsel_cal_data.short_b_offset_mm = 0;
        data->per_vcsel_cal_data.medium_a_offset_mm = 0;
        data->per_vcsel_cal_data.medium_b_offset_mm = 0;
        data->per_vcsel_cal_data.long_a_offset_mm = 0;
        data->per_vcsel_cal_data.long_b_offset_mm = 0;

        data->customer.global_config__spad_enables_ref_0 = 223;
        data->customer.global_config__spad_enables_ref_1 = 231;
        data->customer.global_config__spad_enables_ref_2 = 255;
        data->customer.global_config__spad_enables_ref_3 = 255;
        data->customer.global_config__spad_enables_ref_4 = 247;
        data->customer.global_config__spad_enables_ref_5 = 15;
        data->customer.ref_spad_man__num_requested_ref_spads = 10;
        data->customer.ref_spad_man__ref_location = 2;
        data->customer.algo__crosstalk_compensation_plane_offset_kcps = 8341;
        data->customer.ref_spad_char__total_rate_target_mcps = 2560;
        data->customer.mm_config__inner_offset_mm = 24;
        data->customer.mm_config__outer_offset_mm = 24;

        break;
    case 1:

        for (uint8_t i = 0; i < 6; i++)
        {
            data->algo__xtalk_cpo_HistoMerge_kcps[i] = xtalk_kcps[sensor->id][i];
        }

        for (uint8_t i = 0; i < 12; i++)
        {
            data->xtalkhisto.xtalk_shape.bin_data[i] = xtalk_bin_data[sensor->id][i];
        }

        data->xtalkhisto.xtalk_shape.zero_distance_phase = 4426;
        data->xtalkhisto.xtalk_shape.phasecal_result__reference_phase = 10570;
        data->xtalkhisto.xtalk_shape.cal_config__vcsel_start = 9;
        data->xtalkhisto.xtalk_shape.zone_id = 0;
        data->xtalkhisto.xtalk_shape.vcsel_width = 40;
        data->xtalkhisto.xtalk_shape.VL53LX_p_015 = 48414;

        data->per_vcsel_cal_data.short_a_offset_mm = 0;
        data->per_vcsel_cal_data.short_b_offset_mm = 0;
        data->per_vcsel_cal_data.medium_a_offset_mm = 0;
        data->per_vcsel_cal_data.medium_b_offset_mm = 0;
        data->per_vcsel_cal_data.long_a_offset_mm = 0;
        data->per_vcsel_cal_data.long_b_offset_mm = 0;

        data->customer.global_config__spad_enables_ref_0 = 255;
        data->customer.global_config__spad_enables_ref_1 = 255;
        data->customer.global_config__spad_enables_ref_2 = 255;
        data->customer.global_config__spad_enables_ref_3 = 255;
        data->customer.global_config__spad_enables_ref_4 = 255;
        data->customer.global_config__spad_enables_ref_5 = 5;
        data->customer.ref_spad_man__num_requested_ref_spads = 11;
        data->customer.ref_spad_man__ref_location = 2;
        data->customer.algo__crosstalk_compensation_plane_offset_kcps = 3311;
        data->customer.ref_spad_char__total_rate_target_mcps = 2560;
        data->customer.mm_config__inner_offset_mm = 17;
        data->customer.mm_config__outer_offset_mm = 17;
        break;
    case 2:
        for (uint8_t i = 0; i < 6; i++)
        {
            data->algo__xtalk_cpo_HistoMerge_kcps[i] = xtalk_kcps[sensor->id][i];
        }

        for (uint8_t i = 0; i < 12; i++)
        {
            data->xtalkhisto.xtalk_shape.bin_data[i] = xtalk_bin_data[sensor->id][i];
        }

        data->xtalkhisto.xtalk_shape.zero_distance_phase = 4127;
        data->xtalkhisto.xtalk_shape.phasecal_result__reference_phase = 10271;
        data->xtalkhisto.xtalk_shape.cal_config__vcsel_start = 9;
        data->xtalkhisto.xtalk_shape.zone_id = 0;
        data->xtalkhisto.xtalk_shape.vcsel_width = 40;
        data->xtalkhisto.xtalk_shape.VL53LX_p_015 = 48373;

        data->per_vcsel_cal_data.short_a_offset_mm = 0;
        data->per_vcsel_cal_data.short_b_offset_mm = 0;
        data->per_vcsel_cal_data.medium_a_offset_mm = 0;
        data->per_vcsel_cal_data.medium_b_offset_mm = 0;
        data->per_vcsel_cal_data.long_a_offset_mm = 0;
        data->per_vcsel_cal_data.long_b_offset_mm = 0;

        data->customer.global_config__spad_enables_ref_0 = 255;
        data->customer.global_config__spad_enables_ref_1 = 255;
        data->customer.global_config__spad_enables_ref_2 = 254;
        data->customer.global_config__spad_enables_ref_3 = 182;
        data->customer.global_config__spad_enables_ref_4 = 183;
        data->customer.global_config__spad_enables_ref_5 = 15;
        data->customer.ref_spad_man__num_requested_ref_spads = 12;
        data->customer.ref_spad_man__ref_location = 2;
        data->customer.algo__crosstalk_compensation_plane_offset_kcps = 2714;
        data->customer.ref_spad_char__total_rate_target_mcps = 2560;
        data->customer.mm_config__inner_offset_mm = 18;
        data->customer.mm_config__outer_offset_mm = 18;
        break;
    default:
        break;
    }

    VL53LX_SetCalibrationData(&sensor->sensor, data);
}

void setXTalkCompensation(VL53L3CX_Object_t *dev, bool state)
{
    VL53LX_SetXTalkCompensationEnable(dev, state);
}
void setOffsetCorrectionMode(VL53L3CX_Object_t *dev, VL53LX_OffsetCorrectionModes state)
{
    VL53LX_SetOffsetCorrectionMode(dev, state);
}