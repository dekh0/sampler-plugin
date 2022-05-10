#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "TrigButtons.h"

class SamplerpluginAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    SamplerpluginAudioProcessorEditor (SamplerpluginAudioProcessor&);
    
    ~SamplerpluginAudioProcessorEditor() override;
    
    void paint (juce::Graphics&) override;
    
    void resized() override;
    
private:
    TrigButtons triggerButtons;
    
//    TriggerButtons triggerButtons;
    
    TextButton playButton { "play" };
    
    TextButton stopButton { "stop" };
    
    Slider bpmSlider;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sliderAttachment;
    
    SamplerpluginAudioProcessor& processor;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SamplerpluginAudioProcessorEditor)
};
