/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "GraphicComponents/ButtonsAndDials.h"

//==============================================================================
/**
*/
class MaloyAudioCompressorAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    MaloyAudioCompressorAudioProcessorEditor (MaloyAudioCompressorAudioProcessor&);
    ~MaloyAudioCompressorAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    ButtonsAndDials ButtonsAndDialsObj;
    
    MaloyAudioCompressorAudioProcessor& audioProcessor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MaloyAudioCompressorAudioProcessorEditor)
};
