/*
  ==============================================================================

    Amplifier.cpp
    Created: 12 Dec 2022 8:52:12pm
    Author:  Ciaran Maloy

  ==============================================================================
*/

#include "Amplifier.h"

Amplifier::Amplifier()
{
    // empty constructor
}

void Amplifier::prepare(juce::dsp::ProcessSpec specification)
{
    mSpec = specification;
}

void Amplifier::process(juce::AudioBuffer<float>& buffer)
{
    // gain
    WaveShaping::process(WaveShaping::EffectType::amp, buffer, mParams.gain[1]);
    
    // volunme
    for (int channel = 0; channel < mSpec.numChannels; channel++)
    {
        buffer.applyGainRamp(channel, 0, buffer.getNumSamples(), mParams.level[0], mParams.level[1]);
    }
}

// override for side chain input
void Amplifier::process(juce::AudioBuffer<float>& buffer, juce::AudioBuffer<float> sideChain)
{
    for (int channel = 0; channel < mSpec.numChannels; channel++)
    {
        float* bufferWrite = buffer.getWritePointer(channel);
        const float* bufferRead = buffer.getReadPointer(channel);
        const float* sideChainRead = buffer.getReadPointer(channel);
        
        for (int sample = 0; sample < mSpec.maximumBlockSize; sample++)
        {
            bufferWrite[sample] = bufferRead[sample] * sideChainRead[sample];
        }
    }
}

void Amplifier::update()
{
    mParams.level[0] = mParams.level[1];
    mParams.gain[0] = mParams.gain[1];
}

void Amplifier::updateParams()
{
    update();
}

void Amplifier::updateParams(float level, float gain)
{
    update();
    mParams.level[1] = level;
    mParams.gain[1] = gain;
}
