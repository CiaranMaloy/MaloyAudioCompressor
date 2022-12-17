/*
  ==============================================================================

    Amplifier.h
    Created: 12 Dec 2022 8:52:12pm
    Author:  Ciaran Maloy

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "WaveShaping.h"

class Amplifier
{
public:
    Amplifier(); // constructor
    void prepare(juce::dsp::ProcessSpec); // input spec
    void process(juce::AudioBuffer<float>&); // process data within the audio buffer
    //void process(juce::AudioBuffer<float>&, juce::AudioBuffer<float>); // override for sidechain
    void updateParams(); // update paramiters (no input)
    void updateParams(float, float); // update parameters with gain and volume
    void update(); // update
private:
    struct parameters // parameters that can be used
    {
        std::array<float, 2> gain { 1, 1 };
        std::array<float, 2> level { 1, 1 };
    };
    parameters mParams; // global private parameters
    juce::dsp::ProcessSpec mSpec; // global private 
};
