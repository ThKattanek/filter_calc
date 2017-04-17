#include "wave_buffer_class.h"

WaveBufferClass::WaveBufferClass(unsigned int data_count)
{
    this->data_count = data_count;
    data_buffer = new float[data_count];

    for(unsigned int i=0; i<data_count; i++)
        data_buffer[i] = 0.0;
}

WaveBufferClass::~WaveBufferClass()
{
    if(data_buffer != 0) delete[] data_buffer;
}

void WaveBufferClass::WriteData(unsigned int num, float value)
{
    if(num < data_count)
    {
        data_buffer[num] = value;
    }
}

float WaveBufferClass::ReadData(unsigned int num)
{
    if(num < data_count)
    {
        return data_buffer[num];
    }

    return 0;
}

unsigned int WaveBufferClass::GetBufferCount()
{
    return data_count;
}

float *WaveBufferClass::GetDataPointer()
{
    return data_buffer;
}

float WaveBufferClass::GetMax()
{
    float max = 0.0f;

    for(unsigned int i=0; i<data_count; i++)
        if(data_buffer[i] > max)
            max = data_buffer[i];

    return max;
}

float WaveBufferClass::GetMin()
{
    float min = 0.0f;

    for(unsigned int i=0; i<data_count; i++)
        if(data_buffer[i] < min)
            min = data_buffer[i];

    return min;
}
