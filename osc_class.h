#ifndef OSCCLASS_H
#define OSCCLASS_H

enum {WAVE_SIN,WAVE_SQU,NUM_WAVES};

class OscClass
{
public:
    OscClass(int samplerate);
    ~OscClass();

    void Reset();
    float GetNextSample();
    void SetSampleRate(int samplerate);
    void SetFrequenz(float frequenz);
    void SetFrequenzOffset(float frequenz_offset);
    void Sync();

private:
    void FillWaveTbl();
    static float **wave_tbl;        // Globale WaveTable für alle Objekte von OscClass
    static int NumOscObjects;       // Aktuelle Anzahl von OscClass Objekten

    int samplerate;
    float frequenz_faktor;
    float frequenz;
    float frequenz_offset;

    int current_waveform;
    float *current_wave_tbl;

    unsigned long counter;
    unsigned long add_counter;
};

#endif // OSCCLASS_H
