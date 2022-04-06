//CompressorData.h

// For 'Compressor (Effector)' of the synthesiser

#pragma once

#include <JuceHeader.h>

class CompressorData
{
public:
    void prepare(const juce::dsp::ProcessSpec& spec);
    // Knobs for Threshold, Ratio, Attack, Release
    void setCompressorParameters(const float threshold, const float ratio,
        const float attack, const float release);
    void process(juce::AudioBuffer<float>& buffer);
    void reset();

private:
    juce::dsp::Compressor<float> comp;
    bool isPrepared{ false };
};

