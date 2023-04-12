#ifndef _FUZZYPID_H_
#define _FUZZYPID_H_
#include "main.h"
#include "pid.h"
// e和ec模糊集对应的论域，定义为{-6，-4，-2，0，2，4，6}
#define NB -6
#define NM -4
#define NS -2
#define ZO 0
#define PS 2
#define PM 4
#define PB 6
typedef struct
{
    float Kp;
    float Ki;
    float Kd;

    float max_out; // 最大输出
    float min_out; // 最小输出

    float Set;
    float feedback;

    float out;
    float pout;
    float iout;
    float dout;

    float error[3]; // 0当前时刻1前一时刻2前二时刻
    float errormax;
    float errormin;
    float derrormax;
    float derrormin;

    float maxdKp; /*Kp增量的最大限值*/
    float mindKp; /*Kp增量的最小限值*/
    float dkp;

    float maxdKi; /*Ki增量的最大限值*/
    float mindKi; /*Ki增量的最小限值*/
    float dki;

    float maxdKd; /*Kd增量的最大限值*/
    float mindKd; /*Kd增量的最小限值*/
    float dkd;

} FUZZYPid_T;

#endif