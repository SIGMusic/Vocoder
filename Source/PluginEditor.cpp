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

    inGainText.setText("In Gain");
    iGain.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    iGain.setRange(-12.0, 6.0, 0.1);
    iGain.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 50, 10);
    iGain.setPopupDisplayEnabled (true, false, this);

    outGainText.setText("Out Gain");
    oGain.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    oGain.setRange(-12.0, 6.0, 0.1);
    oGain.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 50, 10);
    oGain.setPopupDisplayEnabled (true, false, this);

    bandText.setText("number of bands");
    nBands.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    nBands.setRange(8, 40, 2);
    nBands.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 10);
    nBands.setPopupDisplayEnabled (false, false, this);

    freqText.setText("Frequency Range");
    freqRange.setSliderStyle(juce::Slider::TwoValueHorizontal);
    freqRange.setRange(20, 12000, 1);
    freqRange.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 10);
    freqRange.setPopupDisplayEnabled(false, false, this);
    // frequency ranges 20-12000 (setup later)
    vocoderText.setText("vocoder bank");
    for (auto& c : vocoders) {
        c = new juce::Slider();
        c->setSliderStyle(juce::Slider::LinearVertical);
        c->setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
        c->setSliderSnapsToMousePosition(false);
        c->setInterceptsMouseClicks(true, true);
        c->setRange(0, 1.0);
    }
    for (int i = 0; i < 8; i++) {
        addAndMakeVisible(vocoders[i]);
    }
    
    // add the slider/button to the gui
//    addAndMakeVisible(&attack);
//    addAndMakeVisible(&release);
    addAndMakeVisible(&iGain);
    addAndMakeVisible(&oGain);
    addAndMakeVisible(&nBands);
    addAndMakeVisible(&outGainText);
    addAndMakeVisible(&inGainText);
    addAndMakeVisible(&freqRange);
    addAndMakeVisible(&freqText);
    addAndMakeVisible(&bandText);
    addAndMakeVisible(&vocoderText);
}

VocoderAudioProcessorEditor::~VocoderAudioProcessorEditor()
{
    for (auto c : vocoders) {
        delete c;
        c = nullptr;
    }
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
    g.drawFittedText (std::to_string(runs), 0, 0, getWidth(), 30, juce::Justification::centred, 1);
    resized();
}

void VocoderAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    
    // setBounds sets the position and size of the slider with arguments (x, y, width, height)
    float vocoderWidth = 750.0 / nBands.getValue();
    for (int i = 0; i < nBands.getValue(); i++) {
        addAndMakeVisible(vocoders[i]);
        setComponent(*vocoders[i], i * vocoderWidth + 200, 100, vocoderWidth, 400);
    }
    setComponent(freqRange, 200, 500, 750, 100);
    for (int i = nBands.getValue(); i < maxVocoders; i++) {
        removeChildComponent(vocoders[i]);
    }
    runs++;
    setComponent(inGainText, 10, 20, 20, 20);
    setComponent(iGain, 0, 50, 100, 100);
    setComponent(outGainText, 110, 20, 20, 20);
    setComponent(oGain, 100, 50, 100, 100);
    setComponent(bandText, 10, 220, 20, 20);
    setComponent(nBands, 0, 250, 200, 200);
    setComponent(freqText, 560, 510, 600, 100);
    setComponent(vocoderText, 750, 30, 60, 30);
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

void VocoderAudioProcessorEditor::updateSliderValueAtPosition(const juce::Point<int>& position) {
    for (int i = 0; i < vocoders.size(); ++i)
    {
        if (vocoders[i]->getBounds().contains(position))
        {
            // Convert to slider's local coordinates
            auto localPos = position - vocoders[i]->getBounds().getPosition();
            
            // Calculate value based on vertical position
            double sliderHeight = vocoders[i]->getHeight();
            double normalizedValue = 1.0 - (localPos.getY() / sliderHeight);
            normalizedValue = juce::jlimit(0.0, 1.0, normalizedValue);
            
            // Set the slider value
            vocoders[i]->setValue(normalizedValue, juce::sendNotificationAsync);
            break;
        }
    }
}

void VocoderAudioProcessorEditor::mouseDown(const juce::MouseEvent& e) {
    isDragging = true;
    updateSliderValueAtPosition(e.getPosition());
}
void VocoderAudioProcessorEditor::mouseDrag(const juce::MouseEvent& e) {
    if (isDragging) {
        updateSliderValueAtPosition(e.getPosition());
    }
}
void VocoderAudioProcessorEditor::mouseUp(const juce::MouseEvent& e) {
    isDragging = false;
}
