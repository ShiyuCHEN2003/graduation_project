#ifndef _FILTER_H_
#define _FILTER_H_

// ��ֵ�˲�
#define AVERAGE_LENGTH 30
typedef struct _AveFilter
{
    float buffer[AVERAGE_LENGTH]; // ��������
    float sum;                    // �ۼӺ�
    int index;                    // ����
} AveFilter;

void AverageFilterInit(AveFilter *Filter);
float AverageFilter(AveFilter *Filter, float in_data);

#endif
