/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

struct CustomRotarySlider : juce::Slider
{
    CustomRotarySlider() : juce::Slider
        (juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag,
         juce::Slider::TextEntryBoxPosition::NoTextBox)
        {

        }
};

//==============================================================================
/**
*/
class _7Band_ParametricEQAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    _7Band_ParametricEQAudioProcessorEditor (_7Band_ParametricEQAudioProcessor&);
    ~_7Band_ParametricEQAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    _7Band_ParametricEQAudioProcessor& audioProcessor;

    CustomRotarySlider
        inputGainSlider,
        outputGainSlider,

        lowCutFreqSlider,
        lowCutSlopeSlider,
        highCutFreqSlider,
        highCutSlopeSlider,

        highShelfFreqSlider,
        highShelfQSlider,
        highShelfGainSlider,

        highMidFreqSlider,
        highMidQSlider,
        highMidGainSlider,

        lowMidFreqSlider,
        lowMidQSlider,
        lowMidGainSlider,

        lowShelfFreqSlider,
        lowShelfQSlider,
        lowShelfGainSlider;

    std::vector<juce::Component*> getComponents();


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (_7Band_ParametricEQAudioProcessorEditor)
};
