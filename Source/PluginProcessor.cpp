/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
_7Band_ParametricEQAudioProcessor::_7Band_ParametricEQAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

_7Band_ParametricEQAudioProcessor::~_7Band_ParametricEQAudioProcessor()
{
}

//==============================================================================
const juce::String _7Band_ParametricEQAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool _7Band_ParametricEQAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool _7Band_ParametricEQAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool _7Band_ParametricEQAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double _7Band_ParametricEQAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int _7Band_ParametricEQAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int _7Band_ParametricEQAudioProcessor::getCurrentProgram()
{
    return 0;
}

void _7Band_ParametricEQAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String _7Band_ParametricEQAudioProcessor::getProgramName (int index)
{
    return {};
}

void _7Band_ParametricEQAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void _7Band_ParametricEQAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void _7Band_ParametricEQAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool _7Band_ParametricEQAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void _7Band_ParametricEQAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
    }
}

//==============================================================================
bool _7Band_ParametricEQAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* _7Band_ParametricEQAudioProcessor::createEditor()
{
    //return new _7Band_ParametricEQAudioProcessorEditor (*this);
    return new juce::GenericAudioProcessorEditor(*this);
}

//==============================================================================
void _7Band_ParametricEQAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void _7Band_ParametricEQAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
//Parameter Layout
juce::AudioProcessorValueTreeState::ParameterLayout _7Band_ParametricEQAudioProcessor::createParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout parameter;

    //Gain Parameters ----------------------------------------------------------
    parameter.add(std::make_unique<juce::AudioParameterFloat>("Input Gain",
                                                                "Input Gain",
                                                                juce::NormalisableRange<float>(-15.0f, 15.0f, 1.0f, 1.0f),
                                                                0.0f));
    parameter.add(std::make_unique<juce::AudioParameterFloat>("Output Gain",
                                                                "Output Gain",
                                                                juce::NormalisableRange<float>(-15.0f, 15.0f, 1.0f, 1.0f),
                                                                0.0f));
    //HighCut & LowCut Slope Values --------------------------------------------------------------------------------------
    juce::StringArray slopeArray;
    for (int i = 0; i < 5; ++i)
    {
        juce::String strSlope;
        strSlope << (12 + i*12);
        strSlope << "db/Oct";
        slopeArray.add(strSlope);
    }
    //LowCut Filter ----------------------------------------------------------------------------------------
    parameter.add(std::make_unique<juce::AudioParameterFloat>("LowCut Frequency",
                                                                "LowCut Frequency",
                                                                juce::NormalisableRange<float>(16.0f, 350.0f, 1.0f, 1.0f),
                                                                16.0f));
    parameter.add(std::make_unique<juce::AudioParameterChoice>("LowCut Slope",
                                                                "LowCut Slope",
                                                                slopeArray,
                                                                0));
    //HighCut Filter ---------------------------------------------------------------------------------------
    parameter.add(std::make_unique<juce::AudioParameterFloat>("HighCut Frequency",
                                                                "HighCut Frequency",
                                                                juce::NormalisableRange<float>(3000.0f, 22000.0f, 100.0f, 1.0f),
                                                                22000.0f));
    parameter.add(std::make_unique<juce::AudioParameterChoice>("HighCut Slope",
                                                                "HighCut Slope",
                                                                slopeArray,
                                                                0));
    //HighShelf Filter -------------------------------------------------------------------------------------
    parameter.add(std::make_unique<juce::AudioParameterFloat>("HighShelf Frequency",
                                                                "HighShelf Frequency",
                                                                juce::NormalisableRange<float>(1500.0f, 16000.0f, 10.0f, 1.0f),
                                                                8000.0f));
    parameter.add(std::make_unique<juce::AudioParameterFloat>("HighShelf Quality",
                                                                "HighShelf Quality",
                                                                juce::NormalisableRange<float>(0.1f, 3.5f, 0.01f, 1.0f),
                                                                1.0f));
    parameter.add(std::make_unique<juce::AudioParameterFloat>("HighShelf Gain",
                                                                "HighShelf Gain",
                                                                juce::NormalisableRange<float>(-15.0f, 15.0f, 0.1f, 1.0f),
                                                                0.0f));
    //HighMidPeak Filter -------------------------------------------------------------------------------------
    parameter.add(std::make_unique<juce::AudioParameterFloat>("HighMid Frequency",
                                                                "HighMid Frequency",
                                                                juce::NormalisableRange<float>(600.0f, 7000.0f, 10.0f, 1.0f),
                                                                3500.0f));
    parameter.add(std::make_unique<juce::AudioParameterFloat>("HighMid Quality",
                                                                "HighMid Quality",
                                                                juce::NormalisableRange<float>(0.1f, 3.5f, 0.01f, 1.0f),
                                                                1.0f));
    parameter.add(std::make_unique<juce::AudioParameterFloat>("HighMid Gain",
                                                                "HighMid Gain",
                                                                juce::NormalisableRange<float>(-15.0f, 15.0f, 0.1f, 1.0f),
                                                                0.0f));
    //LowMidPeak Filter --------------------------------------------------------------------------------------
    parameter.add(std::make_unique<juce::AudioParameterFloat>("LowMid Frequency",
                                                                "LowMid Frequency",
                                                                juce::NormalisableRange<float>(200.0f, 2500.0f, 10.0f, 1.0f),
                                                                500.0f));
    parameter.add(std::make_unique<juce::AudioParameterFloat>("LowMid Quality",
                                                                "LowMid Quality",
                                                                juce::NormalisableRange<float>(0.1f, 3.5f, 0.01f, 1.0f),
                                                                1.0f));
    parameter.add(std::make_unique<juce::AudioParameterFloat>("LowMid Gain",
                                                                "LowMid Gain",
                                                                juce::NormalisableRange<float>(-15.0f, 15.0f, 0.1f, 1.0f),
                                                                0.0f));
    //LowShelf Filter --------------------------------------------------------------------------------------
    parameter.add(std::make_unique<juce::AudioParameterFloat>("LowShelf Frequency",
                                                                "LowShelf Frequency",
                                                                juce::NormalisableRange<float>(30.0f, 450.0f, 1.0f, 1.0f),
                                                                60.f));
    parameter.add(std::make_unique<juce::AudioParameterFloat>("LowShelf Quality",
                                                                "LowShelf Quality",
                                                                juce::NormalisableRange<float>(0.1f, 3.5f, 0.01f, 1.0f),
                                                                1.0f));
    parameter.add(std::make_unique<juce::AudioParameterFloat>("LowShelf Gain",
                                                                "LowShelf Gain",
                                                                juce::NormalisableRange<float>(-15.0f, 15.0f, 0.1f, 1.0f),
                                                                0.0f));

    return parameter;
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new _7Band_ParametricEQAudioProcessor();
}
