#include "DewSensor.h"

// ADC1-IN4  PA4

/**
 * @brief  ��¶��������ʼ����������ADC��ʼ��֮��
 * @param  void
 * @retval void
 */
void DewSensor_Init(void)
{
    HAL_ADCEx_Calibration_Start(&hadc1); // ADCУ׼
    HAL_ADC_Start(&hadc1);
}

/**
 * @brief  ��¶��������ȡʪ����Ϣ
 * @param  float *humidity  ���ʪ��RH 93-100
 *         float *DewSensor_resister  ��¶��������ֵ K��
 * @retval void
 */
void DewSensor_GetData(float *humidity, float *DewSensor_resister)
{
    static uint16_t ADC_Value;
    static float ADC1_voltage, Parallel_resister;

    HAL_ADC_PollForConversion(&hadc1, 50);

    ADC_Value = HAL_ADC_GetValue(&hadc1);

    ADC1_voltage = (float)ADC_Value / 4096 * 3.3; // ת��Ϊ0~3.3��ѹ
    Parallel_resister = 300 * ADC1_voltage / (23 - ADC1_voltage);
    if (Parallel_resister == 50)
        *DewSensor_resister = 50;
    else
        *DewSensor_resister = 50 * Parallel_resister / (50 - Parallel_resister);
    *humidity = log(*DewSensor_resister / (2.133e-23)) / 0.5987;
}
