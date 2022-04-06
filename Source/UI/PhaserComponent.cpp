//PhaserComponent.cpp

//Code for the design of the Phaser.

#include <JuceHeader.h>
#include "PhaserComponent.h"

//==============================================================================
PhaserComponent::PhaserComponent(juce::AudioProcessorValueTreeState& apvts, juce::String rateID,
    juce::String depthID, juce::String centerFreqID, juce::String fdbkID, juce::String mixID)
{
    setSliderWithLabel(rateSlider, rateLabel, apvts, rateID, rateSliderAttachment);
    setSliderWithLabel(depthSlider, depthLabel, apvts, depthID, depthSliderAttachment);
    setSliderWithLabel(centerFreqSlider, centerFreqLabel, apvts, centerFreqID, centerFreqSliderAttachment);
    setSliderWithLabel(fdbkSlider, fdbkLabel, apvts, fdbkID, fdbkSliderAttachment);
    setSliderWithLabel(mixSlider, mixLabel, apvts, mixID, mixSliderAttachment);
}

PhaserComponent::~PhaserComponent()
{
}

//Color the each of the Phaser slider
void PhaserComponent::paint(juce::Graphics& g)
{
    auto bounds = getLocalBounds();
    g.setColour(juce::Colour::fromRGB(25, 25, 25));
    g.drawRoundedRectangle(bounds.toFloat().reduced(10.0f), 4.0f, 3.0f);
    g.fillRoundedRectangle(bounds.getX() + 5, bounds.getY() + 5, bounds.getWidth() - 10,
        bounds.getHeight() - 10, 5.0f);
    g.setColour(juce::Colour::fromRGB(15, 199, 149));
    g.setFont(15);
    g.setFont(g.getCurrentFont().boldened());
    g.drawText("Phaser", 20, 15, 100, 25, juce::Justification::left);
}

//Give the size and position value to the each of Phaser slider
void PhaserComponent::resized()
{
    const auto startYPos = 55;
    const auto sliderWidth = 70; 
    const auto sliderHeight = 90;
    const auto labelYOffset = 20;
    const auto labelHeight = 20;

    rateSlider.setBounds(10, startYPos, sliderWidth, sliderHeight);
    rateLabel.setBounds(rateSlider.getX(), rateSlider.getY() - labelYOffset,
        rateSlider.getWidth(), labelHeight);
    depthSlider.setBounds(rateSlider.getRight(), startYPos, sliderWidth, sliderHeight);
    depthLabel.setBounds(depthSlider.getX(), depthSlider.getY() - labelYOffset,
        depthSlider.getWidth(), labelHeight);
    centerFreqSlider.setBounds(depthSlider.getRight(), startYPos, sliderWidth, sliderHeight);
    centerFreqLabel.setBounds(centerFreqSlider.getX(), centerFreqSlider.getY() - labelYOffset,
        centerFreqSlider.getWidth(), labelHeight);
    fdbkSlider.setBounds(centerFreqSlider.getRight(), startYPos, sliderWidth, sliderHeight);
    fdbkLabel.setBounds(fdbkSlider.getX(), fdbkSlider.getY() - labelYOffset,
        fdbkSlider.getWidth(), labelHeight);
    mixSlider.setBounds(fdbkSlider.getRight(), startYPos, sliderWidth, sliderHeight);
    mixLabel.setBounds(mixSlider.getX(), mixSlider.getY() - labelYOffset,
        mixSlider.getWidth(), labelHeight);
}

using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;
// Attach the each proper label for the each of Phaser slider
void PhaserComponent::setSliderWithLabel(juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts,
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

