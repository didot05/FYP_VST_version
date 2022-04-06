//ReverbComponent.cpp

//Code for the design of the Reverb.

#include "ReverbComponent.h"

//==============================================================================
ReverbComponent::ReverbComponent(juce::AudioProcessorValueTreeState& apvts, 
    juce::String sizeId, juce::String dampingId, juce::String widthId, juce::String dryId, 
    juce::String wetId, juce::String freezeId, juce::String delayId)
{
    setSliderWithLabel(sizeSlider, sizeLabel, apvts, sizeId, sizeSliderAttachment);
    setSliderWithLabel(dampingSlider, dampingLabel, apvts, dampingId, dampingSliderAttachment);
    setSliderWithLabel(stereoWidthSlider, stereoWidthLabel, apvts, widthId, stereoWidthSliderAttachment);
    setSliderWithLabel(drySlider, dryLabel, apvts, dryId, drySliderAttachment);
    setSliderWithLabel(wetSlider, wetLabel, apvts, wetId, wetSliderAttachment);
    setSliderWithLabel(freezeSlider, freezeLabel, apvts, freezeId, freezeSliderAttachment);
    setSliderWithLabel(delaySlider, delayLabel, apvts, delayId, delaySliderAttachment);
    setName("Reverb");
}

ReverbComponent::~ReverbComponent()
{
}

//Color the each of the Reverb slider
void ReverbComponent::paint(juce::Graphics& g)
{
    auto bounds = getLocalBounds();
    g.setColour(juce::Colour::fromRGB(25, 25, 25)); //
    g.drawRoundedRectangle(bounds.toFloat().reduced(10.0f), 4.0f, 3.0f);
    g.fillRoundedRectangle(bounds.getX() + 5, bounds.getY() + 5, bounds.getWidth() - 10,
        bounds.getHeight() - 10, 5.0f);
    g.setColour(juce::Colour::fromRGB(15, 199, 149));
    g.setFont(15);
    g.setFont(g.getCurrentFont().boldened());
    g.drawText("Reverb", 20, 15, 100, 25, juce::Justification::left);
}

//Give the size and position value to the each of Reverb slider
void ReverbComponent::resized()
{
    const auto yStart = 50;
    const auto width = 60;
    const auto height = 88;
    const auto labelYOffset = 15;
    const auto labelHeight = 20;

    sizeSlider.setBounds(8, yStart, width, height);
    sizeLabel.setBounds(sizeSlider.getX(), sizeSlider.getY() - labelYOffset,
        sizeSlider.getWidth(), labelHeight);
    dampingSlider.setBounds(sizeSlider.getRight(), yStart, width, height);
    dampingLabel.setBounds(dampingSlider.getX(), dampingSlider.getY() - labelYOffset,
        dampingSlider.getWidth(), labelHeight);
    stereoWidthSlider.setBounds(dampingSlider.getRight(), yStart, width, height);
    stereoWidthLabel.setBounds(stereoWidthSlider.getX(), stereoWidthSlider.getY() - labelYOffset,
        stereoWidthSlider.getWidth(), labelHeight);
    drySlider.setBounds(stereoWidthSlider.getRight(), yStart, width, height);
    dryLabel.setBounds(drySlider.getX(), drySlider.getY() - labelYOffset,
        drySlider.getWidth(), labelHeight);
    wetSlider.setBounds(drySlider.getRight(), yStart, width, height);
    wetLabel.setBounds(wetSlider.getX(), wetSlider.getY() - labelYOffset,
        wetSlider.getWidth(), labelHeight);
    freezeSlider.setBounds(wetSlider.getRight(), yStart, width, height);
    freezeLabel.setBounds(freezeSlider.getX(), freezeSlider.getY() - labelYOffset,
        freezeSlider.getWidth(), labelHeight);
    delaySlider.setBounds(freezeSlider.getRight(), yStart, width, height);
    delayLabel.setBounds(delaySlider.getX(), delaySlider.getY() - labelYOffset,
        delaySlider.getWidth(), labelHeight);
}

using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;
// Attach the each proper label for the each of Reverb slider
void ReverbComponent::setSliderWithLabel(juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts,
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