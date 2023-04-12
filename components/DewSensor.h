#ifndef _DEWSENSOR_H_
#define _DEWSENSOR_H_

#include "adc.h"
#include "math.h"
void DewSensor_Init(void);
void DewSensor_GetData(float *humidity, float *DewSensor_resister);

#endif
