#include "FilterBank.h"

FilterBank::FilterBank()
{
    for (int i = 0; i < numBands; ++i)
        filters.push_back(std::make_unique<juce::dsp::IIR::Filter<float>>());
}

void FilterBank::prepare(const juce::dsp::ProcessSpec& spec)
{
    for (auto& filter : filters)
        filter->prepare(spec);
}

void FilterBank::setBandFrequencies(const std::vector<float>& centerFrequencies)
{
    double sampleRate = 44100.0; // Change this dynamically if needed
    double qFactor = 1.0;        // Adjust for filter sharpness

    for (size_t i = 0; i < filters.size(); ++i)
    {
        auto coefficients = juce::dsp::IIR::Coefficients<float>::makeBandPass(
            sampleRate, centerFrequencies[i], qFactor);
        *filters[i]->coefficients = *coefficients;
    }
}

void FilterBank::process(juce::AudioBuffer<float>& buffer)
{
    juce::dsp::AudioBlock<float> block(buffer);

    for (auto& filter : filters)
        filter->process(juce::dsp::ProcessContextReplacing<float>(block));
}