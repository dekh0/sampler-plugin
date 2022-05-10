#pragma once
#include <JuceHeader.h>

class Metronome
{
public:
    void init(AudioProcessorValueTreeState*);

    void prepareToPlay(double sampleRate);

    int countSamples(int bufferSize);

    void reset();
    
    float BPM;
    
    void setBPM(float bpm);
    
    float getBPM(void);
    
private:
    unsigned int totalSamples { 0 };

    double sampleRate;

    int interval { 0 };

    int samplesRemaining { 0 };

    AudioProcessorValueTreeState* apvts;
};
