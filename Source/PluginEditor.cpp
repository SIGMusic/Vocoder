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
    setSize (width_, height_);
    setResizable(true, true);
    getConstrainer()->setFixedAspectRatio(ratio_);
    
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
    for (auto& c : vocoders) {
        c.setSliderStyle(juce::Slider::LinearVertical);
        c.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    }
    for (int i = 0; i < 8; i++) {
        addAndMakeVisible(&vocoders[i]);
    }
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

    g.setColour (juce::Colours::darkblue);
    g.setFont (juce::FontOptions (15.0f));
    float scalar = static_cast<float>(getHeight()) / height_;
    g.fillRect(200 * scalar, 100 * scalar, (getWidth()) - (250 * scalar), (getHeight()) - (200 * scalar));
    
    
    //write fun stuff "hi guys\nadding this line to test debugging12" +
    g.drawFittedText (std::to_string(nBands.getValue()), 0, 0, getWidth(), 30, juce::Justification::centred, 1);
}

void VocoderAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    
    // setBounds sets the position and size of the slider with arguments (x, y, width, height)
    float vocoderWidth = 750.0 / nBands.getValue();
    for (int i = 0; i < nBands.getValue(); i++) {
        addAndMakeVisible(&vocoders[i]);
        setComponent(vocoders[i], i * vocoderWidth + 200, 100, vocoderWidth, 400);
    }
    runs++;
    setComponent(iGain, 0, 50, 100, 100);
    setComponent(oGain, 100, 50, 100, 100);
    //oGain.setBounds(50, 50, 50, 50);
    setComponent(nBands, 0, 250, 200, 200);
    //nBands.setBounds(150, 0, 100, 100);
}
void VocoderAudioProcessorEditor::setComponent(juce::Component& c, int left, int top, int width, int height) {
    //use ratio to make it ratioed
    double scalar = (static_cast<double>(getHeight()) / height_);
    int rleft = scalar * left;
    int rtop = scalar * top;
    int rwidth = scalar * width;
    int rheight = scalar * height;
    c.setBounds(rleft, rtop, rwidth, rheight);
        
}
