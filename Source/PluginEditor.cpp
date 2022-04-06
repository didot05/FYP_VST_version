//PluginEditor.cpp

#include "PluginProcessor.h"
#include "PluginEditor.h"
//==============================================================================

SynthAudioProcessorEditor::SynthAudioProcessorEditor (SynthAudioProcessor& p)
: AudioProcessorEditor (&p) 
, openDialogButtons(buttonTexts.size())
, audioProcessor (p)
, osc1 (audioProcessor.apvts, "OSC1", "OSC1GAIN", "OSC1PITCH","OSC1DETUNE", "DISTORTION1", "OSC1FMTYPE", "OSC1FMFREQ", "OSC1FMDEPTH", "OSC1NUMOBERTONES", "OSC1PAN", "OSC1UNISON")
, osc2 (audioProcessor.apvts, "OSC2", "OSC2GAIN", "OSC2PITCH","OSC2DETUNE", "DISTORTION2", "OSC2FMTYPE", "OSC2FMFREQ", "OSC2FMDEPTH", "OSC2NUMOBERTONES", "OSC2PAN", "OSC2UNISON")
, filter (audioProcessor.apvts, "FILTERTYPE", "FILTERCUTOFF", "FILTERRESONANCE")
, adsr (audioProcessor.apvts, "ATTACK", "DECAY", "SUSTAIN", "RELEASE")
, filterAdsr (audioProcessor.apvts, "FILTERATTACK", "FILTERDECAY", "FILTERSUSTAIN", "FILTERRELEASE")
, reverb (audioProcessor.apvts, "REVERBSIZE", "REVERBDAMPING", "REVERBWIDTH", "REVERBDRY", "REVERBWET", "REVERBFREEZE", "DELAY")
, chorus (audioProcessor.apvts, "CHORUSRATE", "CHORUSDEPTH", "CHORUSCENTERDELAY", "CHORUSFEEDBACK", "CHORUSMIX")
, compreData (audioProcessor.apvts, "THRESHOLD", "RATIO", "COMPATTACK", "COMPRELEASE")
, phaser (audioProcessor.apvts, "PHASERRATE", "PHASERDEPTH", "PHASERCENTERFREQ", "PHASERFEEDBACK", "PHASERMIX")
, meter (audioProcessor)
{  
    // setLookAndFeel(&otherLookAndFeel);
    //Make each component visible on the screen.
    addAndMakeVisible (osc1);
    addAndMakeVisible (osc2);
    addAndMakeVisible (filter);
    addAndMakeVisible (adsr);
    addAndMakeVisible (filterAdsr);
    addAndMakeVisible (reverb);
    addAndMakeVisible (meter);
    addAndMakeVisible(chorus);
    addAndMakeVisible(compreData);
    addAndMakeVisible(phaser);

    //Set the name (label) of the each component
    osc1.setName ("Oscillator 1");
    osc2.setName ("Oscillator 2");
    filter.setName ("Filter");
    filterAdsr.setName ("Filter ADSR");
    adsr.setName ("ADSR");
    meter.setName ("Meter");
    reverb.setName("Reverb");
    compreData.setName("Compressor");
    phaser.setName("Phaser");
    
    //Set the color with RGB value
    auto oscColour = juce::Colour::fromRGB (247, 190, 67);
    auto filterColour = juce::Colour::fromRGB (48, 48, 48);
    
    osc1.setBoundsColour (oscColour);
    osc2.setBoundsColour (oscColour);
    
    filterAdsr.setBoundsColour (filterColour);
    filter.setBoundsColour (filterColour);
    adsr.setBoundsColour(filterColour);
    meter.setBoundsColour(filterColour);
    reverb.setBoundsColour(filterColour);

    // Help Button
    int h = 30;
    int w = 80;
    int offset = 10;

    for (int i = 0; i < buttonTexts.size(); i++) {
        openDialogButtons[i].reset(new TextButton(buttonTexts[i], buttonTexts[i]));
        addAndMakeVisible(openDialogButtons[i].get());
    }
    openDialogButtons[0]->setBounds(470, 650, w, h);
    openDialogButtons[0]->setColour(juce::TextButton::buttonColourId, juce::Colour::fromRGB(33, 33, 33));
    openDialogButtons[0]->setColour(juce::TextButton::textColourOffId, juce::Colour::fromRGB(15, 199, 149));
    openDialogButtons[1]->setBounds(570, 650, w, h);
    openDialogButtons[1]->setColour(juce::TextButton::buttonColourId, juce::Colour::fromRGB(33, 33, 33));
    openDialogButtons[1]->setColour(juce::TextButton::textColourOffId, juce::Colour::fromRGB(15, 199, 149));
    openDialogButtons[2]->setBounds(670, 650, w, h);
    openDialogButtons[2]->setColour(juce::TextButton::buttonColourId, juce::Colour::fromRGB(33, 33, 33));
    openDialogButtons[2]->setColour(juce::TextButton::textColourOffId, juce::Colour::fromRGB(15, 199, 149));
    openDialogButtons[3]->setBounds(770, 650, w, h);
    openDialogButtons[3]->setColour(juce::TextButton::buttonColourId, juce::Colour::fromRGB(33, 33, 33));
    openDialogButtons[3]->setColour(juce::TextButton::textColourOffId, juce::Colour::fromRGB(15, 199, 149));
    openDialogButtons[4]->setBounds(530, 700, w, h);
    openDialogButtons[4]->setColour(juce::TextButton::buttonColourId, juce::Colour::fromRGB(33, 33, 33));
    openDialogButtons[4]->setColour(juce::TextButton::textColourOffId, juce::Colour::fromRGB(15, 199, 149));
    openDialogButtons[5]->setBounds(630, 700, w, h);
    openDialogButtons[5]->setColour(juce::TextButton::buttonColourId, juce::Colour::fromRGB(33, 33, 33));
    openDialogButtons[5]->setColour(juce::TextButton::textColourOffId, juce::Colour::fromRGB(15, 199, 149));
    openDialogButtons[6]->setBounds(730, 700, w, h);
    openDialogButtons[6]->setColour(juce::TextButton::buttonColourId, juce::Colour::fromRGB(33, 33, 33));
    openDialogButtons[6]->setColour(juce::TextButton::textColourOffId, juce::Colour::fromRGB(15, 199, 149));

    // reference : https://qiita.com/ring2/items/b024084be6cccc9e2601
    for (int i = 0; i < buttonTexts.size(); i++) {
        openDialogButtons[i]->onClick = [i, this]() {

            MessageBoxIconType iconType;

            String title(buttonTexts[i]);

            String msg0(TRANS(title + "\n" + ": This is the help feature for brief information of each synthesiser's functions."));
            String msg(TRANS(title + "\n" + ": A compressor is used to reduce a signal's dynamic range - reduce the difference in level between the loudest and quietest parts of an audio signal. Use this to attenuate loud transient peaks to help maintain a consistent level."));
            String msg1(TRANS(title + "\n" + ": A phaser creates cuts in the high end of a signal with the placement of those cuts being modulated up and down to different places on the audio spectrum. So, you can use this to add body to individual notes or to create that classic swirling, movement sound."));
            String msg2(TRANS(title + "\n" + ": Chorus thickens your tone and makes it sound like a chorus of guitars all playing at the same time. Chorus takes your signal and splits it into multiple signals."));
            String msg3(TRANS(title + "\n" + ": Reverb lets you transport a listener to a concert hall, a cave, or an intimate performance space. It allows for natural (or added) harmonics of a sound to shine through and gives your mix extra space. (e.g. echo)"));
            String msg4(TRANS(title + "\n" + ": The basic components of a synth sound. Oscillators generate the basic sound by, er, oscillating. You can select the form of the sound wave you want with the OSC selector box."));
            String msg5(TRANS(title + "\n" + ": The filter has a cut-off effect. The 'cutoff 'control lets you choose the frequency where the cutting off the volume of the various frequencies within the sound. You can control the cutoff knob to choose cutoff frequency."));
            String msg6(TRANS(title + "\n" + ": Attack, decay, sustain, release. These stages control the level of the sound from the moment you press a key or advance a music sequencer. Keep your attack time at zero with a fast release to get a staccato sound."));


            function<void(int)> callback = [](int result) {
                DBG("result : " << result);
            };

            if (buttonTexts[i] == "Help") {
                NativeMessageBox::showAsync(MessageBoxOptions()
                    .withIconType(MessageBoxIconType::InfoIcon)
                    .withTitle(buttonTexts[i])
                    .withMessage(msg0)
                    .withButton(TRANS("close")),
                    callback);
            }

            if (buttonTexts[i] == "Compressor") {
                NativeMessageBox::showAsync(MessageBoxOptions()
                    .withIconType(MessageBoxIconType::InfoIcon)
                    .withTitle(buttonTexts[i])
                    .withMessage(msg)
                    .withButton(TRANS("close")),
                    callback);
            }
            else if (buttonTexts[i] == "Phaser") {
                NativeMessageBox::showAsync(MessageBoxOptions()
                    .withIconType(MessageBoxIconType::InfoIcon)
                    .withTitle(buttonTexts[i])
                    .withMessage(msg1)
                    .withButton(TRANS("close")),
                    callback);
            }
            else if (buttonTexts[i] == "Chorus") {
                NativeMessageBox::showAsync(MessageBoxOptions()
                    .withIconType(MessageBoxIconType::InfoIcon)
                    .withTitle(buttonTexts[i])
                    .withMessage(msg2)
                    .withButton(TRANS("close")),
                    callback);
            }
            else if (buttonTexts[i] == "Reverb") {
                NativeMessageBox::showAsync(MessageBoxOptions()
                    .withIconType(MessageBoxIconType::InfoIcon)
                    .withTitle(buttonTexts[i])
                    .withMessage(msg3)
                    .withButton(TRANS("close")),
                    callback);
            }
            else if (buttonTexts[i] == "Osc") {
                NativeMessageBox::showAsync(MessageBoxOptions()
                    .withIconType(MessageBoxIconType::InfoIcon)
                    .withTitle(buttonTexts[i])
                    .withMessage(msg4)
                    .withButton(TRANS("close")),
                    callback);
            }
            else if (buttonTexts[i] == "Filter") {
                NativeMessageBox::showAsync(MessageBoxOptions()
                    .withIconType(MessageBoxIconType::InfoIcon)
                    .withTitle(buttonTexts[i])
                    .withMessage(msg5)
                    .withButton(TRANS("close")),
                    callback);
            }
            else if (buttonTexts[i] == "ADSR") {
                NativeMessageBox::showAsync(MessageBoxOptions()
                    .withIconType(MessageBoxIconType::InfoIcon)
                    .withTitle(buttonTexts[i])
                    .withMessage(msg5)
                    .withButton(TRANS("close")),
                    callback);
            }
        };
    }


    startTimerHz(30);
    setSize(1120, 820);  
    setResizable(true, true);

}

SynthAudioProcessorEditor::~SynthAudioProcessorEditor()
{
    stopTimer();
    for (int i = 0; i < buttonTexts.size(); i++) {
        openDialogButtons[i] = nullptr;
    }
}

//==============================================================================
void SynthAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colour::fromRGB(33, 33, 33));
}

void SynthAudioProcessorEditor::resized()
{
    const auto oscWidth = 390; 
    const auto oscHeight = 230; 

    osc1.setBounds(0, 0, oscWidth, oscHeight);
    osc2.setBounds(0, osc1.getBottom(), oscWidth, oscHeight);
    filter.setBounds(osc1.getRight(), 0, 180, 200);
    filterAdsr.setBounds(filter.getRight(), 0, 240, 200);
    adsr.setBounds(filterAdsr.getRight(), 0, 240, 200);
    chorus.setBounds(0, osc2.getBottom(), oscWidth, 150);
    reverb.setBounds(0, chorus.getBottom(), oscWidth + 45, 155);
    compreData.setBounds(osc2.getRight(), filter.getBottom(), 280, 180);
    phaser.setBounds(compreData.getRight(), filter.getBottom(), 380, 180);
    meter.setBounds(chorus.getRight(), compreData.getBottom(), 660, 220);
}

void SynthAudioProcessorEditor::timerCallback()
{
    repaint();
	//midiKeyboard.grabKeyboardFocus();
	//stopTimer();
}

void SynthAudioProcessorEditor::hostMIDIControllerIsAvailable(bool controllerIsAvailable)
{
}
