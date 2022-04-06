//OtherLookAndFeel.h


#pragma once
#include <JuceHeader.h>

//==============================================================================
/*
*/
class OtherLookAndFeel : public juce::LookAndFeel_V4
{
public:
    OtherLookAndFeel()
    {
        setColour(juce::Slider::thumbColourId, juce::Colour::fromRGB(255, 201, 71));
    }
    ~OtherLookAndFeel() override
    {

    }

    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
        const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider& slider) {

        auto radius = (float)juce::jmin(width / 2, height / 2) - 4.0f;
        auto centreX = (float)x + (float)width * 0.5f;
        auto centreY = (float)y + (float)height * 0.5f;
        auto rx = centreX - radius;
        auto ry = centreY - radius;
        auto rw = radius * 2.0f;
        auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);

        // fill
        g.setColour(juce::Colour::fromRGB(33, 33, 33));
        g.fillEllipse(rx, ry, rw, rw);

        // inner ellipse
        g.setColour(juce::Colour::fromRGB(25, 25, 25));
        g.fillEllipse(rx + 5, ry + 5, rw - 10, rw - 10);

        // outline
        g.setColour(juce::Colour::fromRGB(63, 33, 89));
        g.drawEllipse(rx, ry, rw, rw, 1.0f);

        juce::Path p;
        auto pointerLength = radius * 1.0f;
        auto pointerThickness = 3.0f;
        p.addEllipse(-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
        //-pointerThickness * 0.5f, -radius, radius * 0.2, radius * 0.2
        p.applyTransform(juce::AffineTransform::rotation(angle).translated(centreX, centreY));

        //pointer
        g.setColour(juce::Colour::fromRGB(15, 199, 149));
        g.fillPath(p);


        auto center_X = x + width / 2;
        auto center_Y = y + height / 2;

        auto numberOfDots = 11;
        auto dotsAngleIncrement = (rotaryEndAngle - rotaryStartAngle)
            / (numberOfDots - 1.0f);
        auto dotSize = 2.0f;
        auto dotsRadius = (float)juce::jmin(width / 2, height / 2) - dotSize;
        auto knobRadius = dotsRadius * 0.6f;

        /*
        g.setColour(juce::Colour::fromRGB(15, 199, 149));
        for (auto i = 0; i < numberOfDots; i++) {
            auto dotAngle = rotaryStartAngle + i * dotsAngleIncrement;
            auto dotPercentage = (float)i / numberOfDots;

            auto isHighlighted = sliderPos >= dotPercentage && sliderPos != 0;
            juce::Path p;
            p.addRectangle(-dotSize,
                -dotSize,
                2 * dotSize,
                2 * dotSize);
            p.applyTransform(juce::AffineTransform::translation(center_X, center_Y - dotsRadius)
                .rotated(dotAngle, center_X, center_Y));
            g.fillPath(p);
        }
        */
    }

    void drawComboBox(juce::Graphics& g, int width, int height,
        const bool isButtonDown,
        int buttonX, int buttonY,
        int buttonW, int buttonH,
        juce::ComboBox& box)
    {
        g.fillAll(box.findColour(juce::ComboBox::backgroundColourId));
        g.setColour(box.findColour((isButtonDown) ? juce::ComboBox::buttonColourId
            : juce::ComboBox::backgroundColourId));
        g.fillRect(buttonX, buttonY, buttonW, buttonH);
        g.setColour(juce::Colour::fromRGB(15, 199, 149));
        g.drawRect(0, 0, width, height);

        const float arrowX = 0.2f;
        const float arrowH = 0.3f;

        if (box.isEnabled())
        {
            juce::Path p;
            p.addTriangle(buttonX + buttonW * 0.5f, buttonY + buttonH * (0.45f - arrowH),
                buttonX + buttonW * (1.0f - arrowX), buttonY + buttonH * 0.45f,
                buttonX + buttonW * arrowX, buttonY + buttonH * 0.45f);

            p.addTriangle(buttonX + buttonW * 0.5f, buttonY + buttonH * (0.55f + arrowH),
                buttonX + buttonW * (1.0f - arrowX), buttonY + buttonH * 0.55f,
                buttonX + buttonW * arrowX, buttonY + buttonH * 0.55f);

            g.setColour(box.findColour((isButtonDown) ? juce::ComboBox::backgroundColourId
                : juce::ComboBox::buttonColourId));
            g.fillPath(p);
        }
    }
};