//ChorusData.h

// For 'Chorus (Effector)' of the synthesiser

#pragma once
#include <JuceHeader.h>

class ChorusData
{
public:
    void prepare(const juce::dsp::ProcessSpec& spec);
    // Knobs for Rate, Depth, Centre Delay, Feedback, Mix value
    void setChorusParameters(const float rate, const float depth, const float centerDelay,
        const float fdbk, const float mix);
    void process(juce::AudioBuffer<float>& buffer);
    void reset();

private:
    juce::dsp::Chorus<float> chorus;
    bool isPrepared{ false };
};