/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
VocoderAudioProcessorEditor::VocoderAudioProcessorEditor (VocoderAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
    
    // implement your slider/buttons here
//    attack.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
//    attack.setRange(0.0, 30.0, 0.1);
//    attack.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 50, 10);
//    attack.setPopupDisplayEnabled (true, false, this);
//    
//    release.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
//    release.setRange(50.0, 500.0, 0.5);
//    release.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 50, 10);
//    release.setPopupDisplayEnabled (true, false, this);
    
    iGain.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    iGain.setRange(-12.0, 6.0, 0.1);
    iGain.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 50, 10);
    iGain.setPopupDisplayEnabled (true, false, this);
    
    oGain.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    oGain.setRange(-12.0, 6.0, 0.1);
    oGain.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 50, 10);
    oGain.setPopupDisplayEnabled (true, false, this);
    
    // frequency ranges 20-12000 (setup later)
    
    // add the slider/button to the gui
//    addAndMakeVisible(&attack);
//    addAndMakeVisible(&release);
    addAndMakeVisible(&iGain);
    addAndMakeVisible(&oGain);
}

VocoderAudioProcessorEditor::~VocoderAudioProcessorEditor()
{
}

//==============================================================================
void VocoderAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (juce::FontOptions (15.0f));
    
    //write fun stuff
    g.drawFittedText ("hi guys\nadding this line to test debugging", 0, 0, getWidth(), 30, juce::Justification::centred, 1);
}

void VocoderAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    
    // setBounds sets the position and size of the slider with arguments (x, y, width, height)
//    attack.setBounds(0, 0, 50, 50);
//    release.setBounds(50, 0, 50, 50);
    iGain.setBounds(0, 50, 50, 50);
    oGain.setBounds(50, 50, 50, 50);
}
