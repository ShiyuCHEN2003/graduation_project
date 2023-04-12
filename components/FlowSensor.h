
#ifndef _FLOWSENSOR_H_
#define _FLOWSENSOR_H_
#include "tim.h"
// TIM3_CH1    PA6

typedef struct
{
    uint8_t flag;     // 0为未开始，1为开始，2为结束
    uint32_t buf[3];  // 计数值
    uint16_t timeout; // 溢出次数
    float f;          // 每秒频率
} CAPTUREC_t;

extern CAPTUREC_t capturecal;
void Flowsensor_Init(void);
float Flowsensor_YFs401(CAPTUREC_t *capturecal);
float Flowsensor_PS2216(CAPTUREC_t *capturecal);
#endif
