//CompressorData.cpp

// For 'Compressor (Effector)' of the synthesiser

#include "CompressorData.h"

void CompressorData::prepare(const juce::dsp::ProcessSpec& spec)
{
    comp.prepare(spec);
    isPrepared = true;
}

void CompressorData::setCompressorParameters(const float threshold, const float ratio,
    const float attack, const float release)
{
    // Set the values for Threshold, Ratio, Attack, Release
    comp.setThreshold(threshold);
    comp.setRatio(ratio);
    comp.setAttack(attack);
    comp.setRelease(release);
}

void CompressorData::process(juce::AudioBuffer<float>& buffer)
{
    jassert(isPrepared);
    juce::dsp::AudioBlock<float> block(buffer);
    comp.process(juce::dsp::ProcessContextReplacing<float>(block));
}

void CompressorData::reset()
{
    comp.reset();
}


