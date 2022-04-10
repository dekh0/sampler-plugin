/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class SamplerpluginAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    SamplerpluginAudioProcessorEditor (SamplerpluginAudioProcessor&);
    ~SamplerpluginAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::TextButton mLoadButton { "Load" };
    SamplerpluginAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SamplerpluginAudioProcessorEditor)
};
