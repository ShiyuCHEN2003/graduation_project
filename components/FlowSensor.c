#include "FlowSensor.h"

CAPTUREC_t capturecal[2];

// ��ʱ��TIM4    �����ж�TIM3
// С������FM-PS2216  TIM3_CH1     ��������YF-s401  TIM3_CH2
/**
 * @brief  ��ʼ��
 * @param
 * @retval
 */
void Flowsensor_Init(CAPTUREC_t *capturecal)
{
    // ������ʱ������ж�
    HAL_TIM_Base_Start_IT(&htim3);
    HAL_TIM_Base_Start_IT(&htim4);

    // �������벶���жϣ������½��ش����ж�
    __HAL_TIM_SET_CAPTUREPOLARITY(&htim3, TIM_CHANNEL_2, TIM_INPUTCHANNELPOLARITY_FALLING);
    // �������벶��
    HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_2);
    capturecal->number = 0;
}

/**
 * @brief  YF-s401������
 * @param  CAPTURE_t *capturecal
 * @retval float ��������0.3-6L/min
 */
float Flowsensor_YFs401(CAPTUREC_t *capturecal)
{
    return (capturecal->f + 3) / 5.5 / 60;
}

/**
 * @brief  FM-PS2216������
 * @param  CAPTURE_t *capturecal
 * @retval float ��������0.04-0.15L/min
 */
float Flowsensor_PS2216(CAPTUREC_t *capturecal)
{
    return (capturecal->f + 330.9) / 72.603;
}
