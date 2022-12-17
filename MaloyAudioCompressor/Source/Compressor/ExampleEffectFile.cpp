/*
  ==============================================================================

    ExampleEffectFile.cpp
    Created: 17 Dec 2022 10:05:14pm
    Author:  Ciaran Maloy

  ==============================================================================
*/

#include "ExampleEffectFile.h"

EffectName::EffectName()
{
    // empty constructor
}

void EffectName::prepare(juce::dsp::ProcessSpec specification)
{
    mSpec = specification;
}

void EffectName::process(juce::AudioBuffer<float>& buffer)
{
    // volume
    for (int channel = 0; channel < mSpec.numChannels; channel++)
    {
        buffer.applyGainRamp(channel, 0, buffer.getNumSamples(), mParams.example[0], mParams.example[1]);
    }
}

void EffectName::update()
{
    mParams.example[0] = mParams.example[1];
}

void EffectName::updateParams()
{
    update();
}

void EffectName::updateParams(float example)
{
    update();
    mParams.example[1] = example;
}
