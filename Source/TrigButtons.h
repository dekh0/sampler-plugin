
#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

#define numOfButtons 32

class TrigButtons  : public juce::Component
{
public:
    TrigButtons(SamplerpluginAudioProcessor& p);
    ~TrigButtons() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> btnAttch;
    
    SamplerpluginAudioProcessor& processor;
    
    OwnedArray<ToggleButton> buttons;
    
    OwnedArray<std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment>> btnAttchmts;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TrigButtons)
};
