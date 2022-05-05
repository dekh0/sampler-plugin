#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

class SamplerpluginAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    SamplerpluginAudioProcessorEditor (SamplerpluginAudioProcessor&);
    ~SamplerpluginAudioProcessorEditor() override;

        void paint (juce::Graphics&) override;
    void resized() override;
    

private:
    TextButton playButton { "play" };
    TextButton stopButton { "stop" };
    Slider bpmSlider;
    
    juce::TextButton mLoadButton { "Load" };
    SamplerpluginAudioProcessor& processor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SamplerpluginAudioProcessorEditor)
    MidiKeyboardComponent midiKeyboardComponent;
};
