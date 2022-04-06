//CompressorComponent.cpp

//Code for the design of the Compressor.

#include <JuceHeader.h>
#include "CompressorComponent.h"

//==============================================================================
CompressorComponent::CompressorComponent(juce::AudioProcessorValueTreeState& apvts, juce::String thresholdID,
    juce::String ratioID, juce::String attackID, juce::String releaseID)
{
    setSliderWithLabel(thresholdSlider, thresholdLabel, apvts, thresholdID, thresholdSliderAttachment);
    setSliderWithLabel(ratioSlider, ratioLabel, apvts, ratioID, ratioSliderAttachment);
    setSliderWithLabel(attackSlider, attackLabel, apvts, attackID, attackSliderAttachment);
    setSliderWithLabel(releaseSlider, releaseLabel, apvts, releaseID, releaseSliderAttachment);
}

CompressorComponent::~CompressorComponent()
{
}

//Color the each of the Compressor slider
void CompressorComponent::paint(juce::Graphics& g)
{
    auto bounds = getLocalBounds();
    g.setColour(juce::Colour::fromRGB(25, 25, 25));
    g.drawRoundedRectangle(bounds.toFloat().reduced(10.0f), 4.0f, 3.0f);
    g.fillRoundedRectangle(bounds.getX() + 5, bounds.getY() + 5, bounds.getWidth() - 10,
        bounds.getHeight() - 10, 5.0f);
    g.setColour(juce::Colour::fromRGB(15, 199, 149));
    g.setFont(15);
    g.setFont(g.getCurrentFont().boldened());
    g.drawText("Compressor", 20, 15, 100, 25, juce::Justification::left);
}

//Give the size and position value to the each of Compressor slider
void CompressorComponent::resized()
{
    const auto startYPos = 55;
    const auto sliderWidth = 60; 
    const auto sliderHeight = 90;
    const auto labelYOffset = 20;
    const auto labelHeight = 20;

    thresholdSlider.setBounds(20, startYPos, sliderWidth, sliderHeight);
    thresholdLabel.setBounds(thresholdSlider.getX(), thresholdSlider.getY() - labelYOffset,
        thresholdSlider.getWidth(), labelHeight);
    ratioSlider.setBounds(thresholdSlider.getRight(), startYPos, sliderWidth, sliderHeight);
    ratioLabel.setBounds(ratioSlider.getX(), ratioSlider.getY() - labelYOffset,
        ratioSlider.getWidth(), labelHeight);
    attackSlider.setBounds(ratioSlider.getRight(), startYPos, sliderWidth, sliderHeight);
    attackLabel.setBounds(attackSlider.getX(), attackSlider.getY() - labelYOffset,
        attackSlider.getWidth(), labelHeight);
    releaseSlider.setBounds(attackSlider.getRight(), startYPos, sliderWidth, sliderHeight);
    releaseLabel.setBounds(releaseSlider.getX(), releaseSlider.getY() - labelYOffset,
        releaseSlider.getWidth(), labelHeight);
}

using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;
// Attach the each proper label for the each of Compressor slider
void CompressorComponent::setSliderWithLabel(juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts,
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

