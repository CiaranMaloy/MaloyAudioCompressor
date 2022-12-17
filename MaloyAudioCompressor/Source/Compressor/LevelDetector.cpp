/*
  ==============================================================================

    LevelDetector.cpp
    Created: 12 Dec 2022 8:52:37pm
    Author:  Ciaran Maloy

  ==============================================================================
*/

#include "LevelDetector.h"

LevelDetector::LevelDetector()
{
    // empty constructor
}

void LevelDetector::prepare(juce::dsp::ProcessSpec specification)
{
    mSpec = specification;
    
    // set buffer object
    sideChain.setSize(mSpec.numChannels, mSpec.maximumBlockSize);
}

void LevelDetector::process(juce::AudioBuffer<float>& buffer)
{
    // for now this just calculates a sidechain array that
    for (int channel = 0; channel < mSpec.numChannels; channel++)
    {
        buffer.applyGainRamp(channel, 0, buffer.getNumSamples(), mParams.example[0], mParams.example[1]);
    }
}

void LevelDetector::update()
{
    mParams.example[0] = mParams.example[1];
}

void LevelDetector::updateParams()
{
    update();
}

void LevelDetector::updateParams(float example)
{
    update();
    mParams.example[1] = example;
}
