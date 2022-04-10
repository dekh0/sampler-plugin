/*
 ==============================================================================
 
 This file contains the basic framework code for a JUCE plugin editor.
 
 ==============================================================================
 */

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SamplerpluginAudioProcessorEditor::SamplerpluginAudioProcessorEditor (SamplerpluginAudioProcessor& p)
: AudioProcessorEditor (&p), processor (p)
{
    mLoadButton.onClick = [&]{ processor.loadFile(); };
    addAndMakeVisible(mLoadButton);
    
    setSize (200, 200);
}

SamplerpluginAudioProcessorEditor::~SamplerpluginAudioProcessorEditor()
{
}

//==============================================================================
void SamplerpluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    
    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void SamplerpluginAudioProcessorEditor::resized()
{
    const int buttonWidth = 100;
    const int buttonHeight = 100;
    
    mLoadButton.setBounds(getWidth()/2-buttonWidth/2, getHeight()/2-buttonHeight/2, buttonWidth, buttonHeight);
}
