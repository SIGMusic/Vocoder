#pragma once
#include <JuceHeader.h>

class Modulator {
public:
    void prepare(double sampleRate);
    void applyModulation(juce::AudioBuffer<float>& carrierBand, juce::AudioBuffer<float>& modulatorBand,
        juce::AudioBuffer<float>& outputBand);

private:
    juce::dsp::Gain<float> envelopeFollower;
};