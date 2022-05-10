#include <JuceHeader.h>
#include "TrigButtons.h"


TrigButtons::TrigButtons (SamplerpluginAudioProcessor& p)  : processor(p)
{
    for(int i=0; i < numOfButtons; i++)
    {
        auto newButton = new ToggleButton {  };
        buttons.add(newButton);
        addAndMakeVisible(buttons[i]);
        
        auto newAttch = new std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment>
        {
            std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment> (p.getApvts(), juce::String(std::to_string(i+1)), *buttons[i])
        };
        
        btnAttchmts.add(newAttch);
    }
}

TrigButtons::~TrigButtons(){}

void TrigButtons::paint (juce::Graphics& g){}

void TrigButtons::resized()
{
    int width = getWidth();
    int height = getHeight();
    for(int i=0; i<numOfButtons; i++)
    {
        buttons[i]->setBounds(i*width/numOfButtons, 0, width/numOfButtons, height);
    }
}

