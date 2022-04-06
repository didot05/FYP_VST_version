//PluginEditor.h


#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "UI/OscComponent.h"
#include "UI/FilterComponent.h"
#include "UI/AdsrComponent.h"
#include "UI/ChorusComponent.h"
#include "UI/CompressorComponent.h"
#include "UI/PhaserComponent.h"
#include "UI/ReverbComponent.h"
#include "UI/MeterComponent.h"
#include "UI/OtherLookAndFeel.h"

using namespace juce;
using namespace std;
//==============================================================================
/**
*/
class SynthAudioProcessorEditor  : public juce::AudioProcessorEditor
, public juce::Timer
{
public:
    SynthAudioProcessorEditor (SynthAudioProcessor&);
    ~SynthAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
    void timerCallback() override;

	void hostMIDIControllerIsAvailable(bool) override;

private:

    SynthAudioProcessor& audioProcessor;
    OscComponent osc1;
    OscComponent osc2;
    FilterComponent filter;
    AdsrComponent adsr;
    ChorusComponent chorus;
    CompressorComponent compreData;
    PhaserComponent phaser;
    AdsrComponent filterAdsr;
    ReverbComponent reverb;
    MeterComponent meter;
	//=====================================
    //Help Button
    vector<string> buttonTexts = {
        "Help",
        "Compressor",
        "Phaser",
        "Chorus",
        "Reverb",
        "Osc",
        "Filter",
        "ADSR",
    };
    vector<unique_ptr<TextButton> > openDialogButtons;

    OtherLookAndFeel otherLookAndFeel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthAudioProcessorEditor)
};
