// PhaserData.cpp

// For 'Phaser(Effector)' of the synthesiser 

#include "PhaserData.h"

void PhaserData::prepare(const juce::dsp::ProcessSpec& spec)
{
    phaser.prepare(spec);
    isPrepared = true;
}

void PhaserData::setPhaserParameters(const float rate, const float depth, const float centerFreq,
    const float fdbk, const float mix)
{
    // Set the values for Rate, Depth, Centre Delay, Feedback, Mix
    phaser.setRate(rate);
    phaser.setDepth(depth);
    phaser.setCentreFrequency(centerFreq);
    phaser.setFeedback(fdbk);
    phaser.setMix(mix);
}

void PhaserData::process(juce::AudioBuffer<float>& buffer)
{
    jassert(isPrepared);
    juce::dsp::AudioBlock<float> block(buffer);
    phaser.process(juce::dsp::ProcessContextReplacing<float>(block));
}

void PhaserData::reset()
{
    phaser.reset();
}


