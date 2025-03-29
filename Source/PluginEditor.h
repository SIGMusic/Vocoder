/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class VocoderAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    VocoderAudioProcessorEditor (VocoderAudioProcessor&);
    ~VocoderAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void setComponent(juce::Component& c, int left, int top, int width, int height);
    void mouseUp(const juce::MouseEvent& e);
    void mouseDrag(const juce::MouseEvent& e);
    void mouseDown(const juce::MouseEvent& e);
    void updateSliderValueAtPosition(const juce::Point<int>& position);
private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    VocoderAudioProcessor& audioProcessor;

    //define the buttons and sliders and such here first
//    juce::Slider attack;
//    juce::Slider release;
    const int height_ = 600;
    const int width_ = 1000;
    const float ratio_ = 1000.0 / 600.0;
    const int maxVocoders = 40;
    bool isDragging = false;
    juce::Slider iGain;
    juce::Slider oGain;
    juce::Slider nBands;
    juce::Slider freqRange;
    juce::DrawableText bandText;
    juce::DrawableText inGainText;
    juce::DrawableText outGainText;
    juce::DrawableText filterText;
    juce::DrawableText freqText;
    juce::DrawableText vocoderText;
    std::vector<juce::Slider*> vocoders = std::vector<juce::Slider*> (maxVocoders);
    int runs = 0;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VocoderAudioProcessorEditor)
};
