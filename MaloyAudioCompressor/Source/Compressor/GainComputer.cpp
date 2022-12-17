/*
  ==============================================================================

    GainComputer.cpp
    Created: 12 Dec 2022 8:52:55pm
    Author:  Ciaran Maloy

  ==============================================================================
*/

#include "GainComputer.h"

GainComputer::GainComputer()
{
    // empty constructor
}

void GainComputer::prepare(juce::dsp::ProcessSpec specification)
{
    mSpec = specification;
    sideChain.setSize(mSpec.numChannels, mSpec.maximumBlockSize);
}

void GainComputer::process(juce::AudioBuffer<float>& bufferFromLevelDetector)
{
    // volume
    for (int channel = 0; channel < mSpec.numChannels; channel++)
    {
        const float * levelDetectorReadPointer = bufferFromLevelDetector.getReadPointer(channel);
        float * gainComputerWritePointer = sideChain.getWritePointer(channel);
        for (int sample = 0; sample < mSpec.maximumBlockSize; sample++)
        {
            gainComputerWritePointer[sample] = computegain(levelDetectorReadPointer[sample]);
        }
    }
}

void GainComputer::update()
{
    mParams.example[0] = mParams.example[1];
}

void GainComputer::updateParams()
{
    update();
}

void GainComputer::updateParams(float example)
{
    update();
    mParams.example[1] = example;
}

// private function
float GainComputer::computeGain(float input, float threshold, float ratio, float knee)
{
    // gain computation algorithm goes here
    
    
    return gain;
}
