#include "FlowSensor.h"

CAPTUREC_t capturecal[2];

// 定时器TIM4    捕获中断TIM3
// 小流量计FM-PS2216  TIM3_CH1     大流量计YF-s401  TIM3_CH2
/**
 * @brief  初始化
 * @param
 * @retval
 */
void Flowsensor_Init(CAPTUREC_t *capturecal)
{
    // 开启定时器溢出中断
    HAL_TIM_Base_Start_IT(&htim3);
    HAL_TIM_Base_Start_IT(&htim4);

    // 开启输入捕获中断，设置下降沿触发中断
    __HAL_TIM_SET_CAPTUREPOLARITY(&htim3, TIM_CHANNEL_2, TIM_INPUTCHANNELPOLARITY_FALLING);
    // 启动输入捕获
    HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_2);
    capturecal->number = 0;
}

/**
 * @brief  YF-s401流量计
 * @param  CAPTURE_t *capturecal
 * @retval float 流量参数0.3-6L/min
 */
float Flowsensor_YFs401(CAPTUREC_t *capturecal)
{
    return (capturecal->f + 3) / 5.5 / 60;
}

/**
 * @brief  FM-PS2216流量计
 * @param  CAPTURE_t *capturecal
 * @retval float 流量参数0.04-0.15L/min
 */
float Flowsensor_PS2216(CAPTUREC_t *capturecal)
{
    return (capturecal->f + 330.9) / 72.603;
}
