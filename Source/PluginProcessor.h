#pragma once

#include <JuceHeader.h>
#include "Metronome.h"

/**
*/
class SamplerpluginAudioProcessor  : public juce::AudioProcessor, MidiKeyboardState::Listener
{
public:
    
    SamplerpluginAudioProcessor();
    ~SamplerpluginAudioProcessor() override;

    
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    void play();
    
    void stop();
    
    enum class PlayState
    {
        Playing,
        Stopped
    };
    
    void loadFile();
    
    MidiKeyboardState midiKeyboardState;
    
    Synthesiser mSampler;
    
    void setBPM(float bpm);
    
    float getBPM(void);
    
private:
    
    float BPM {120.0};
    PlayState playState { PlayState::Stopped };
    
    Metronome metronome;
    
    void handleNoteOn(MidiKeyboardState* source, int midiChannel, int midiNoteNumber, float velocity) override
        {
//            ampEnvelope.noteOn();
//            lastMidiNoteNumber = midiNoteNumber;
//            lastMidiNoteHertz = MidiMessage::getMidiNoteInHertz(lastMidiNoteNumber);
//            mIsNotePlayed = true;
        }

        void handleNoteOff(MidiKeyboardState* source, int midiChannel, int midiNoteNumber, float velocity) override
        {
//            ampEnvelope.noteOff();
//            lastPlaybackPosition = 0;
//            mIsNotePlayed = false;
        }
    int count = 0;
    
    const int mNumVoices { 3 };
    AudioFormatManager mFormatManager;
    AudioFormatReader* mFormatReader { nullptr };
    //juce::MidiKeyboardState keyboardState;
    juce::MidiMessageCollector midiCollector;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SamplerpluginAudioProcessor)
};
