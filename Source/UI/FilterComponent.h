//FilterComponent.h

//Code for the design of the Filter.

#pragma once

#include <JuceHeader.h>
#include "CustomComponent.h"

//==============================================================================
/*
*/
class FilterComponent : public CustomComponent
{
public:
    FilterComponent (juce::AudioProcessorValueTreeState& apvts, juce::String filterTypeId, juce::String cutoffId, juce::String resonanceId);
    ~FilterComponent() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    juce::ComboBox filterTypeSelector;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> filterTypeAttachment;
    using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    void setSliderWithLabel(juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts,
        juce::String parameterID, std::unique_ptr<Attachment>& sliderAttachment);

    //Each of the Slider
    juce::Slider cutoffSlider;
    juce::Slider resonanceSlider;

    //Each of the label
    juce::Label cutoffLabel{ "Cut Off", "Cut Off" };
    juce::Label resonanceLabel{ "Resonance", "Resonance" };

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> cutoffSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> resonanceSliderAttachment;
    
    //Default size of the slider
    static constexpr int dialWidth = 70;
    static constexpr int dialHeight = 70;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterComponent)
};
