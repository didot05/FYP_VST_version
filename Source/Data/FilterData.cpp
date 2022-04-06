//FilterData.cpp

// For 'Filter (Amplifier)' of the synthesiser

#include "FilterData.h"
FilterData::FilterData()
{
    setType(juce::dsp::StateVariableTPTFilterType::lowpass);
}

void FilterData::setParams(const int filterType, const float filterCutoff, const float filterResonance)
{
    selectFilterType(filterType);
    //set the cut of frequency value
    setCutoffFrequency(filterCutoff);
    setResonance(filterResonance);
}

void FilterData::setLfoParams(const float freq, const float depth)
{
    //    lfoGain = juce::Decibels::gainToDecibels (depth);
    //    lfo.setFrequency (freq);
}

void FilterData::prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels)
{
    resetAll();
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = outputChannels;
    prepare(spec);
}


void FilterData::selectFilterType(const int filterType)
{
    switch (filterType)
    {
        //low-pass filter
    case 0:
        setType(juce::dsp::StateVariableTPTFilterType::lowpass);
        break;
        //band-pass filter    
    case 1:
        setType(juce::dsp::StateVariableTPTFilterType::bandpass);
        break;
        //high-pass filter    
    case 2:
        setType(juce::dsp::StateVariableTPTFilterType::highpass);
        break;
        // Default : low-pass filter (the most famous filter for subtractive synthesiser)
    default:
        setType(juce::dsp::StateVariableTPTFilterType::lowpass);
        break;
    }
}

void FilterData::processNextBlock(juce::AudioBuffer<float>& buffer)
{
    juce::dsp::AudioBlock<float> block{ buffer };
    process(juce::dsp::ProcessContextReplacing<float>(block));
}

float FilterData::processNextSample(int channel, float inputValue)
{
    return processSample(channel, inputValue);
}

void FilterData::resetAll()
{
    reset();
    lfo.reset();
}
