#include "TypeConversion.h"

// Float To Uint8 ������ʹ��round�����������룬ȡ������ŷ���char_array
void FloatToUint8(uint8_t *char_array, float *data,uint16_t size)
{
    uint16_t i;
    for (i = 0; i < size; i++)
    {
        char_array[i] = round(data[i]);
    }
}
