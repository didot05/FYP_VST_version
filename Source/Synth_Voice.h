//SynthVoice.h


#pragma once

#include "Synth_Sound.h"
#include "Data/OscData.h"
#include "Data/FilterData.h"
#include "Data/AdsrData.h"

class SynthVoice : public juce::SynthesiserVoice
{
public:
    bool canPlaySound(juce::SynthesiserSound* sound) override;
    // this voice object is capable of playing the given sound
    void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) override;
    //Called to start a new note
    void stopNote(float velocity, bool allowTailOff) override;
    //Called to stop a note
    void controllerMoved(int controllerNumber, int newControllerValue) override;
    //Called to let the voice know that a midi controller has been moved
    void pitchWheelMoved(int newPitchWheelValue) override;
    //Called to let the voice know that the pitch wheel has been moved
    void prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels);
    void renderNextBlock(juce::AudioBuffer< float >& outputBuffer, int startSample, int numSamples) override;
    //Renders the next block of data for this voice
    void reset();

    OscData& getOscillator1() { return osc1; }
    OscData& getOscillator2() { return osc2; }
    AdsrData& getAdsr() { return adsr; }
    AdsrData& getFilterAdsr() { return filterAdsr; }
    float getFilterAdsrOutput() { return filterAdsrOutput; }
    void updateFilterParams(const int filterType, const float filterCutoff, const float filterResonance, const float adsrDepth /*const float lfoFreq, const float lfoDepth*/);

private:
    static constexpr int numChannelsToProcess{ 2 };
    // 2 OSC for synthesiser
    OscData osc1;
    OscData osc2;
    // Filter - low-pass(default), band-pass, high-pass
    FilterData filter;
    // Envelope
    AdsrData adsr;
    // Envelope - for filter
    AdsrData filterAdsr;
    juce::AudioBuffer<float> synthBuffer;
    float filterAdsrOutput{ 0.0f };
    bool isPrepared{ false };
    std::array<float, numChannelsToProcess> lfoOutput{ 0.0f, 0.0f };
    std::array<juce::dsp::Oscillator<float>, numChannelsToProcess> lfo;
    juce::dsp::Gain<float> gain;
};
