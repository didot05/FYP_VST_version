//AdsrComponent.h

//Code for the design of the Envelope.

#pragma once

#include "CustomComponent.h"

//==============================================================================
/*
*/
class AdsrComponent : public CustomComponent
{
public:
    AdsrComponent (juce::AudioProcessorValueTreeState& apvts, juce::String attackId, juce::String decayId, juce::String sustainId, juce::String releaseId);
    ~AdsrComponent() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    void setSliderWithLabel(juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts,
        juce::String parameterID, std::unique_ptr<Attachment>& sliderAttachment);

    //Each of the Slider
    juce::Slider attackSlider;
    juce::Slider decaySlider;
    juce::Slider sustainSlider;
    juce::Slider releaseSlider;

    //Each of the label
    juce::Label attackLabel{ "Attack", "Attack" };
    juce::Label decayLabel{ "Decay", "Decay" };
    juce::Label sustainLabel{ "Sustain", "Sustain" };
    juce::Label releaseLabel{ "Release", "Release" };

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attackSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> decaySliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sustainSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> releaseSliderAttachment;
    
    //Default size of the slider
    static constexpr int sliderWidth = 50;
    static constexpr int sliderHeight = 100;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AdsrComponent)
};
