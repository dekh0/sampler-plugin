#include "Metronome.h"

void Metronome::prepareToPlay(double sr, float BPM)
{
    sampleRate = sr;
    interval = (60.0f / BPM * float(sampleRate))/8.0f;
//    HighResolutionTimer::startTimer(interval);
}

void Metronome::hiResTimerCallback()
{
    
}

int Metronome::countSamples(int bufferSize)
{
    totalSamples += bufferSize;

    samplesRemaining = totalSamples % interval;
    
    if(samplesRemaining + bufferSize > interval)
    {
        return interval - samplesRemaining;
    }
    return -1;
}

void Metronome::reset()
{
    totalSamples = 0;
}

