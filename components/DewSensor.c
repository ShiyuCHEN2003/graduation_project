#include "DewSensor.h"
#include "adc.h"

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
 * @param  float *humidity  相对湿度RH 0-100
 * @retval void
 */
void DewSensor_GetData(float *humidity)
{
    static uint16_t ADC_Value;
    static float ADC1_voltage, DewSensor_resister;

    HAL_ADC_PollForConversion(&hadc1, 50);

    ADC_Value = HAL_ADC_GetValue(&hadc1);

    ADC1_voltage = (float)ADC_Value / 4096 * 3.3; // 转化为0~3.3电压
    DewSensor_resister = 300 * ADC1_voltage / (8 - ADC1_voltage);
    *humidity = DewSensor_resister;
}
