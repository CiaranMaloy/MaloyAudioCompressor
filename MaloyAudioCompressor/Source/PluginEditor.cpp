/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MaloyAudioCompressorAudioProcessorEditor::MaloyAudioCompressorAudioProcessorEditor (MaloyAudioCompressorAudioProcessor& p)
: AudioProcessorEditor (&p), ButtonsAndDialsObj(p), audioProcessor(p)
{
    addAndMakeVisible(ButtonsAndDialsObj);
    //addAndMakeVisible(VisualiserWindowObj);
    setSize (800, 250);
}

MaloyAudioCompressorAudioProcessorEditor::~MaloyAudioCompressorAudioProcessorEditor()
{
}

//==============================================================================
void MaloyAudioCompressorAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::green);
    g.setColour(juce::Colours::white);
}

void MaloyAudioCompressorAudioProcessorEditor::resized()
{
    const float bnd_x_pos_relative = 0;
    const float bnd_y_pos_relative = 0.4;
    
    ButtonsAndDialsObj.setBoundsRelative(bnd_x_pos_relative, bnd_y_pos_relative, 1.0f-bnd_x_pos_relative, 1.0f-bnd_y_pos_relative);
}
