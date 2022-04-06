//AdsrComponent.cpp

//Code for the design of the Envelope.

#include <JuceHeader.h>
#include "AdsrComponent.h"

//==============================================================================
AdsrComponent::AdsrComponent (juce::AudioProcessorValueTreeState& apvts, 
    juce::String attackId, juce::String decayId, juce::String sustainId, juce::String releaseId)
{
    setSliderWithLabel(attackSlider, attackLabel, apvts, attackId, attackSliderAttachment);
    setSliderWithLabel(decaySlider, decayLabel, apvts, decayId, decaySliderAttachment);
    setSliderWithLabel(sustainSlider, sustainLabel, apvts, sustainId, sustainSliderAttachment);
    setSliderWithLabel(releaseSlider, releaseLabel, apvts, releaseId, releaseSliderAttachment);
}

AdsrComponent::~AdsrComponent()
{
}

//Color the each of the ADSR slider
void AdsrComponent::paint(juce::Graphics& g)
{
    auto bounds = getLocalBounds();
    g.setColour(juce::Colour::fromRGB(25, 25, 25));
    g.drawRoundedRectangle(bounds.toFloat().reduced(10.0f), 4.0f, 3.0f);
    g.fillRoundedRectangle(bounds.getX() + 5, bounds.getY() + 5, bounds.getWidth() - 10,
        bounds.getHeight() - 10, 5.0f);
    g.setColour(juce::Colour::fromRGB(15, 199, 149));
    g.setFont(15);
    g.setFont(g.getCurrentFont().boldened());
    g.drawText("ADSR", 20, 15, 100, 25, juce::Justification::left);
}

//Give the size and position value to the each of ADSR slider
void AdsrComponent::resized()
{
    const auto startX = 15;
    const auto startY = 55;
    const auto width = sliderWidth + 3;
    const auto height = sliderHeight + 20;
    const auto labelYOffset = 10;
    const auto labelHeight = 10;

    attackSlider.setBounds(startX, startY, width, height);
    attackLabel.setBounds(attackSlider.getX(), attackSlider.getY() - labelYOffset,
        attackSlider.getWidth(), labelHeight);
    decaySlider.setBounds(attackSlider.getRight(), startY, width, height);
    decayLabel.setBounds(decaySlider.getX(), decaySlider.getY() - labelYOffset,
        decaySlider.getWidth(), labelHeight);
    sustainSlider.setBounds(decaySlider.getRight(), startY, width, height);
    sustainLabel.setBounds(sustainSlider.getX(), sustainSlider.getY() - labelYOffset,
        sustainSlider.getWidth(), labelHeight);
    releaseSlider.setBounds(sustainSlider.getRight(), startY, width, height);
    releaseLabel.setBounds(releaseSlider.getX(), releaseSlider.getY() - labelYOffset,
        releaseSlider.getWidth(), labelHeight);

}

using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;
// Attach the each proper label for the each of ADSR slider
void AdsrComponent::setSliderWithLabel(juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts,
    juce::String parameterID, std::unique_ptr<Attachment>& sliderAttachment)
{
    slider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    slider.setColour(juce::Slider::ColourIds::textBoxTextColourId, juce::Colour::fromRGB(255, 201, 71));
    addAndMakeVisible(slider);

    sliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, parameterID, slider);
    //Attach the label
    label.setColour(juce::Label::ColourIds::textColourId, juce::Colour::fromRGB(15, 199, 149));
    label.setFont(15.0f);
    label.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(label);
    
    slider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colour::fromRGB(63, 33, 89));
    slider.setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colour::fromRGB(33, 33, 33));
    slider.setColour(juce::Slider::thumbColourId, juce::Colour::fromRGB(25, 25, 25));
    slider.setColour(juce::Slider::trackColourId, juce::Colour::fromRGB(24, 35, 52));
    slider.setColour(juce::Slider::ColourIds::textBoxTextColourId, juce::Colour::fromRGB(15, 199, 149));
    slider.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colour::fromRGB(63, 33, 89));
}


