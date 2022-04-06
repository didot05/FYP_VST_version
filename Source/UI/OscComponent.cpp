//OscComponent.cpp

//Code for the design of the oscillator.

#include "OscComponent.h"

extern juce::StringArray oscTypes;
//==============================================================================
OscComponent::OscComponent(juce::AudioProcessorValueTreeState& apvts,
	juce::String&& oscTypeId, juce::String&& gainId, juce::String&& pitchId, juce::String&& detuneId, juce::String&& distortionId,
	juce::String&& fmTypeId, juce::String&& fmFreqId, juce::String&& fmDepthId, juce::String&& nObertonesId,
	juce::String&& panId, juce::String&& unisonId)

{
	//juce::StringArray oscChoices { "Sine", "Saw", "Square", "Triangle", "Noice", "Saw smooth" };
	oscSelector.addItemList(oscTypes, 1);
	oscSelector.setSelectedItemIndex(0);
	addAndMakeVisible(oscSelector);

	fmTypeSelector.addItemList(oscTypes, 1);
	fmTypeSelector.setSelectedItemIndex(0);
	addAndMakeVisible(fmTypeSelector);

	//oscSelector - combo box
	oscSelector.setColour(juce::ComboBox::backgroundColourId, juce::Colour::fromRGB(63, 33, 89));
	oscSelector.setColour(juce::ComboBox::textColourId, juce::Colour::fromRGB(15, 199, 149));
	oscSelector.setColour(juce::ComboBox::arrowColourId, juce::Colour::fromRGB(15, 199, 149));
	//fmTypeSelector - combo box
	fmTypeSelector.setColour(juce::ComboBox::backgroundColourId, juce::Colour::fromRGB(63, 33, 89));
	fmTypeSelector.setColour(juce::ComboBox::textColourId, juce::Colour::fromRGB(15, 199, 149));
	fmTypeSelector.setColour(juce::ComboBox::arrowColourId, juce::Colour::fromRGB(15, 199, 149));

	oscSelAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, oscTypeId, oscSelector);
	fmTypeSelectorlAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, fmTypeId, fmTypeSelector);

	setSliderWithLabel(gainSlider, gainLabel, apvts, gainId, gainSliderAttachment);
	setSliderWithLabel(pitchSlider, pitchLabel, apvts, pitchId, pitchSliderAttachment);
	setSliderWithLabel(detuneSlider, detuneLabel, apvts, detuneId, detuneSliderAttachment);
	setSliderWithLabel(distortionSlider, distortionLabel, apvts, distortionId, distortionSliderAttachment);
	setSliderWithLabel(fmFreqSlider, fmFreqLabel, apvts, fmFreqId, fmFreqSliderAttachment);
	setSliderWithLabel(fmDepthSlider, fmDepthLabel, apvts, fmDepthId, fmDepthSliderAttachment);
	setSliderWithLabel(nObertonesSlider, nObertonesLabel, apvts, nObertonesId, nObertonesSliderAttachment);
	setSliderWithLabel(panSlider, panLabel, apvts, panId, panSliderAttachment);
	setSliderWithLabel(unisonSlider, unisonLabel, apvts, unisonId, unisonSliderAttachment);

	setName("OSC");
}

OscComponent::~OscComponent()
{
}

//Color the each of the Oscillator slider
void OscComponent::paint(juce::Graphics& g)
{
	auto bounds = getLocalBounds();
	g.setColour(juce::Colour::fromRGB(25, 25, 25));
	g.drawRoundedRectangle(bounds.toFloat().reduced(10.0f), 4.0f, 3.0f);
	g.fillRoundedRectangle(bounds.getX() + 5, bounds.getY() + 5, bounds.getWidth() - 10,
		bounds.getHeight() - 10, 5.0f);
	//
	g.setColour(juce::Colour::fromRGB(15, 199, 149));
	g.setFont(15);
	g.setFont(g.getCurrentFont().boldened());
	g.drawText("OSC", 20, 10, 100, 25, juce::Justification::left);
}

//Give the size and position value to the each of Oscillator slider
void OscComponent::resized()
{
	const auto paddingX = 25; 
	const auto paddingY = 35; 
	const auto sliderWidth = 60; 
	const auto sliderHeight = 80; 
	const auto labelYOffset = 10;
	const auto labelHeight = 10;

	oscSelector.setBounds(paddingX, paddingY + 10, 100, 25);
	fmTypeSelector.setBounds(paddingX, oscSelector.getBottom() + 15, 100, 25);

	gainSlider.setBounds(oscSelector.getRight(), paddingY, sliderWidth, sliderHeight);
	gainLabel.setBounds(gainSlider.getX(), gainSlider.getY() - labelYOffset,
		gainSlider.getWidth(), labelHeight);
	pitchSlider.setBounds(gainSlider.getRight(), paddingY, sliderWidth, sliderHeight);
	pitchLabel.setBounds(pitchSlider.getX(), pitchSlider.getY() - labelYOffset,
		pitchSlider.getWidth(), labelHeight);
	detuneSlider.setBounds(pitchSlider.getRight(), paddingY, sliderWidth, sliderHeight);
	detuneLabel.setBounds(detuneSlider.getX(), detuneSlider.getY() - labelYOffset,
		detuneSlider.getWidth(), labelHeight);
	distortionSlider.setBounds(detuneSlider.getRight(), paddingY, sliderWidth, sliderHeight);
	distortionLabel.setBounds(distortionSlider.getX(), distortionSlider.getY() - labelYOffset,
		distortionSlider.getWidth(), labelHeight);
	panSlider.setBounds(paddingX, gainSlider.getBottom() + 20, sliderWidth, sliderHeight + 4);
	panLabel.setBounds(panSlider.getX(), gainSlider.getBottom() + 5,
		panSlider.getWidth(), labelHeight);
	fmFreqSlider.setBounds(fmTypeSelector.getRight(), gainSlider.getBottom() + 10, sliderWidth, sliderHeight + 20);
	fmFreqLabel.setBounds(fmFreqSlider.getX(), fmFreqSlider.getY() - 5,
		fmFreqSlider.getWidth(), labelHeight);
	fmDepthSlider.setBounds(gainSlider.getRight(), gainSlider.getBottom() + 10, sliderWidth, sliderHeight + 20);
	fmDepthLabel.setBounds(fmDepthSlider.getX(), fmDepthSlider.getY() - 5,
		fmDepthSlider.getWidth(), labelHeight);
	unisonSlider.setBounds(fmDepthSlider.getRight(), gainSlider.getBottom() + 10, sliderWidth, sliderHeight + 20);
	unisonLabel.setBounds(unisonSlider.getX(), unisonSlider.getY() - 5,
		unisonSlider.getWidth(), labelHeight);
	nObertonesSlider.setBounds(detuneSlider.getRight(), gainSlider.getBottom() + 10, sliderWidth, sliderHeight + 20);
	nObertonesLabel.setBounds(nObertonesSlider.getX(), nObertonesSlider.getY() - 5,
		nObertonesSlider.getWidth(), labelHeight);
}


using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;
// Attach the each proper label for the each of Oscillator slider
void OscComponent::setSliderWithLabel(juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts,
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
