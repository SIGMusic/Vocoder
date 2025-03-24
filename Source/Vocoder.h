#pragma once
#include <JuceHeader.h>
#include "FilterBank.h"
#include "Modulator.h"

class Vocoder {
public:
    void prepare(const juce::dsp::ProcessSpec& spec);
    void process(juce::AudioBuffer<float>& carrier, juce::AudioBuffer<float>& modulator, juce::AudioBuffer<float>& output);

private:
    void mixOutput(juce::AudioBuffer<float>& output);

    FilterBank filterBank_;
    Modulator modulator_;

    std::vector<juce::AudioBuffer<float>> carrierBands;
    std::vector<juce::AudioBuffer<float>> modulatorBands;
    std::vector<juce::AudioBuffer<float>> outputBands;

    int numBands_ = 8;
};