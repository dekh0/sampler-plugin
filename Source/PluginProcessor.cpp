
#include "PluginProcessor.h"
#include "PluginEditor.h"

SamplerpluginAudioProcessor::SamplerpluginAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
: AudioProcessor (BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
                  .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
#endif
                  .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
#endif
                  )
#endif
{
    mFormatManager.registerBasicFormats();
    
    for(int i = 0; i < mNumVoices; i++){
        mSampler.addVoice(new juce::SamplerVoice());
    }
}

void SamplerpluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)

{
    mSampler.setCurrentPlaybackSampleRate(sampleRate);
    
    midiCollector.reset(sampleRate);
    
    midiKeyboardState.reset();
    midiKeyboardState.addListener(this);
    
    metronome.prepareToPlay(sampleRate, BPM);
}

void SamplerpluginAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    
    
    if(playState==PlayState::Playing)
    {
        int sampleNumber = metronome.countSamples(buffer.getNumSamples());
        if(sampleNumber>0)
        {
            MidiMessage event = MidiMessage::noteOn(1, 70, uint8(70));
            midiMessages.addEvent(event, sampleNumber);
        }
        
    }
    else
    {
        metronome.reset();
    }
    
//    auto totalNumInputChannels  = getTotalNumInputChannels();
//    auto totalNumOutputChannels = getTotalNumOutputChannels();
    
    //midiCollector.removeNextBlockOfMessages (midiMessages, buffer.getNumSamples());
    
    midiKeyboardState.processNextMidiBuffer (midiMessages, 0 ,
                                             buffer.getNumSamples(), true);
    
    
    //    MidiBuffer processedBuffer;
    //
    //    for (const auto meta : midiMessages) {
    //     }
    //    MidiMessage msg;
    //    if(count % 1 == 0)
    //    {
    //        msg = MidiMessage::noteOn(1, 50, uint8(70));
    //        processedBuffer.addEvent(msg, 0);
    //        msg = MidiMessage::noteOff(1, 50, uint8(70));
    //        processedBuffer.addEvent(msg, buffer.getNumSamples());
    //    }
    //    count++;
    //
    //           processedBuffer.addEv
    //
    //    midiMessages.swapWith(processedBuffer);
    
//    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
//        buffer.clear (i, 0, buffer.getNumSamples());
    
    mSampler.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
    
}

SamplerpluginAudioProcessor::~SamplerpluginAudioProcessor()
{
    mFormatReader = nullptr;
}

const juce::String SamplerpluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SamplerpluginAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool SamplerpluginAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool SamplerpluginAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

double SamplerpluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SamplerpluginAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
    // so this should be at least 1, even if you're not really implementing programs.
}

int SamplerpluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SamplerpluginAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String SamplerpluginAudioProcessor::getProgramName (int index)
{
    return {};
}

void SamplerpluginAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

void SamplerpluginAudioProcessor::releaseResources()
{
    
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SamplerpluginAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
#else
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
        && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;
#if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
#endif
    return true;
#endif
}
#endif


bool SamplerpluginAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* SamplerpluginAudioProcessor::createEditor()
{
    return new SamplerpluginAudioProcessorEditor (*this);
}

void SamplerpluginAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{

}

void SamplerpluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    
}

void SamplerpluginAudioProcessor::loadFile()
{
    std::unique_ptr<AudioFormatReader> reader;
    juce::FileChooser chooser { "Pleace load a file" };
    if(chooser.browseForFileToOpen())
    {
        BigInteger range;
        range.setRange(0, 128, true);
        
        auto stream = chooser.getURLResult().createInputStream (URL::InputStreamOptions (URL::ParameterHandling::inAddress));
        
        if (stream == nullptr)
        {
            jassert("NULL");
            return;
        }
        
        auto reader = rawToUniquePtr (mFormatManager.createReaderFor (std::move (stream)));
        
        if (reader == nullptr)
        {
            jassert("NULL");
            return;
        }
        mSampler.addSound (new SamplerSound ("", *reader, range, 64, 0.0, 0.0, 30.0));
    }
}

void SamplerpluginAudioProcessor::play(){
    playState = PlayState::Playing;
}


void SamplerpluginAudioProcessor::stop(){
    playState = PlayState::Stopped;
}

// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SamplerpluginAudioProcessor();
}

void SamplerpluginAudioProcessor::setBPM(float bpm)
{
    metronome.prepareToPlay(getSampleRate(), bpm);
}

float SamplerpluginAudioProcessor::getBPM(void)
{
    return BPM;
}


