#pragma once

#include <JuceHeader.h>

class FilterBank
{
public:
    FilterBank();
    void prepare(const juce::dsp::ProcessSpec& spec);
    void process(juce::AudioBuffer<float>& buffer);
    void setBandFrequencies(const std::vector<float>& centerFrequencies);

private:
    static constexpr int numBands = 8;
    std::vector<std::unique_ptr<juce::dsp::IIR::Filter<float>>> filters;
};