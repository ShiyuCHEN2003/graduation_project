#ifndef _FILTER_H_
#define _FILTER_H_

// 均值滤波
#define AVERAGE_LENGTH 100
typedef struct _AveFilter
{
    float buffer[AVERAGE_LENGTH]; // 缓存数组
    float sum;                    // 累加和
    int index;                    // 索引
} AveFilter;

void AverageFilterInit(AveFilter *Filter);
float AverageFilter(AveFilter *Filter, float in_data);

#endif
