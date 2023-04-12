
#ifndef _FLOWSENSOR_H_
#define _FLOWSENSOR_H_
#include "tim.h"
// TIM3_CH1    PA6

typedef struct
{
    uint8_t flag;     // 0Ϊδ��ʼ��1Ϊ��ʼ��2Ϊ����
    uint32_t buf[3];  // ����ֵ
    uint16_t timeout; // �������
    float f;          // ÿ��Ƶ��
} CAPTUREC_t;

extern CAPTUREC_t capturecal;
void Flowsensor_Init(void);
float Flowsensor_YFs401(CAPTUREC_t *capturecal);
float Flowsensor_PS2216(CAPTUREC_t *capturecal);
#endif
