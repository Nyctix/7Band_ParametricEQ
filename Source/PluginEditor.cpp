//==============================================================================

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
_7Band_ParametricEQAudioProcessorEditor::_7Band_ParametricEQAudioProcessorEditor (_7Band_ParametricEQAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    for (auto* componenet : getComponents())
    {
        addAndMakeVisible(componenet);
    }

    setSize(500, 800);

    //Parameter Attachments - Input, Output & Phase
    inputGainSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.ParaEQ, "Input Gain", inputGainSlider);
    outputGainSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.ParaEQ, "Output Gain", outputGainSlider);
    phaseInvertButtonAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.ParaEQ, "Phase", phaseInvertButton);

    //Parameter Attachments - LowCut Filter
    lowCutFreqSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.ParaEQ, "LowCut Frequency", lowCutFreqSlider);
    lowCutSlopeSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.ParaEQ, "LowCut Slope", lowCutSlopeSlider);
    lowCutBypassButtonAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.ParaEQ, "LowCut Bypass", lowCutBypassButton);

    //Parameter Attachments - HighCut Filter
    highCutFreqSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.ParaEQ, "HighCut Frequency", highCutFreqSlider);
    highCutSlopeSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.ParaEQ, "HighCut Slope", highCutSlopeSlider);
    highCutBypassButtonAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.ParaEQ, "HighCut Bypass", highCutBypassButton);

    //Parameter Attachments - HighShelf Filter
    highShelfFreqSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.ParaEQ, "HighShelf Frequency", highShelfFreqSlider);
    highShelfGainSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.ParaEQ, "HighShelf Gain", highShelfGainSlider);
    highShelfQSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.ParaEQ, "HighShelf Quality", highShelfQSlider);
    highShelfToBellButtonAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.ParaEQ, "HighShelf to Bell", highShelfToBellButton);
    highShelfBypassButtonAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.ParaEQ, "HighShelf Bypass", highShelfBypassButton);

    //Parameter Attachments - LowShelf Filter
    lowShelfFreqSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.ParaEQ, "LowShelf Frequency", lowShelfFreqSlider);
    lowShelfGainSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.ParaEQ, "LowShelf Gain", lowShelfGainSlider);
    lowShelfQSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.ParaEQ, "LowShelf Quality", lowShelfQSlider);
    lowShelfToBellButtonAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.ParaEQ, "LowShelf to Bell", lowShelftoBellButton);
    lowShelfBypassButtonAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.ParaEQ, "LowShelf Bypass", lowShelfBypassButton);

    //Parameter Attachments - HighMid Filter
    highMidFreqSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.ParaEQ, "HighMid Frequency", highMidFreqSlider);
    highMidGainSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.ParaEQ, "HighMid Gain", highMidGainSlider);
    highMidQSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.ParaEQ, "HighMid Quality", highMidQSlider);
    highMidBypassButtonAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.ParaEQ, "HighMid Bypass", highMidBypassButton);

    //Parameter Attachments - LowMid Filter
    lowMidFreqSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.ParaEQ, "LowMid Frequency", lowMidFreqSlider);
    lowMidGainSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.ParaEQ, "LowMid Gain", lowMidGainSlider);
    lowMidQSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.ParaEQ, "LowMid Quality", lowMidQSlider);
    lowMidBypassButtonAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.ParaEQ, "LowMid Bypass", lowMidBypassButton);


    //StartTimer for Meter Refreshing
    startTimerHz(60);
}

_7Band_ParametricEQAudioProcessorEditor::~_7Band_ParametricEQAudioProcessorEditor()
{
}

void _7Band_ParametricEQAudioProcessorEditor::timerCallback()
{
    InputMeterL.setLevel(audioProcessor.getRmsValue(0));
    InputMeterR.setLevel(audioProcessor.getRmsValue(1));
    InputMeterL.repaint();
    InputMeterR.repaint();

    OutputMeterL.setLevel(audioProcessor.getRmsValue(0));
    OutputMeterR.setLevel(audioProcessor.getRmsValue(1));
    OutputMeterL.repaint();
    OutputMeterR.repaint();
}

//==============================================================================
void _7Band_ParametricEQAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.drawImage(juce::ImageCache::getFromMemory(BinaryData::RoughLayout_png, BinaryData::RoughLayout_pngSize), getLocalBounds().toFloat());
}

void _7Band_ParametricEQAudioProcessorEditor::resized()
{
    auto totalArea = getLocalBounds(); // (pos x, pos y, size width, size height) = diff: 9, 9

    inputGainSlider.setBounds(337, 262, 75, 75); //346, 271
    outputGainSlider.setBounds(337, 652, 75, 75); //346, 661
    phaseInvertButton.setBounds(362, 744, 25, 25); //346, 746

    InputMeterL.setBounds(315, 370, 20, 240);
    InputMeterR.setBounds(345, 370, 20, 240);
    OutputMeterL.setBounds(385, 370, 20, 240);
    OutputMeterR.setBounds(415, 370, 20, 240);

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

        &InputMeterL,
        &InputMeterR,
        &OutputMeterL,
        &OutputMeterR,

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