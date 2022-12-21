/*
  ==============================================================================

    ViewVoltageTransfer.h
    Created: 21 Dec 2022 7:17:56am
    Author:  Ciaran Maloy

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../Compressor/GainComputer.h"

/*
  ==============================================================================
*/
class ViewVoltageTransfer  : public juce::Component
{
public:
    ViewVoltageTransfer();
    ~ViewVoltageTransfer() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    void setLineColour(juce::Colour colour) {mSetColour = colour;};
    

private:
    // == rects
    juce::Rectangle<float> outerBounds;
    juce::Rectangle<float> innerBounds;
    
    // == member variable buffer
//    juce::AudioBuffer<float> mDisplayBuffer;
    
    // == voltage transfer
    juce::Path generateVoltageTransferPath(juce::Rectangle<float> Rect);
    //juce::Path generateVoltageTransferPath(juce::Rectangle<float> Rect, WaveShaping::EffectType type);
    
    // == Settings
    juce::Colour mSetColour {juce::Colours::white};
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ViewVoltageTransfer)
};
