
#ifndef _PID_H_
#define _PID_H_
#include "math.h"
#include "stdint.h"
#include "stddef.h"

typedef struct
{
    float Kp;
    float Ki;
    float Kd;

    float max_out;  // ������
    float max_dout; // ���������

    float Set;
    float feedback;

    float out;
    float pout;
    float iout;
    float dout;

    float error[3]; // 0��ǰʱ��1ǰһʱ��2ǰ��ʱ��
} Pid_T;

// extern Pid_T Pid;

void PidInit(Pid_T *pid, float Kp, float Ki, float Kd, float max_out, float max_iout); // �趨PID��������ʼֵ

float PidCalculate(Pid_T *pid, float set, float feedback); // ����PID�������ֵ

float IntergralSeparationPTD(Pid_T *pid, float set, float feedback, float region); // ���ַ���PID�������ֵ
#endif
