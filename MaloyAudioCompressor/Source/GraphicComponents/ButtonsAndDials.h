/*
  ==============================================================================

    ButtonsAndDials.h
    Created: 18 Dec 2022 9:26:38am
    Author:  Ciaran Maloy

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../PluginProcessor.h"
#include "ViewVoltageTransfer.h"

//==============================================================================
/*
 1. I'll have to add the audio processor in here later, when I use a value tree to pass over th values
 but a. just do the graphics
*/
class ButtonsAndDials  : public juce::Component
{
public:
    ButtonsAndDials(MaloyAudioCompressorAudioProcessor& p);
    ~ButtonsAndDials() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // ====== Selection enum ======
    enum WetDryChain
    {
        wet,
        dry
    };
    
    //    // setout plugin
    //    float input_level = 1.0f;
    //    float input_gain = 1.0f;
    //    float threshold = 0.2;
    //    float ratio = 5.0f;
    //    float knee = 0.1;
    // ====== Sliders and Labels ======
    juce::Slider mInputGainSlider, mInputLevelSlider, mThresholdSlider, mRatioSlider, mKneeSlider;
    juce::Label mInputGainLabel, mInputLevelLabel, mThresholdLabel, mRatioLabel, mKneeLabel;
    
    
    void addSliderWithLabel(juce::Slider::SliderStyle style, juce::Slider* sliderObj, juce::Label* labelObj, std::string labelText, WetDryChain selection, double centre_point=0);
    //void addToggleWithLabel(juce::ToggleButton* toggleObj, juce::Label* labelObj, std::string label_text, double centre_point=0);
    void addTransferObjWithLabel(ViewVoltageTransfer* trans, juce::Label* labelObj, std::string label_text);
    // ====== ======
    
    // ====== audio processor value tree state attachments =====
    // Sliders
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mInputLevelAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mInputGainAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mThresholdAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mRatioAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mKneeAttachment;
    // ====== ======
    
    // ====== Audio Processor Pointer ======
    MaloyAudioCompressorAudioProcessor& audioProcessor;
    // ====== ======
    
    // ====== Visuals ======
    ViewVoltageTransfer mCompTransferObj;
    juce::Label mCompTransferObjLabel;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ButtonsAndDials)
};
