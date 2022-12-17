/*
  ==============================================================================

    LevelDetector.h
    Created: 12 Dec 2022 8:52:37pm
    Author:  Ciaran Maloy

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class LevelDetector
{
public:
    LevelDetector(); // constructor
    void prepare(juce::dsp::ProcessSpec); // input spec
    void process(juce::AudioBuffer<float>&); // process data within the audio buffer
    void updateParams(); // update paramiters (no input)
    void updateParams(float, float); // attack, release
    void update();
    
    // getters and setters
    juce::AudioBuffer<float> getSideChain(); // maybe this should be a pointer?
    
private:
    struct parameters // parameters that can be used
    {
        std::array<float, 2> attack { 1, 1 };
        std::array<float, 2> release { 1, 1 };
    };
    parameters mParams;
    juce::dsp::ProcessSpec mSpec;
    juce::AudioBuffer<float> sideChain;
};
