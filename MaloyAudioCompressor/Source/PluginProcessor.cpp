/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MaloyAudioCompressorAudioProcessor::MaloyAudioCompressorAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), apvts(*this, nullptr, "PROCESSOR", createAPVTSParameterLayout())
#endif
{
}
// Parameter layout
juce::AudioProcessorValueTreeState::ParameterLayout MaloyAudioCompressorAudioProcessor::createAPVTSParameterLayout()
{
//    // setout plugin
//    float input_level = 1.0f;
//    float input_gain = 1.0f;
//    float threshold = 0.2;
//    float ratio = 5.0f;
//    float knee = 0.1;
    
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
    const int versionHint = 1;
    
    // Floats
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"INPUT LEVEL", versionHint}, "Input Level", 0.0f, 2.0f, 1.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"INPUT GAIN", versionHint}, "Input Gain", 0.0f, 3.0f, 0.0f));
    
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"THRESHOLD", versionHint}, "Threshold", 0.0f, 1.0f, 0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"RATIO", versionHint}, "Ratio", 0.0f, 10.0f, 1.0f));
    
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"KNEE", versionHint}, "Knee", 0.0f, 1.0f, 0.1f));
    
    return {params.begin(), params.end()};
}

MaloyAudioCompressorAudioProcessor::~MaloyAudioCompressorAudioProcessor()
{
}

//==============================================================================
const juce::String MaloyAudioCompressorAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool MaloyAudioCompressorAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool MaloyAudioCompressorAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool MaloyAudioCompressorAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double MaloyAudioCompressorAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MaloyAudioCompressorAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int MaloyAudioCompressorAudioProcessor::getCurrentProgram()
{
    return 0;
}

void MaloyAudioCompressorAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String MaloyAudioCompressorAudioProcessor::getProgramName (int index)
{
    return {};
}

void MaloyAudioCompressorAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void MaloyAudioCompressorAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    mSpec.maximumBlockSize = samplesPerBlock;
    mSpec.sampleRate = sampleRate;
    mSpec.numChannels = 2;
    
    // Create objects
    // Amplifier
    Amp.prepare(mSpec);
    LevelDetect.prepare(mSpec);
    GainComp.prepare(mSpec);
    
}

void MaloyAudioCompressorAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MaloyAudioCompressorAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void MaloyAudioCompressorAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    // Standard stuff
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // setout plugin
    updateEffectParameters();
    
    // 1. Input gain
    //Amp.process(buffer);
    
    // 2. Detect signal level
    LevelDetect.process(buffer);
    GainComp.process(LevelDetect.getSideChain());
    
    // 3. apply gain from gaincomp
    Amp.process(buffer, GainComp.getSideChain());
}

void MaloyAudioCompressorAudioProcessor::updateEffectParameters()
{
    Amp.updateParams(
                     apvts.getRawParameterValue("INPUT LEVEL")->load(),
                     apvts.getRawParameterValue("INPUT GAIN")->load()
                     );
    LevelDetect.updateParams();
    GainComp.updateParams(
                          apvts.getRawParameterValue("THRESHOLD")->load(),
                          apvts.getRawParameterValue("RATIO")->load(),
                          apvts.getRawParameterValue("KNEE")->load()
                          );
}

//==============================================================================
bool MaloyAudioCompressorAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* MaloyAudioCompressorAudioProcessor::createEditor()
{
    return new MaloyAudioCompressorAudioProcessorEditor (*this);
}

//==============================================================================
void MaloyAudioCompressorAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void MaloyAudioCompressorAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MaloyAudioCompressorAudioProcessor();
}
