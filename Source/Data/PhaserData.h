// PhaserData.h

// For 'Phaser(Effector)' of the synthesiser 

#pragma once

#include <JuceHeader.h>

class PhaserData
{
public:
    void prepare(const juce::dsp::ProcessSpec& spec);
    // Knobs for Rate, Depth, Centre Delay, Feedback, Mix value
    void setPhaserParameters(const float rate, const float depth, const float centerFreq,
        const float fdbk, const float mix);
    void process(juce::AudioBuffer<float>& buffer);
    void reset();

private:
    juce::dsp::Phaser<float> phaser;
    bool isPrepared{ false };
};
