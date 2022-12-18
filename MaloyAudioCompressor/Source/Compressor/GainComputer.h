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
    void process(juce::AudioBuffer<float>); // process data within the audio buffer
    void updateParams(); // update paramiters (no input)
    void updateParams(float, float, float); // threshold, ratio, knee
    void update(); // update
    
    // getters and setters
    juce::AudioBuffer<float> getSideChain();
private:
    struct parameters // parameters that can be used
    {
        std::array<float, 2> threshold { 1, 1 };
        std::array<float, 2> ratio { 1, 1 };
        std::array<float, 2> knee { 1, 1 };
    };
    parameters mParams; // global private parameters
    juce::dsp::ProcessSpec mSpec; // global private
    juce::AudioBuffer<float> sideChain;
    
    float computeGain(float, float, float, float); // input, threshold, ratio, knee
};
