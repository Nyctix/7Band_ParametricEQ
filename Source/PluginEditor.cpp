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
    g.drawImage(juce::ImageCache::getFromMemory(BinaryData::RoughLayout_jpeg, BinaryData::RoughLayout_jpegSize), getLocalBounds().toFloat());
}

void _7Band_ParametricEQAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    auto totalArea = getLocalBounds();

    inputGainSlider.setBounds(0, 0, 70, 70); // (pos x, pos y, size width, size height)


}

std::vector<juce::Component*> _7Band_ParametricEQAudioProcessorEditor::getComponents()
{
    return
    {
        &inputGainSlider,
        &outputGainSlider,

        &lowCutFreqSlider,
        &highCutFreqSlider,

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


