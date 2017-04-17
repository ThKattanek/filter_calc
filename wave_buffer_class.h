#ifndef WAVEBUFFERCLASS_H
#define WAVEBUFFERCLASS_H


class WaveBufferClass
{
public:
    WaveBufferClass(unsigned int data_count);
    ~WaveBufferClass();

    void WriteData(unsigned int num, float value);
    float ReadData(unsigned int num);

    unsigned int GetBufferCount();
    float* GetDataPointer();

    float GetMax();
    float GetMin();

private:
    unsigned int data_count;
    float *data_buffer;
};

#endif // WAVEBUFFERCLASS_H
