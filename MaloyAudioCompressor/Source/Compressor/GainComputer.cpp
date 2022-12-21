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
    mSpec.maximumBlockSize = 512;
    mSpec.numChannels = 1;
    mSpec.sampleRate = 44100;
}

void GainComputer::prepare(juce::dsp::ProcessSpec specification)
{
    mSpec = specification;
    sideChain.setSize(mSpec.numChannels, mSpec.maximumBlockSize);
}

void GainComputer::process(juce::AudioBuffer<float> bufferFromLevelDetector)
{
    // volume
    for (int channel = 0; channel < mSpec.numChannels; channel++)
    {
        const float * levelDetectorReadPointer = bufferFromLevelDetector.getReadPointer(channel);
        float * gainComputerWritePointer = sideChain.getWritePointer(channel);
        for (int sample = 0; sample < mSpec.maximumBlockSize; sample++)
        {
            gainComputerWritePointer[sample] = computeGain(
                                                           levelDetectorReadPointer[sample],
                                                           mParams.threshold[1],
                                                           mParams.ratio[1],
                                                           mParams.knee[1]
                                                           );
        }
    }
}

void GainComputer::update()
{
    mParams.threshold[0] = mParams.threshold[1];
    mParams.ratio[0] = mParams.ratio[1];
    mParams.knee[0] = mParams.knee[1];
    
}

void GainComputer::updateParams()
{
    update();
}

void GainComputer::updateParams(float threshold, float ratio, float knee)
{
    update();
    mParams.threshold[1] = threshold;
    mParams.ratio[1] = ratio;
    mParams.knee[1] = knee;
}

juce::AudioBuffer<float> GainComputer::getSideChain()
{
    return sideChain;
}

// private function
float GainComputer::computeGain(float input, float threshold, float ratio, float knee)
{
    // gain computation algorithm goes here
    if (2.0f*(input-threshold) < -knee)
    {
        return input;
    }
    else if (2.0f*std::abs(input-threshold) >= knee)
    {
        return input + ((1/(ratio-1)) * std::pow(input - threshold + knee/2, 2.0f))/(2.0f*knee);
    }
    else if (2.0f*(input-threshold) > knee)
    {
        return threshold + (input - threshold)/ratio;
    }
    else
    {
        jassert(false); // if this condition is hit the code will break, it shouldn't be hit
        return 0;
    }
}

// output gain curve
juce::AudioBuffer<float> GainComputer::getVoltageTransferFunction(int N)
{
    int CHANNEL = 0;
    int NCHANNELS = mSpec.numChannels;
    mDisplayBuffer.setSize(NCHANNELS, N);
    
    // === writer -1 to 1 in the buffer
    for (int sample = 0; sample < mDisplayBuffer.getNumSamples(); sample++)
    {
        float input = 1.0*(static_cast<float>(sample))/(static_cast<float>(N)); // = n/N for n to N
        mDisplayBuffer.setSample(CHANNEL, sample, input);
    }
    // ======
    // ====== Put the audio throught the effect
    process(mDisplayBuffer);
    // ======
    
    return mDisplayBuffer;
}
