/*
  ==============================================================================

    ButtonsAndDials.cpp
    Created: 18 Dec 2022 9:26:38am
    Author:  Ciaran Maloy

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ButtonsAndDials.h"

//==============================================================================
ButtonsAndDials::ButtonsAndDials(MaloyAudioCompressorAudioProcessor& p) : audioProcessor(p)
{
    // Add sliders and labels
    addSliderWithLabel(juce::Slider::SliderStyle::LinearVertical, &mInputLevelSlider, &mInputLevelLabel, "Level", WetDryChain::wet);
    addSliderWithLabel(juce::Slider::SliderStyle::RotaryVerticalDrag, &mInputGainSlider, &mInputGainLabel, "Gain", WetDryChain::wet);
    
    addSliderWithLabel(juce::Slider::SliderStyle::RotaryVerticalDrag, &mThresholdSlider, &mThresholdLabel, "Threshold", WetDryChain::wet);
    addSliderWithLabel(juce::Slider::SliderStyle::RotaryVerticalDrag, &mRatioSlider, &mRatioLabel, "Ratio", WetDryChain::wet);
    
    addSliderWithLabel(juce::Slider::SliderStyle::RotaryVerticalDrag, &mKneeSlider, &mKneeLabel, "Knee", WetDryChain::wet);
    
    // Sliders
    mInputLevelAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getAPVTS(), "INPUT LEVEL", mInputLevelSlider);
    mInputGainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getAPVTS(), "INPUT GAIN", mInputGainSlider);
    
    mThresholdAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getAPVTS(), "THRESHOLD", mThresholdSlider);
    mRatioAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getAPVTS(), "RATIO", mRatioSlider);
    mKneeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getAPVTS(), "KNEE", mKneeSlider);
    
    // transfer object
    addTransferObjWithLabel(&mCompTransferObj, &mCompTransferObjLabel, "Compressor");
}

ButtonsAndDials::~ButtonsAndDials()
{
}

void ButtonsAndDials::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::black);   // clear the background
    g.setColour(juce::Colours::white);
    
    auto InputColour = juce::Colours::white;
    mInputLevelSlider.setColour(juce::Slider::ColourIds::thumbColourId, InputColour);
    mInputLevelSlider.setColour(juce::Slider::ColourIds::textBoxTextColourId, InputColour);
    mInputLevelLabel.setColour(juce::Label::textColourId, InputColour);
    mInputGainSlider.setColour(juce::Slider::ColourIds::thumbColourId, InputColour);
    mInputGainSlider.setColour(juce::Slider::ColourIds::textBoxTextColourId, InputColour);
    mInputGainLabel.setColour(juce::Label::textColourId, InputColour);
    
    auto CompressorColour = juce::Colours::white;
    mThresholdSlider.setColour(juce::Slider::ColourIds::thumbColourId, CompressorColour);
    mThresholdSlider.setColour(juce::Slider::ColourIds::textBoxTextColourId, CompressorColour);
    mThresholdLabel.setColour(juce::Label::textColourId, CompressorColour);
    mRatioSlider.setColour(juce::Slider::ColourIds::thumbColourId, CompressorColour);
    mRatioSlider.setColour(juce::Slider::ColourIds::textBoxTextColourId, CompressorColour);
    mRatioLabel.setColour(juce::Label::textColourId, CompressorColour);
    
    auto CompTransferObjColour = juce::Colours::white;
    mCompTransferObj.setLineColour(CompTransferObjColour);
    mCompTransferObj.repaint();
    mCompTransferObj.setColour(juce::Label::textColourId, CompTransferObjColour);
}

void ButtonsAndDials::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    const auto startX = 0.f;
    const auto startY = 0.2f;
    const auto dialWidth = 1.0f/9.0f;
    const auto dialHeight = 0.75f;
    
    float n = 0;
    
    // Input
    mInputLevelSlider.setBoundsRelative(startX+n*dialWidth, startY, dialWidth, dialHeight);n+=1;
    mInputGainSlider.setBoundsRelative(startX+n*dialWidth, startY, dialWidth, dialHeight);n+=1;
    
    // Distortion
    mThresholdSlider.setBoundsRelative(startX+n*dialWidth, startY, dialWidth, dialHeight);n+=1;
    mRatioSlider.setBoundsRelative(startX+n*dialWidth, startY, dialWidth, dialHeight);n+=1;
    mKneeSlider.setBoundsRelative(startX+n*dialWidth, startY, dialWidth, dialHeight);n+=1;
    
    // Graphics
    mCompTransferObj.setBoundsRelative(startX+n*dialWidth, startY, dialWidth, dialHeight);n+=1;
}

void ButtonsAndDials::addSliderWithLabel(juce::Slider::SliderStyle style, juce::Slider* sliderObj, juce::Label* labelObj, std::string label_text,  WetDryChain selection, double centre_point)
{
    // Create Sliders
    sliderObj->setSliderStyle(style);
    sliderObj->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    
    switch (selection)
    {
        case WetDryChain::wet:
            sliderObj->setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::white);
            break;
            
        case WetDryChain::dry:
            sliderObj->setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::powderblue);
            break;
        default:
            break;
    }
    
    addAndMakeVisible(sliderObj);
    
    // Add label
    labelObj->setFont(15.f);
    labelObj->setText(label_text, juce::NotificationType::dontSendNotification);
    labelObj->setJustificationType(juce::Justification::horizontallyCentred);
    labelObj->attachToComponent(sliderObj, false); // when this is true for some reason the labels show up??
    
    addAndMakeVisible(labelObj);
}

//void ButtonsAndDials::addToggleWithLabel(juce::ToggleButton* toggleObj, juce::Label* labelObj, std::string label_text, double centre_point)
//{
//    addAndMakeVisible(toggleObj);
//    
//    // Add label
//    labelObj->setFont(10.f);
//    labelObj->setText(label_text, juce::NotificationType::dontSendNotification);
//    labelObj->setJustificationType(juce::Justification::centredRight);
//    labelObj->attachToComponent(toggleObj, false);
//    
//    addAndMakeVisible(labelObj);
//}

void ButtonsAndDials::addTransferObjWithLabel(ViewVoltageTransfer* trans, juce::Label* labelObj, std::string label_text)
{
    addAndMakeVisible(trans);
    // Add label
    labelObj->setFont(15.f);
    labelObj->setText(label_text, juce::NotificationType::dontSendNotification);
    labelObj->setJustificationType(juce::Justification::horizontallyCentred);
    labelObj->attachToComponent(trans, false);
    addAndMakeVisible(labelObj);
}
