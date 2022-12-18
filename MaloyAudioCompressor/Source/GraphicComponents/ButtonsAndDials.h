/*
  ==============================================================================

    ButtonsAndDials.h
    Created: 18 Dec 2022 9:26:38am
    Author:  Ciaran Maloy

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class ButtonsAndDials  : public juce::Component
{
public:
    ButtonsAndDials();
    ~ButtonsAndDials() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ButtonsAndDials)
};
