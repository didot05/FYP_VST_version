//FilterComponent.cpp

//Code for the design of the Filter.

#include "FilterComponent.h"

//==============================================================================
FilterComponent::FilterComponent (juce::AudioProcessorValueTreeState& apvts, 
    juce::String filterTypeId, juce::String cutoffId, juce::String resonanceId)
{
    juce::StringArray filterTypeChoices { "Low Pass", "Band Pass", "High Pass" };
    filterTypeSelector.addItemList (filterTypeChoices, 1);
    filterTypeSelector.setSelectedItemIndex (0);
    addAndMakeVisible (filterTypeSelector);

    filterTypeSelector.setColour(juce::ComboBox::backgroundColourId, juce::Colour::fromRGB(63, 33, 89));
    filterTypeSelector.setColour(juce::ComboBox::textColourId, juce::Colour::fromRGB(15, 199, 149));
    filterTypeSelector.setColour(juce::ComboBox::arrowColourId, juce::Colour::fromRGB(15, 199, 149));

    filterTypeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, filterTypeId, filterTypeSelector);
    
    setSliderWithLabel(cutoffSlider, cutoffLabel, apvts, cutoffId, cutoffSliderAttachment);
    setSliderWithLabel(resonanceSlider, resonanceLabel, apvts, resonanceId, resonanceSliderAttachment);
}

FilterComponent::~FilterComponent()
{
}

//Color the each of the Filter slider
void FilterComponent::paint(juce::Graphics& g)
{
    auto bounds = getLocalBounds();
    g.setColour(juce::Colour::fromRGB(25, 25, 25));
    g.drawRoundedRectangle(bounds.toFloat().reduced(10.0f), 4.0f, 3.0f);
    g.fillRoundedRectangle(bounds.getX() + 5, bounds.getY() + 5, bounds.getWidth() - 10,
        bounds.getHeight() - 10, 5.0f);
    g.setColour(juce::Colour::fromRGB(15, 199, 149));
    g.setFont(15);
    g.setFont(g.getCurrentFont().boldened());
    g.drawText("Filter", 20, 15, 100, 25, juce::Justification::left);
}

//Give the size and position value to the each of Filter slider
void FilterComponent::resized()
{
    const auto startX = 18;
    const auto startY = 90;
    const auto width = 70;
    const auto height = 88;
    const auto labelYOffset = 20;
    const auto labelHeight = 20;

    filterTypeSelector.setBounds (18, 40, 145, 25);

    cutoffSlider.setBounds(startX, startY, width, height);
    cutoffLabel.setBounds(cutoffSlider.getX(), cutoffSlider.getY() - labelYOffset,
        cutoffSlider.getWidth(), labelHeight);
    resonanceSlider.setBounds(cutoffSlider.getRight(), startY, width, height);
    resonanceLabel.setBounds(resonanceSlider.getX(), resonanceSlider.getY() - labelYOffset,
        resonanceSlider.getWidth(), labelHeight);
}


using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;
// Attach the each proper label for the each of Filter slider
void FilterComponent::setSliderWithLabel(juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts,
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


