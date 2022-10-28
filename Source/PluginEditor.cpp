/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
_7Band_ParametricEQAudioProcessorEditor::_7Band_ParametricEQAudioProcessorEditor (_7Band_ParametricEQAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.

    for (auto* componenet : getComponents())
    {
        addAndMakeVisible(componenet);
    }

    setSize(500, 800);

    inputGainSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.ParaEQ, "Input Gain", inputGainSlider);
    outputGainSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.ParaEQ, "Output Gain", outputGainSlider);

    lowCutFreqSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.ParaEQ, "LowCut Frequency", lowCutFreqSlider);
    lowCutSlopeSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.ParaEQ, "LowCut Slope", lowCutSlopeSlider);

    highCutFreqSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.ParaEQ, "HighCut Frequency", highCutFreqSlider);
    highCutSlopeSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.ParaEQ, "HighCut Slope", highCutSlopeSlider);

    highShelfFreqSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.ParaEQ, "HighShelf Frequency", highShelfFreqSlider);
    highShelfGainSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.ParaEQ, "HighShelf Gain", highShelfGainSlider);
    highShelfQSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.ParaEQ, "HighShelf Quality", highShelfQSlider);

    lowShelfFreqSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.ParaEQ, "LowShelf Frequency", lowShelfFreqSlider);
    lowShelfGainSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.ParaEQ, "LowShelf Gain", lowShelfGainSlider);
    lowShelfQSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.ParaEQ, "LowShelf Quality", lowShelfQSlider);
    
    highMidFreqSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.ParaEQ, "HighMid Frequency", highMidFreqSlider);
    highMidGainSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.ParaEQ, "HighMid Gain", highMidGainSlider);
    highMidQSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.ParaEQ, "HighMid Quality", highMidQSlider);

    lowMidFreqSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.ParaEQ, "LowMid Frequency", lowMidFreqSlider);
    lowMidGainSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.ParaEQ, "LowMid Gain", lowMidGainSlider);
    lowMidQSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.ParaEQ, "LowMid Quality", lowMidQSlider);

}

_7Band_ParametricEQAudioProcessorEditor::~_7Band_ParametricEQAudioProcessorEditor()
{
}

//==============================================================================
void _7Band_ParametricEQAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.drawImage(juce::ImageCache::getFromMemory(BinaryData::RoughLayout_png, BinaryData::RoughLayout_pngSize), getLocalBounds().toFloat());
}

void _7Band_ParametricEQAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    auto totalArea = getLocalBounds(); // (pos x, pos y, size width, size height) = diff: 9, 9

    inputGainSlider.setBounds(337, 262, 75, 75); //346, 271
    outputGainSlider.setBounds(337, 652, 75, 75); //346, 661
    phaseInvertButton.setBounds(362, 744, 25, 25); //346, 746

    lowCutFreqSlider.setBounds(294, 18, 75, 75); //303, 27
    lowCutSlopeSlider.setBounds(294, 111, 75, 75); //303, 121
    lowCutBypassButton.setBounds(319, 198, 25, 25); //319, 197

    highCutFreqSlider.setBounds(384, 18, 75, 75); //393,27
    highCutSlopeSlider.setBounds(384, 111, 75, 75); //393,121
    highCutBypassButton.setBounds(408, 198, 25, 25); //408, 197

    highShelfFreqSlider.setBounds(32, 19, 75, 75); //41, 28
    highShelfGainSlider.setBounds(142, 18, 75, 75); //151 , 27
    highShelfQSlider.setBounds(87, 110, 75, 75); //96, 119
    highShelfToBellButton.setBounds(187, 134, 25, 25); // 186, 134
    highShelfBypassButton.setBounds(187, 198, 25, 25); //186, 197

    highMidFreqSlider.setBounds(31, 220, 75, 75); //40, 229
    highMidGainSlider.setBounds(31, 310, 75, 75); //40, 319
    highMidQSlider.setBounds(107, 274, 75, 75); //116, 283
    highMidBypassButton.setBounds(187, 351, 25, 25); //187, 351

    lowMidFreqSlider.setBounds(32, 420, 75, 75); // 42, 429 
    lowMidGainSlider.setBounds(32, 510, 75, 75); // 42, 519
    lowMidQSlider.setBounds(107, 463, 75, 75); // 116, 472
    lowMidBypassButton.setBounds(187, 430, 25, 25); //187, 430

    lowShelfFreqSlider.setBounds(32, 705, 75, 75); // 42, 714
    lowShelfGainSlider.setBounds(142, 705, 75,75); //152, 
    lowShelfQSlider.setBounds(87, 614, 75, 75); // 96, 623
    lowShelftoBellButton.setBounds(187, 639, 25, 25); //187, 638
    lowShelfBypassButton.setBounds(187, 575, 25, 25); //187, 574

}

std::vector<juce::Component*> _7Band_ParametricEQAudioProcessorEditor::getComponents()
{
    return
    {
        &inputGainSlider,
        &outputGainSlider,
        &phaseInvertButton,

        &lowCutFreqSlider,
        &lowCutSlopeSlider,
        &highCutFreqSlider,
        &highCutSlopeSlider,
        &lowCutBypassButton,
        &highCutBypassButton,

        &highShelfFreqSlider,
        &highShelfQSlider,
        &highShelfGainSlider,
        &highShelfBypassButton,
        &highShelfToBellButton,

        &highMidFreqSlider,
        &highMidQSlider,
        &highMidGainSlider,
        &highMidBypassButton,

        &lowMidFreqSlider,
        &lowMidQSlider,
        &lowMidGainSlider,
        &lowMidBypassButton,

        &lowShelfFreqSlider,
        &lowShelfQSlider,
        &lowShelfGainSlider,
        &lowShelfBypassButton,
        &lowShelftoBellButton

    };
}


