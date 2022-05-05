#pragma once
#include <JuceHeader.h>

class Metronome: public HighResolutionTimer
{
public:
    void prepareToPlay(double sampleRate, float BPM);
    int countSamples(int bufferSize);
    void reset();
    
    void hiResTimerCallback() override;
//    float BPM { 960.0 };
    
private:
    unsigned int totalSamples { 0 };
    double sampleRate;
    int interval { 0 };
    int samplesRemaining { 0 };
};
