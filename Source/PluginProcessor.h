// ==============================================================================

#pragma once
#include <JuceHeader.h>

enum Slope
{
    Slope_12,
    Slope_24,
    Slope_36,
    Slope_48
};

struct ChainSettings
{
    float lowCutFrequency{ 0 }, highCutFrequency{ 0 };
    float highShelfFrequency{ 0 }, highShelfGainInDecibels{ 0 }, highShelfQuality{ 1.f };
    float highMidFrequency{ 0 }, highMidGainInDecibels{ 0 }, highMidQuality{ 1.f };
    float lowMidFrequency{ 0 }, lowMidGainInDecibels{ 0 }, lowMidQuality{ 1.f };
    float lowShelfFrequency{ 0 }, lowShelfGainInDecibels{ 0 }, lowShelfQuality{ 1.f };
    float inputGain{ 0 }, outputGain{ 0 };

    bool phase{ false };
    bool highShelfToBell{ false }, lowShelfToBell{ false };
    bool lowCutBypassed{ false }, highCutBypassed{ false },
            highShelfBypassed{ false }, lowShelfBypassed{ false },
            highMidBypassed{ false }, lowMidBypassed{ false };

    Slope lowCutSlope{ Slope::Slope_12 }, highCutSlope{ Slope::Slope_12 };
};

ChainSettings getChainSettings(juce::AudioProcessorValueTreeState& ParaEQ);

//==============================================================================

class _7Band_ParametricEQAudioProcessor  : public juce::AudioProcessor
                            #if JucePlugin_Enable_ARA
                             , public juce::AudioProcessorARAExtension
                            #endif
{
public:
    //==============================================================================
    _7Band_ParametricEQAudioProcessor();
    ~_7Band_ParametricEQAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    //==============================================================================    
    static juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    juce::AudioProcessorValueTreeState ParaEQ {*this, nullptr, "Parameters", createParameterLayout() };

    float getRmsValue(const int channel) const;

private:
    using Filter = juce::dsp::IIR::Filter<float>;
    using CutFilter = juce::dsp::ProcessorChain<Filter, Filter, Filter, Filter, Filter, Filter>;
    using MonoChain = juce::dsp::ProcessorChain<CutFilter, Filter, Filter, Filter, Filter, CutFilter>;

    MonoChain leftChain, rightChain;

    enum ChainPositions
    {
        HighCut,
        HighShelf,
        HighMid,        
        LowMid,
        LowShelf,
        LowCut
    };
    
    //updating Filters
    void updateHighShelfFilter(const ChainSettings& chainSettings);
    void updateHighMidFilter(const ChainSettings& chainSettings);
    void updateLowMidFilter(const ChainSettings& chainSettings);
    void updateLowShelfFilter(const ChainSettings& chainSettings);


    //updating Fiter Coefficients
    using Coefficients = Filter::CoefficientsPtr;
    static void updateCoefficients(Coefficients& old, const Coefficients& replacements);

    //LowCut Filter Refactoring
    template<int Index, typename ChainType, typename CoefficientType>
    void update(ChainType& chain, const CoefficientType& slopeCoefficients)
    {
        updateCoefficients(chain.template get<Index>().coefficients, slopeCoefficients[Index]);
        chain.template setBypassed<Index>(false);
    }

    template<typename ChainType, typename CoefficientType>
    void updateCutFilter(ChainType& chain,
        const CoefficientType& slopeCoefficients,
        const Slope& slope)
    {
        chain.template setBypassed<0>(true);
        chain.template setBypassed<1>(true);
        chain.template setBypassed<2>(true);
        chain.template setBypassed<3>(true);

        switch (slope)
        {
            case Slope_48:
            {
                update<3>(chain, slopeCoefficients);
            }
            case Slope_36:
            {
                update<2>(chain, slopeCoefficients);
            }
            case Slope_24:
            {
                update<1>(chain, slopeCoefficients);
            }
            case Slope_12:
            {
                update<0>(chain, slopeCoefficients);
            }
        }
    }

    void updateLowCutFilter(const ChainSettings& chainSettings);
    void updateHighCutFilter(const ChainSettings& chainSettings);

    void updateAllFilters();

    juce::LinearSmoothedValue<float> InputLevelL, InputLevelR;
    juce::LinearSmoothedValue<float> OutputLevelL, OutputLevelR;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (_7Band_ParametricEQAudioProcessor)
};
