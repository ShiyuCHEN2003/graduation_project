#ifndef AHT10_h
#define AHT10_h

//i2c1   PB7-SDA   PB6-SCL
#include "i2c.h"

//定义AHT10地址
#define AHT10_ADDRESS 0x70
#define AHT10_Write_ADDRESS 0x70
#define AHT10_Read_ADDRESS 0x71

//定义AHT10命令
#define AHT10_Init_com 0xE1
#define AHT10_SoftReset_com 0xBA
#define AHT10_TrigeMea_com 0xAC



void AHT10_Init(void);
void AHT10_TrigeMea(void);
uint8_t AHT10_Read_predata(float *humidity, float *temperature);

#endif
