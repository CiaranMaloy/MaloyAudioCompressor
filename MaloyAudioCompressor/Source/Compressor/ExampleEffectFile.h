/*
  ==============================================================================

    ExampleEffectFile.h
    Created: 17 Dec 2022 10:05:14pm
    Author:  Ciaran Maloy

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class EffectName
{
public:
    EffectName(); // constructor
    void prepare(juce::dsp::ProcessSpec); // input spec
    void process(juce::AudioBuffer<float>&); // process data within the audio buffer
    void updateParams(); // update paramiters (no input)
    void updateParams(float); // update parameters with gain and volume
    void update(); // update
private:
    struct parameters // parameters that can be used
    {
        std::array<float, 2> example { 1, 1 };  
    };
    parameters mParams; // global private parameters
    juce::dsp::ProcessSpec mSpec; // global private
};
