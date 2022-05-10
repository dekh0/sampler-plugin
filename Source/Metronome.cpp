#include "Metronome.h"

void Metronome::init(AudioProcessorValueTreeState* apvt)
{
    apvts = apvt;
}

void Metronome::prepareToPlay(double sr)
{
    sampleRate = sr;
    interval = (60.0f / BPM * float(sampleRate))/8.0f;
}

int Metronome::countSamples(int bufferSize)
{
    auto bpm = apvts->getRawParameterValue("BPM");
    interval = (60.0f / float(bpm->load()) * float(sampleRate))/8.0f;
    totalSamples += bufferSize;

    samplesRemaining = totalSamples % interval;
    
    if(samplesRemaining + bufferSize >= interval)
    {
        return interval - samplesRemaining;
    }
    return -1;
}

void Metronome::reset()
{
    totalSamples = 0;
}

void Metronome::setBPM(float bpm)
{
    BPM = bpm;
}

float Metronome::getBPM(void)
{
    return BPM;
}
