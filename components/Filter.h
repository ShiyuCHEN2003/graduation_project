#ifndef Filter_h
#define Filter_h

// 均值滤波
#define AVERAGE_LENGTH 30
typedef struct _AveFilter
{
    float buffer[AVERAGE_LENGTH]; // 缓存数组
    float sum;                    // 累加和
    int index;                    // 索引
} AveFilter;

void AverageFilterInit(AveFilter *Filter);
float AverageFilter(AveFilter *Filter, float in_data);

#endif
