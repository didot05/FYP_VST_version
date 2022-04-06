//MeterComponent.h

//Code for the design of the Meter(oscilloscope).

#pragma once

#include "../PluginProcessor.h"
#include "CustomComponent.h"

//==============================================================================
/*
*/
class MeterComponent  : public CustomComponent
{
public:
    MeterComponent (SynthAudioProcessor& p);
    ~MeterComponent() override;

    void paint(juce::Graphics&) override;
    void paintOverChildren (juce::Graphics& g) override;
    void resized() override;

private:
    SynthAudioProcessor& audioProcessor;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MeterComponent)
};
