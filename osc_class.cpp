#include "osc_class.h"
#include <iostream>
#include <math.h>

float** OscClass::wave_tbl = NULL;
int OscClass::NumOscObjects = 0;

OscClass::OscClass(int samplerate)
{   
    SetSampleRate(samplerate);

    if(wave_tbl == NULL)
    {
        wave_tbl = new float*[NUM_WAVES];
        for(int i=0; i<NUM_WAVES; i++)
            wave_tbl[i] = new float[0x10000];
        FillWaveTbl();
    }
    NumOscObjects++;    

    Reset();
}

OscClass::~OscClass()
{
    NumOscObjects--;

    if(wave_tbl != NULL && NumOscObjects == 0)
    {
        for(int i=0; i<NUM_WAVES; i++)
        {
            delete[] wave_tbl[i];
            wave_tbl[i] = NULL;
        }
        delete[] wave_tbl;
        wave_tbl = NULL;
    }
}

void OscClass::Reset()
{
    frequenz = 50.0f;
    frequenz_offset = 0.0f;
    SetFrequenz(frequenz);

    current_waveform = WAVE_SQU;
    current_wave_tbl = wave_tbl[current_waveform];
}

float OscClass::GetNextSample()
{
    float sample = current_wave_tbl[(counter >> 16)&0xffff];
    counter += add_counter;
    return sample;
}

void OscClass::SetSampleRate(int samplerate)
{
    this->samplerate = samplerate;
    frequenz_faktor = 4294967296.0/samplerate;              // 2^32 / Samplerate
}

void OscClass::SetFrequenz(float frequenz)
{
    this->frequenz = frequenz;
    add_counter = (unsigned long)((frequenz+frequenz_offset) * frequenz_faktor);
}

void OscClass::SetFrequenzOffset(float frequenz_offset)
{
    this->frequenz_offset = frequenz_offset;
    add_counter = (unsigned long)((frequenz+frequenz_offset) * frequenz_faktor);
}

void OscClass::Sync()
{
    counter = 0;
}

void OscClass::FillWaveTbl()
{
    const float mul = 1.0 / (float)0x10000;

    for(int wave_type = 0; wave_type < NUM_WAVES ;wave_type++)
    {
        switch(wave_type)
        {
        case WAVE_SIN:
            for(int i=0;i<0x10000;i++)
            {
                wave_tbl[WAVE_SIN][i] = sin(2.0 * M_PI * i * mul);
            }
            break;
        case WAVE_SQU:
            for(int i=0;i<0x10000;i++)
            {
                if(i & 0x8000)
                    wave_tbl[WAVE_SQU][i] = 1.0;
                else wave_tbl[WAVE_SQU][i] = -1.0;
            }
            break;
        default:
            break;
        }
    }
}
