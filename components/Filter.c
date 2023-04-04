#include "Filter.h"
/**
 * @brief  ��ֵ�˲���ʼ��
 * @param  AveFilter *Filter
 * @retval void
 */
void AverageFilterInit(AveFilter *Filter)
{
    Filter->index = -1;
    Filter->sum = 0;
}

/**
 * @brief  ��ֵ�˲�
 * @param  AveFilter *Filter
 *         float in_data  �����²�������
 * @retval float  �����˲��������
 */
float AverageFilter(AveFilter *Filter, float in_data)
{
    if (Filter->index == -1)
    {
        for (int i = 0; i < AVERAGE_LENGTH; i++)
        {
            Filter->buffer[i] = in_data;
            Filter->sum += Filter->buffer[i];
        }
        Filter->index = 0;
    }
    else
    {
        Filter->sum -= Filter->buffer[Filter->index];
        Filter->sum += in_data;
        Filter->buffer[Filter->index] = in_data;
        Filter->index++;
        if (Filter->index >= AVERAGE_LENGTH)
            Filter->index = 0;
    }
    return Filter->sum / AVERAGE_LENGTH;
}
