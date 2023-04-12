#ifndef _FUZZYPID_H_
#define _FUZZYPID_H_
#include "main.h"
#include "pid.h"
// e��ecģ������Ӧ�����򣬶���Ϊ{-6��-4��-2��0��2��4��6}
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

    float max_out; // ������
    float min_out; // ��С���

    float Set;
    float feedback;

    float out;
    float pout;
    float iout;
    float dout;

    float error[3]; // 0��ǰʱ��1ǰһʱ��2ǰ��ʱ��
    float errormax;
    float errormin;
    float derrormax;
    float derrormin;

    float maxdKp; /*Kp�����������ֵ*/
    float mindKp; /*Kp��������С��ֵ*/
    float dkp;

    float maxdKi; /*Ki�����������ֵ*/
    float mindKi; /*Ki��������С��ֵ*/
    float dki;

    float maxdKd; /*Kd�����������ֵ*/
    float mindKd; /*Kd��������С��ֵ*/
    float dkd;

} FUZZYPid_T;

#endif