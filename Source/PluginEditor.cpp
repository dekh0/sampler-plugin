#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Metronome.h"


SamplerpluginAudioProcessorEditor::SamplerpluginAudioProcessorEditor (SamplerpluginAudioProcessor& p)
: AudioProcessorEditor (&p), processor (p),
midiKeyboardComponent(p.midiKeyboardState, MidiKeyboardComponent::Orientation::horizontalKeyboard)

{
    mLoadButton.onClick = [&]{ processor.loadFile(); };
    addAndMakeVisible(mLoadButton);
    
    bpmSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 100, 100);
    bpmSlider.setRange(20, 999);
    bpmSlider.onValueChange = [&]{p.setBPM(bpmSlider.getValue());};
    bpmSlider.setValue(p.getBPM());
    addAndMakeVisible(bpmSlider);
 
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
    
    
    midiKeyboardComponent.setSize(100, 200);
    midiKeyboardComponent.setKeyWidth(40);
    midiKeyboardComponent.setLowestVisibleKey(30);
    midiKeyboardComponent.setBounds(getLocalBounds());
    midiKeyboardComponent.setColour(MidiKeyboardComponent::keyDownOverlayColourId, Colours::mediumturquoise);
    midiKeyboardComponent.setColour(MidiKeyboardComponent::mouseOverKeyOverlayColourId, Colours::whitesmoke);
    addAndMakeVisible(midiKeyboardComponent);
    
    setSize (500, 500);
}

SamplerpluginAudioProcessorEditor::~SamplerpluginAudioProcessorEditor()
{
}

void SamplerpluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void SamplerpluginAudioProcessorEditor::resized()
{
    const int buttonWidth = 100;
    const int buttonHeight = 100;
    
    mLoadButton.setBounds(getWidth()/2-buttonWidth/2, getHeight()/2-buttonHeight/2, buttonWidth, buttonHeight);
    
    playButton.setBounds(getWidth()/2-buttonWidth/2, getHeight()/2-buttonHeight/2+200, buttonWidth, buttonHeight);
    stopButton.setBounds(getWidth()/2-buttonWidth/2+100, getHeight()/2-buttonHeight/2+200, buttonWidth, buttonHeight);
    midiKeyboardComponent.setBounds(0, 0, getWidth(), 100);
    
    bpmSlider.setBounds(0, 300, 300, 20);
}
