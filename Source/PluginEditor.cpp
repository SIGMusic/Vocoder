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
    lowFreq.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    lowFreq.setRange(0.0, 127.0, 0.5);
    lowFreq.setTextBoxStyle (juce::Slider::NoTextBox, false, 90, 0);
    lowFreq.setPopupDisplayEnabled (true, false, this);
    lowFreq.setTextValueSuffix ("Lo");
    lowFreq.setValue(1.0);
    
    // add the slider/button to the gui
    addAndMakeVisible(&lowFreq);
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
    
    // sets the position and size of the slider with arguments (x, y, width, height)
    lowFreq.setBounds(0, 0, 200, 200);
}
