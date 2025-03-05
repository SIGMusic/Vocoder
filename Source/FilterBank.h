#pragma once

#include <JuceHeader.h>

class FilterBank
{
public:
    FilterBank();
    void prepare(const juce::dsp::ProcessSpec& spec);
    float processOneBand(float sample, int bandToProcess);
    void setBandFrequencies();
    void setBandFrequencies(const std::vector<float>& centerFrequencies);
    void setQFactor(double q);
    void setSampleRate(double rate);

private:
    static constexpr int numBands = 8;
    double sampleRate = 44100.0;
    double qFactor = 1.0;
    std::vector<juce::dsp::IIR::Filter<float>> filters;
};