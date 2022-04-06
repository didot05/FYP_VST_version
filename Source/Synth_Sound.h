//SynthSound.h


#pragma once

#include <JuceHeader.h>

class SynthSound : public juce::SynthesiserSound
{
public:
    bool appliesToNote(int midiNoteNumber) override { return true; }
    // if this sound should be played when a given midi note is pressed
    bool appliesToChannel(int midiChannel) override { return true; }
    //if the sound should be triggered by midi events on a given channel
};
