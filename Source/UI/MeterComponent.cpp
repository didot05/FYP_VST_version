//MeterComponent.cpp

//Code for the design of the Meter(oscilloscope).

#include "MeterComponent.h"

//==============================================================================
MeterComponent::MeterComponent (SynthAudioProcessor& p) : audioProcessor (p)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

MeterComponent::~MeterComponent()
{
}

inline float scale(float v, float a, float b, float x, float y) {
	return (v - a) / (b - a) * (y - x) + x;
}

void MeterComponent::paintOverChildren(juce::Graphics& g)
{
	  //===============================================
	
	auto buffer = audioProcessor.getAudioBufferCopy();
	auto samplesPtr = buffer.getReadPointer(0);
	
	if (samplesPtr != nullptr) {
		auto numSamples = buffer.getNumSamples();

		float paddingX = 8;

		g.setColour(juce::Colour::fromRGB(15, 199, 149));
		float width = getRight() - paddingX * 2, height = getHeight();
		float xStep = width / numSamples;

		float x = paddingX, y = scale(samplesPtr[0], -3.f, 3.f, height, 0.f);
		float xNew, yNew;
		for (int i = 1; i < numSamples; i++)
		{
			xNew = x + xStep;
			yNew = scale(samplesPtr[i], -3.f, 3.f, height, 0.f);
			g.drawLine(x, 110, xNew, yNew); //x, y, nNew, yNew (only line graph);
			x = xNew; y = yNew;
		}
		//========================
		float rms = buffer.getRMSLevel(0, 0, numSamples);
		float magnitude = buffer.getMagnitude(0, 0, numSamples);

		g.fillRoundedRectangle(paddingX, height - height / 8, magnitude * 100, height / 8 - paddingX, 2);
		g.setColour(juce::Colour::fromRGB(25, 25, 25));
		g.fillRoundedRectangle(paddingX, height - height / 8, rms * 100, height / 8 - paddingX, 2);
		//buffer.max
	}

}
	

void MeterComponent::paint(juce::Graphics& g)
{
	auto bounds = getLocalBounds();
	g.setColour(juce::Colour::fromRGB(25, 25, 25));
	g.drawRoundedRectangle(bounds.toFloat().reduced(10.0f), 4.0f, 3.0f);
	g.fillRoundedRectangle(bounds.getX() + 5, bounds.getY() + 5, bounds.getWidth() - 10,
		bounds.getHeight() - 10, 5.0f);
	g.setColour(juce::Colour::fromRGB(15, 199, 149));
	g.setFont(15);
	g.setFont(g.getCurrentFont().boldened());
	g.drawText("Meter", 20, 15, 100, 25, juce::Justification::left);
}


void MeterComponent::resized()
{
   
}
