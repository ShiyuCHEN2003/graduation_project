
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

    float max_out;  // 最大输出
    float max_dout; // 最大积分输出

    float Set;
    float feedback;

    float out;
    float pout;
    float iout;
    float dout;

    float error[3]; // 0当前时刻1前一时刻2前二时刻
} Pid_T;

// extern Pid_T Pid;

void PidInit(Pid_T *pid, float Kp, float Ki, float Kd, float max_out, float max_iout); // 设定PID控制器初始值

float PidCalculate(Pid_T *pid, float set, float feedback); // 经典PID计算输出值

float IntergralSeparationPTD(Pid_T *pid, float set, float feedback, float region); // 积分分离PID计算输出值
#endif
