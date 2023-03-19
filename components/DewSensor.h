#ifndef DewSensor_h
#define DewSensor_h

#include "adc.h"
#include "math.h"
void DewSensor_Init(void);
void DewSensor_GetData(float *humidity, float *DewSensor_resister);

#endif
