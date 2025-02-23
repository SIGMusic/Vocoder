#pragma once

#include "FilterBank.h"

class Vocoder
{
public:
    void prepare(const juce::dsp::ProcessSpec& spec);
    void process(juce::AudioBuffer<float>& modulator, juce::AudioBuffer<float>& carrier);

private:
    FilterBank filterBank;
};