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
    // Sliders/Knobs
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

    //Slider Attachments

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> inputGainSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> outputGainSliderAttachment;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> lowCutFreqSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> lowCutSlopeSliderAttachment;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> highCutFreqSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> highCutSlopeSliderAttachment;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> highShelfFreqSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> highShelfGainSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> highShelfQSliderAttachment;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> lowShelfFreqSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> lowShelfGainSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> lowShelfQSliderAttachment;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> highMidFreqSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> highMidGainSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> highMidQSliderAttachment;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> lowMidFreqSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> lowMidGainSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> lowMidQSliderAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (_7Band_ParametricEQAudioProcessorEditor)
};
