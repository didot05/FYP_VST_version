//ReverbComponent.h

//Code for the design of the Reverb.

#pragma once

#include <JuceHeader.h>
#include "CustomComponent.h"

//==============================================================================
/*
*/
class ReverbComponent : public CustomComponent
{
public:
    ReverbComponent(juce::AudioProcessorValueTreeState& apvts, juce::String sizeId, juce::String dampingId, juce::String widthId, juce::String dryId, juce::String wetId, juce::String freezeId, juce::String delayId);
    ~ReverbComponent() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    void setSliderWithLabel(juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts,
        juce::String parameterID, std::unique_ptr<Attachment>& sliderAttachment);

    //Each of the Slider
    juce::Slider sizeSlider;
    juce::Slider dampingSlider;
    juce::Slider stereoWidthSlider;
    juce::Slider drySlider;
    juce::Slider wetSlider;
    juce::Slider freezeSlider;
    juce::Slider delaySlider;

    //Each of the label
    juce::Label sizeLabel{ "Size", "Size" };
    juce::Label dampingLabel{ "Damping", "Damping" };
    juce::Label stereoWidthLabel{ "Width", "Width" };
    juce::Label dryLabel{ "Dry", "Dry" };
    juce::Label wetLabel{ "Wet", "Wet" };
    juce::Label freezeLabel{ "Freeze", "Freeze" };
    juce::Label delayLabel{ "Delay", "Delay" };

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sizeSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> dampingSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> stereoWidthSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> drySliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> wetSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> freezeSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> delaySliderAttachment;

    //Default size of the slider
    static constexpr int dialWidth = 64;
    static constexpr int dialHeight = 64;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ReverbComponent)
};