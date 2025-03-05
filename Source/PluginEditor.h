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

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    VocoderAudioProcessor& audioProcessor;

    //define the buttons and sliders and such here first
//    juce::Slider attack;
//    juce::Slider release;
    
    juce::Slider iGain;
    juce::Slider oGain;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VocoderAudioProcessorEditor)
};
