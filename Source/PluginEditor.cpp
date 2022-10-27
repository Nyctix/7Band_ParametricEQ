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

    auto totalArea = getLocalBounds();

    inputGainSlider.setBounds(337, 652, 75, 75); //346, 661
    outputGainSlider.setBounds(337, 262, 75, 75); //346, 271

    lowCutFreqSlider.setBounds(294, 18, 75, 75); //303, 27
    lowCutSlopeSlider.setBounds(294, 111, 75, 75); //303, 121

    highCutFreqSlider.setBounds(384, 18, 75, 75); //393,27
    highCutSlopeSlider.setBounds(384, 111, 75, 75); //393,121

    highShelfFreqSlider.setBounds(32, 19, 75, 75); // (pos x, pos y, size width, size height) = diff: 9, 9
    highShelfGainSlider.setBounds(142, 18, 75, 75); //151 , 27
    highShelfQSlider.setBounds(87, 110, 75, 75); //96, 119

    highMidFreqSlider.setBounds(31, 220, 75, 75); //40, 229
    highMidGainSlider.setBounds(31, 310, 75, 75); //40, 319
    highMidQSlider.setBounds(107, 274, 75, 75); //116, 283

    lowMidFreqSlider.setBounds(32, 420, 75, 75); // 42, 429 
    lowMidGainSlider.setBounds(32, 510, 75, 75); // 42, 519
    lowMidQSlider.setBounds(107, 463, 75, 75); // 116, 472

    lowShelfFreqSlider.setBounds(32, 705, 75, 75); // 42, 714
    lowShelfGainSlider.setBounds(142, 705, 75,75); //152, 
    lowShelfQSlider.setBounds(87, 614, 75, 75); // 96, 623

}

std::vector<juce::Component*> _7Band_ParametricEQAudioProcessorEditor::getComponents()
{
    return
    {
        &inputGainSlider,
        &outputGainSlider,

        &lowCutFreqSlider,
        &lowCutSlopeSlider,
        &highCutFreqSlider,
        &highCutSlopeSlider,

        &highShelfFreqSlider,
        &highShelfQSlider,
        &highShelfGainSlider,

        &highMidFreqSlider,
        &highMidQSlider,
        &highMidGainSlider,

        &lowMidFreqSlider,
        &lowMidQSlider,
        &lowMidGainSlider,

        &lowShelfFreqSlider,
        &lowShelfQSlider,
        &lowShelfGainSlider

    };
}


