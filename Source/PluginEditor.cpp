#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Metronome.h"


SamplerpluginAudioProcessorEditor::SamplerpluginAudioProcessorEditor (SamplerpluginAudioProcessor& p)
: AudioProcessorEditor (&p), triggerButtons(p), processor (p)

{
    addAndMakeVisible(triggerButtons);
    
    bpmSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 100, 100);
    bpmSlider.setRange(20, 999);
    bpmSlider.setValue(processor.apvts.getParameter("BPM")->getValue());
    addAndMakeVisible(bpmSlider);
    sliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.apvts, "BPM", bpmSlider);
    
    playButton.setToggleable(true);
    playButton.setRadioGroupId(1);
    playButton.onClick = [&]{p.play();};
    playButton.setToggleState(false, NotificationType::dontSendNotification);
    addAndMakeVisible(playButton);
    
    stopButton.setToggleable(true);
    stopButton.onClick = [&]{p.stop();};
    stopButton.setRadioGroupId(1);
    stopButton.setToggleState(true, NotificationType::dontSendNotification);
    addAndMakeVisible(stopButton);
    

    setSize (200, 200);
}

SamplerpluginAudioProcessorEditor::~SamplerpluginAudioProcessorEditor() {}

void SamplerpluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (Colour(40, 60, 40));
}

void SamplerpluginAudioProcessorEditor::resized()
{
    const int buttonWidth = 100;
    const int buttonHeight = 100;
    
    playButton.setBounds(
                         getWidth()/2-buttonWidth/2,
                         getHeight()/2-buttonHeight/2+200,
                         buttonWidth,
                         buttonHeight
                         );
    
    stopButton.setBounds(
                         getWidth()/2-buttonWidth/2+100,
                         getHeight()/2-buttonHeight/2+200,
                         buttonWidth,
                         buttonHeight
                         );

    bpmSlider.setBounds(0, 300, 300, 20);
    

    
    triggerButtons.setBounds(30, 30, getWidth()-60, 40);
}
