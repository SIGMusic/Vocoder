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
    setSize (1000, 600);
    setResizable(true, true);
    getConstrainer()->setFixedAspectRatio(1000.0/600.0);
    
    iGain.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    iGain.setRange(-12.0, 6.0, 0.1);
    iGain.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 50, 10);
    iGain.setPopupDisplayEnabled (true, false, this);
    
    oGain.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    oGain.setRange(-12.0, 6.0, 0.1);
    oGain.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 50, 10);
    oGain.setPopupDisplayEnabled (true, false, this);
    nBands.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    nBands.setRange(8, 40, 2);
    nBands.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 10);
    nBands.setPopupDisplayEnabled (false, false, this);
    // frequency ranges 20-12000 (setup later)
    
    // add the slider/button to the gui
//    addAndMakeVisible(&attack);
//    addAndMakeVisible(&release);
    addAndMakeVisible(&iGain);
    addAndMakeVisible(&oGain);
    addAndMakeVisible(&nBands);
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
    
    g.fillRect(100, 100, 100 ,100);
    
    
    //write fun stuff
    g.drawFittedText ("hi guys\nadding this line to test debugging", 0, 0, getWidth(), 30, juce::Justification::centred, 1);
}

void VocoderAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    
    // setBounds sets the position and size of the slider with arguments (x, y, width, height)
    iGain.setBounds(0, 50, 50, 50);
    oGain.setBounds(50, 50, 50, 50);
    nBands.setBounds(150, 0, 100, 100);
}
void VocoderAudioProcessorEditor::setComponent(juce::Component c, int left, int top, int width, int height) {

        
}
