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
    sideChain.setSize(mSpec.numChannels, mSpec.maximumBlockSize);
}

void LevelDetector::process(juce::AudioBuffer<float>& buffer)
{
    // for now this just calculates a sidechain array that
    for (int channel = 0; channel < mSpec.numChannels; channel++)
    {
        // calculate rms value of the buffer
        float buffer_sum = 0;
        const float * mainBufferReadPointer = buffer.getReadPointer(channel);
        for (int sample = 0; sample < mSpec.maximumBlockSize; sample++ )
        {
            buffer_sum += mainBufferReadPointer[sample] * mainBufferReadPointer[sample];
        }
        float rms_value = std::sqrt(buffer_sum/static_cast<float>(mSpec.maximumBlockSize));
        
        // make the rms value in the side chain
        float * sideChainWritePointer = sideChain.getWritePointer(channel);
        for (int sample = 0; sample < mSpec.maximumBlockSize; sample++)
        {
            sideChainWritePointer[sample] = rms_value;
        }
    }
}

void LevelDetector::update()
{
    mParams.attack[0] = mParams.attack[1];
    mParams.release[0] = mParams.release[1];
}

void LevelDetector::updateParams()
{
    update();
}

void LevelDetector::updateParams(float attack, float release)
{
    update();
    mParams.attack[1] = attack;
    mParams.release[1] = release;
}

juce::AudioBuffer<float> LevelDetector::getSideChain()
{
    return sideChain;
}
