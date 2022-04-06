// PhaserComponent.h

//Code for the design of the Phaser.

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class PhaserComponent : public juce::Component
{
public:
    PhaserComponent(juce::AudioProcessorValueTreeState& apvts, juce::String rateID,
        juce::String depthID, juce::String centerFreqID, juce::String fdbkID, juce::String mixID);
    ~PhaserComponent() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    void setSliderWithLabel(juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts,
        juce::String parameterID, std::unique_ptr<Attachment>& sliderAttachment);

    //Each of the Slider
    juce::Slider rateSlider;
    juce::Slider depthSlider;
    juce::Slider centerFreqSlider;
    juce::Slider fdbkSlider;
    juce::Slider mixSlider;
    
    //Each of the label
    juce::Label rateLabel{ "Rate", "Rate" };
    juce::Label depthLabel{ "Depth", "Depth" };
    juce::Label centerFreqLabel{ "Center Freq", "Center Freq" };
    juce::Label fdbkLabel{ "Feedback", "Feedback" };
    juce::Label mixLabel{ "Mix", "Mix" };
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> rateSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> depthSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> centerFreqSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> fdbkSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mixSliderAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PhaserComponent)
};
