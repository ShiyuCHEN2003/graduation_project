#ifndef _WATERPUMP_H_
#define _WATERPUMP_H_

#include "tim.h"

void WaterPump_Init(void);
void WaterPump_Speed(uint16_t *duty);

#endif
