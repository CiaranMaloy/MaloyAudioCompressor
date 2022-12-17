/*
  ==============================================================================

    GainComputer.h
    Created: 12 Dec 2022 8:52:55pm
    Author:  Ciaran Maloy

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class GainComputer
{
public:
    GainComputer(); // constructor
    void prepare(juce::dsp::ProcessSpec); // input spec
    void process(juce::AudioBuffer<float>&); // process data within the audio buffer
    void updateParams(); // update paramiters (no input)
    void updateParams(float); // update parameters with gain and volume
    void update(); // update
    
    // getters and setters
    // there are none so far
private:
    struct parameters // parameters that can be used
    {
        std::array<float, 2> example { 1, 1 };
    };
    parameters mParams; // global private parameters
    juce::dsp::ProcessSpec mSpec; // global private
};
