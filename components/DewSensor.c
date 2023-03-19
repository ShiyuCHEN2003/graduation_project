#include "DewSensor.h"

// ADC1-IN4  PA4

/**
 * @brief  结露传感器初始化（必须在ADC初始化之后）
 * @param  void
 * @retval void
 */
void DewSensor_Init(void)
{
    HAL_ADCEx_Calibration_Start(&hadc1); // ADC校准
    HAL_ADC_Start(&hadc1);
}

/**
 * @brief  结露传感器读取湿度信息
 * @param  float *humidity  相对湿度RH 93-100
 *         float *DewSensor_resister  结露传感器阻值 KΩ
 * @retval void
 */
void DewSensor_GetData(float *humidity, float *DewSensor_resister)
{
    static uint16_t ADC_Value;
    static float ADC1_voltage, Parallel_resister;

    HAL_ADC_PollForConversion(&hadc1, 50);

    ADC_Value = HAL_ADC_GetValue(&hadc1);

    ADC1_voltage = (float)ADC_Value / 4096 * 3.3; // 转化为0~3.3电压
    Parallel_resister = 300 * ADC1_voltage / (23 - ADC1_voltage);
    if (Parallel_resister == 50)
        *DewSensor_resister = 50;
    else
        *DewSensor_resister = 50 * Parallel_resister / (50 - Parallel_resister);
    *humidity = log(*DewSensor_resister / (2.133e-23)) / 0.5987;
}
