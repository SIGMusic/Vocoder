#pragma once
#include <JuceHeader.h>

class FilterBank {
public:
    void prepare(double sampleRate, int samplesPerBlock, int numChannels, int numBands,
        const std::vector<float>& centerFrequencies, const std::vector<float>& Qs);

    void process(juce::AudioBuffer<float>& buffer, std::vector<juce::AudioBuffer<float>>& bandBuffers);
    void reset();

private:
    juce::dsp::ProcessSpec spec;
    std::vector<juce::dsp::ProcessorDuplicator<
        juce::dsp::IIR::Filter<float>,
        juce::dsp::IIR::Coefficients<float>>> bands;
};