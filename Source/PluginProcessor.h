#pragma once

#include <JuceHeader.h>
#include "Synth_Voice.h"
#include "Synth_Sound.h"
#include "Data/ChorusData.h"
#include "Data/CompressorData.h"
#include "Data/PhaserData.h"

//==============================================================================
/**
*/
class SynthAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    SynthAudioProcessor();
    ~SynthAudioProcessor() override;

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
    
    juce::AudioBuffer<float>& getAudioBufferCopy() { return audioBufferCopy; }
    juce::AudioProcessorValueTreeState apvts;


private:
    static constexpr int numChannelsToProcess{ 2 };
    juce::Synthesiser synth;

    juce::AudioProcessorValueTreeState::ParameterLayout createParams();
    //Set each parameter values of the synthesiser (Filter, Effectors)
    void setParams();
    void setVoiceParams();
    void setFilterParams();
    void setReverbParams();

    void setChorusParams();
    void setCompeDataParams();
    void setPhaserParams();

    static constexpr int numVoices{ 5 };
    juce::dsp::Reverb reverb;
    juce::Reverb::Parameters reverbParams;

    ChorusData chorus;
    CompressorData compreData;
    PhaserData phaser;

    juce::AudioBuffer<float> audioBufferCopy;
    //================= Delay =====================
    juce::AudioBuffer<float> delayBuffer;
    void applyDelay(juce::AudioBuffer<float>& buffer, juce::AudioBuffer<float>& delayBuffer, float delayLevel);
    int delayPosition = 0;
    float delayLevel = 0.f;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthAudioProcessor)
};