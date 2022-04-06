//OscComponent.h

//Code for the design of the oscillator.

#pragma once

#include <JuceHeader.h>
#include "CustomComponent.h"

//==============================================================================
/*
*/
class OscComponent : public CustomComponent
{
public:
    OscComponent(juce::AudioProcessorValueTreeState& apvts,
        juce::String&& oscTypeId, juce::String&& gainId, juce::String&& pitchId, juce::String&& detuneId, juce::String&& distortionID,
        juce::String&& fmTypeId, juce::String&& fmFreqId, juce::String&& fmDepthId, juce::String&& nObertonesId,
        juce::String&& panId, juce::String&& unisonID);
    ~OscComponent() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    juce::ComboBox oscSelector;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> oscSelAttachment;
    juce::ComboBox fmTypeSelector;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> fmTypeSelectorlAttachment;
    
    using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    void setSliderWithLabel(juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts,
        juce::String parameterID, std::unique_ptr<Attachment>& sliderAttachment);

    //Each of the Slider
    juce::Slider gainSlider;
    juce::Slider pitchSlider;
    juce::Slider detuneSlider;
    juce::Slider distortionSlider;
    juce::Slider fmFreqSlider;
    juce::Slider fmDepthSlider;
    juce::Slider nObertonesSlider;
    juce::Slider panSlider;
    juce::Slider unisonSlider;

    //Each of the label
    juce::Label gainLabel{ "Gain", "Gain" };
    juce::Label pitchLabel{ "Pitch", "Pitch" };
    juce::Label detuneLabel{ "Detune", "Detune" };
    juce::Label distortionLabel{ "Distortion", "Distortion" };
    juce::Label fmFreqLabel{ "FmFreq", "FmFreq" };
    juce::Label fmDepthLabel{ "FmDepth", "FmDepth" };
    juce::Label nObertonesLabel{ "Nobertone", "Nobertone" };
    juce::Label panLabel{ "Pan", "Pan" };
    juce::Label unisonLabel{ "Unison", "Unison" };

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gainSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> pitchSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> detuneSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> distortionSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> fmFreqSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> fmDepthSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> nObertonesSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> panSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> unisonSliderAttachment;

    //Default size of the slider
    static constexpr int dialWidth = 64;
    static constexpr int dialHeight = 64;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OscComponent)
};