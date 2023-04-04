/**
 * @file WaterPump.c
 * @author ChenShiyu (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-11-14
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "WaterPump.h"
// TMI2_CH3   PA2   pwm_front
// TIM2_CH4   PA3   pwm_back
// ARR=500   f=2KHZ

/**
 * @brief  水泵初始化（输出为0）
 * @param  void
 * @retval void
 */
void WaterPump_Init(void)
{
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4);
    htim2.Instance->CCR3 = 250;
    htim2.Instance->CCR4 = 0;
}

/**
 * @brief  水泵调速(正转)
 * @param  uint8_t *duty   水泵占空比，变化范围0-100
 * @retval void
 */
void WaterPump_Speed(uint16_t *duty)
{
    static uint16_t pwm_front;
    uint16_t pwm_back = 0;
    pwm_front = (*duty) * 3 + 200; // duty 0-100 映射到 200-500（水泵最小电压及最大电压）
	  if(pwm_front<=200)
			pwm_front=0;
    htim2.Instance->CCR3 = pwm_front;
    htim2.Instance->CCR4 = pwm_back;
}
