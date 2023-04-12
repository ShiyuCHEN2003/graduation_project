#include "FuzzyPid.h"
// Kp模糊控制规则表
int ruleKp[7][7] =
    {
        PB, PB, PM, PM, PS, ZO, ZO;
PB, PB, PM, PS, PS, ZO, NS;
PM, PM, PM, PS, ZO, NS, NS;
PM, PM, PS, ZO, NS, NM, NM;
PS, PS, ZO, NS, NS, NM, NM;
PS, ZO, NS, NM, NM, NM, NB;
ZO, ZO, NM, NM, NM, NB, NB;
}
;
int ruleKi[7][7] =
    {
        NB, NB, NM, NM, NS, ZO, ZO;
NB, NB, NM, NS, NS, ZO, ZO;
NB, NM, NS, NS, ZO, PS, PS;
NM, NM, NS, ZO, PS, PM, PM;
NM, NS, ZO, PS, PS, PM, PB;
ZO, ZO, PS, PS, PM, PB, PB;
ZO, ZO, PS, PM, PM, PB, PB;
}
;
int ruleKd[7][7] = {0};
void FuzzyPid_Init(FUZZYPid_T *FPID, float Kp, float Ki, float Kd, float max_out, float min_out)
{
    if (FPID == NULL)
    {
        return;
    }
    FPID->Kp = Kp;
    FPID->Ki = Ki;
    FPID->Kd = Kd;
    FPID->max_out = max_out;
    FPID->max_dout = max_dout;
    FPID->error[0] = FPID->error[1] = FPID->error[2] = FPID->pout = FPID->iout = FPID->dout = FPID->out = 0.0f;
}

// 线性量化
void LinearQuantization(FUZZYPid_T *FPID, float *qvalue)
{
    float error;
    float derror;

    error = FPID->error[0];
    derror = FPID->error[0] - FPID->error[1];

    qvalue[0] = 6 * error / (FPID->errormax - FPID->errormin);
    qvalue[1] = 6 * derror / (FPID->derrormax - FPID->derrormin);
}

/**
 * @brief  计算隶属度函数
 * @param  float *qvalue 线性量化之后的值
 *         int *index  索引值
 *         float *membership  隶属度
 * @retval void
 */
void CalMembership(float *qvalue, int *index, float *membership)
{
    if ((qvalue >= NB) && (qvalue < NM))
    {
        index[0] = 0;
        index[1] = 1;
        membership[0] = -0.5 * qvalue - 2.0;
        membership[1] = 0.5 * qvalue + 3.0;
    }
    if ((qvalue >= NM) && (qvalue < NS))
    {
        index[0] = 1;
        index[1] = 2;
        membership[0] = -0.5 * qvalue - 1.0;
        membership[1] = 0.5 * qvalue + 2.0;
    }
    if ((qvalue >= NS) && (qvalue < ZO))
    {
        index[0] = 2;
        index[1] = 3;
        membership[0] = -0.5 * qvalue;
        membership[1] = 0.5 * qvalue + 1.0;
    }
    if ((qvalue >= ZO) && (qvalue < PS))
    {
        index[0] = 3;
        index[1] = 4;
        membership[0] = -0.5 * qvalue + 1.0;
        membership[1] = 0.5 * qvalue;
    }
    if ((qvalue >= PS) && (qvalue < PM))
    {
        index[0] = 4;
        index[1] = 5;
        membership[0] = -0.5 * qvalue + 2.0;
        membership[1] = 0.5 * qvalue - 1.0;
    }
    if ((qvalue >= PM) && (qvalue < PB))
    {
        index[0] = 5;
        index[1] = 6;
        membership[0] = -0.5 * qvalue + 3.0;
        membership[1] = 0.5 * qvalue - 2.0;
    }
}

void LinearRealization(FUZZYPid_T *FPID, float qKp, float qKi, float qKd)
{
    FPID->dKp = qKp * (FPID->maxdKp - FPID->mindKp) / 6;
    FPID->dKi = qKi * (FPID->maxdKi - FPID->mindKi) / 6;
    FPID->dKd = qKd * (FPID->maxdKd - FPID->mindKd) / 6;
}

/**
 * @brief  模糊控制计算
 * @param  FUZZYPid_T *FPID
 *         float *qvalue 线性量化之后的值
 *         float *index  索引值
 *         float *membership  隶属度
 * @retval void
 */
void FuzzyCompute(FUZZYPid_T *FPID, float set, float feedback)
{
    int Eindex[2] = {0, 0};
    int dEindex[2] = {0, 0};
    float Emembership[2] = {0, 0};
    float dEmembership[2] = {0, 0};
    float qKp, qKi, qKd = 0; // 线性量化模糊值
    float qvalue[2] = {0};   // 线性量化E EC

    FPID->error[2] = FPID->error[1];
    FPID->error[1] = FPID->error[0];
    FPID->Set = set;
    FPID->feedback = feedback;
    FPID->error[0] = FPID->Set - FPID->feedback;

    LinearQuantization(FPID, qvalue);

    CalMembership(qvalue[0], Eindex, Emembership);
    CalMembership(qvalue[1], dEindex, dEmembership);

    qKp = Emembership[0] * (dEmembership[0] * ruleKp[indexE[0]][indexEC[0]] + dEmembership[1] * ruleKp[indexE[0]][indexEC[1]]) + Emembership[1] * (dEmembership[0] * ruleKp[indexE[1]][indexEC[0]] + dEmembership[1] * ruleKp[indexE[1]][indexEC[1]]);
    qKi = Emembership[0] * (dEmembership[0] * ruleKi[indexE[0]][indexEC[0]] + dEmembership[1] * ruleKi[indexE[0]][indexEC[1]]) + Emembership[1] * (dEmembership[0] * ruleKi[indexE[1]][indexEC[0]] + dEmembership[1] * ruleKi[indexE[1]][indexEC[1]]);
    qKd = Emembership[0] * (dEmembership[0] * ruleKd[indexE[0]][indexEC[0]] + dEmembership[1] * ruleKd[indexE[0]][indexEC[1]]) + Emembership[1] * (dEmembership[0] * ruleKd[indexE[1]][indexEC[0]] + dEmembership[1] * ruleKd[indexE[1]][indexEC[1]]);

    LinearRealization(FPID, qKd, qKi, qKp);

    FPID->Kp += FPID->dkp;
    FPID->Ki += FPID->dki;
    FPID->Kd += FPID->dkd;

    FPID->pout = FPID->Kp * FPID->error[0];
    FPID->dout = FPID->Kd * (FPID->error[0] - FPID->error[1]);
    FPID->out = FPID->pout + FPID->iout + FPID->dout;
    LimitMax(pid->out, pid->max_out);
}