/**
 ******************************************************************************
 * @file	SerialDebug.h
 * @author  Wang Hongxi Liu Zhijie
 * @version V2.0.0
 * @date    2022/2/10
 * @brief   UWP Serial debug assistant lib based on HAL
 ******************************************************************************
 * @attention
 * usart.h is generated by STM32CubeMX
 ******************************************************************************
 */
#ifndef _SERIAL_DEBUG_H
#define _SERIAL_DEBUG_H

#include "usart.h"
#include "stdint.h"
#include <stdarg.h>

#define DEBUG_BUFFER_LEN 200

void Serial_Debug_Init(UART_HandleTypeDef *huart);
void Serial_Debug(UART_HandleTypeDef *huart, uint16_t debug_period, float a, float b, float c, float d, float e, float f);
void Serial_Debug_Indeterminate_Length(uint8_t num, ...);
#endif
