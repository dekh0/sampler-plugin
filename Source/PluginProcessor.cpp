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
    
    metronome.init(&apvts);
    
    for(int i = 0; i < mNumVoices; i++){
        sampler1.addVoice(new juce::SamplerVoice());
    }
    
}


void SamplerpluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    sampler1.setCurrentPlaybackSampleRate(sampleRate);
    
    metronome.prepareToPlay(sampleRate);
    
    BigInteger hatMidiRange;
    hatMidiRange.setRange(0, 127, true);
    WavAudioFormat wavFormat;
    std::unique_ptr<AudioFormatReader> sampReader(wavFormat.createReaderFor(new MemoryInputStream(BinaryData::click_wav, BinaryData::click_wavSize, false), true));
    sampler1.addSound(new SamplerSound("",
                                       *sampReader,
                                       hatMidiRange,
                                       80,  // midi note
                                       0.,  // attack time in seconds
                                       0.,  // release time in seconds
                                       3.));  // maximum sample length in seconds
}


void SamplerpluginAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    buffer.clear();
    
    if(playState==PlayState::Playing)
    {
        int sampleNumber = metronome.countSamples(buffer.getNumSamples());
        if(sampleNumber>0)
        {
            if(sequencer.tick())
            {
                std::array<bool, numOfButtons> trigValues;
                
                for(int i = 1; i<numOfButtons; i++)
                {
                    trigValues[i-1] = (apvts.getParameter(std::to_string(i))->getValue() == 1) ? true : false;
                }
                
                sequencer.setTriggers(trigValues);
                
                MidiMessage event = MidiMessage::noteOn(1, 30, uint8(126));
                midiMessages.addEvent(event, sampleNumber);
            }
        }
        
    }
    else
    {
        metronome.reset();
    }
    
    sampler1.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}


SamplerpluginAudioProcessor::~SamplerpluginAudioProcessor() {mFormatReader = nullptr;}


const juce::String SamplerpluginAudioProcessor::getName() const {return JucePlugin_Name;}


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


double SamplerpluginAudioProcessor::getTailLengthSeconds() const {return 0.0;}


int SamplerpluginAudioProcessor::getNumPrograms() {return 1;}


int SamplerpluginAudioProcessor::getCurrentProgram() {return 0;}


void SamplerpluginAudioProcessor::setCurrentProgram (int index){}


const juce::String SamplerpluginAudioProcessor::getProgramName (int index){return {};}


void SamplerpluginAudioProcessor::changeProgramName (int index, const juce::String& newName) {}


void SamplerpluginAudioProcessor::releaseResources() {}

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


bool SamplerpluginAudioProcessor::hasEditor() const {return true;}

juce::AudioProcessorEditor* SamplerpluginAudioProcessor::createEditor()
{
    return new SamplerpluginAudioProcessorEditor (*this);
}

void SamplerpluginAudioProcessor::getStateInformation (juce::MemoryBlock& destData){}

void SamplerpluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes){}

void SamplerpluginAudioProcessor::loadFile()
{
    
    //    std::unique_ptr<AudioFormatReader> reader;
    //    juce::FileChooser chooser { "Pleace load a file" };
    //    if(chooser.browseForFileToOpen())
    //    {
    //        BigInteger range;
    //        range.setRange(0, 128, true);
    //
    //        auto stream = chooser.getURLResult().createInputStream (URL::InputStreamOptions (URL::ParameterHandling::inAddress));
    //
    //        if (stream == nullptr)
    //        {
    //            jassert("NULL");
    //            return;
    //        }
    //
    //        auto reader = rawToUniquePtr (mFormatManager.createReaderFor (std::move (stream)));
    //
    //        if (reader == nullptr)
    //        {
    //            jassert("NULL");
    //            return;
    //        }
    //        mSampler.addSound (new SamplerSound ("", *reader, range, 64, 0.0, 0.0, 30.0));
    //    }
    
}

void SamplerpluginAudioProcessor::play(){playState = PlayState::Playing;}


void SamplerpluginAudioProcessor::stop(){playState = PlayState::Stopped;}


juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{return new SamplerpluginAudioProcessor();}

void SamplerpluginAudioProcessor::setBPM(float bpm){metronome.setBPM(bpm);}

float SamplerpluginAudioProcessor::getBPM(void){return metronome.getBPM();}

juce::AudioProcessorValueTreeState::ParameterLayout SamplerpluginAudioProcessor::createParameters()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
    
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
                                                                 "BPM",
                                                                 "bpm",
                                                                 0.0f,
                                                                 999.0f,
                                                                 120.0f));
    
    for(int i = 0; i < 32; i++)
        params.push_back(std::make_unique<juce::AudioParameterBool>
                         (std::to_string(i+1),
                          std::to_string(i+1),
                          false));
    
    
    params.push_back(std::make_unique<juce::AudioParameterBool>(
                                                                "PAD",
                                                                "Pad",
                                                                false));
    return {params.begin(), params.end()};
}



