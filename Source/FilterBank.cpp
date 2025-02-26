#include "FilterBank.h"


// Constructor that fills the vector "filters" with [numBands] IIRFilters
FilterBank::FilterBank()
{
    for (int i = 0; i < numBands; ++i)
        filters.push_back(std::make_unique<juce::dsp::IIR::Filter<float>>());
}


// Loops through each filter in the bank, preparing it with the Process specifications passed into the method
void FilterBank::prepare(const juce::dsp::ProcessSpec& spec) 
{
    for (auto& filter : filters)
        filter.reset(); // reset filter state, clearing history
        filter.prepare(spec);
}


// Creates/applies IIRFilter coefficients for each IIRFilter in the bank, using a vector of center frequencies, which should have the same size as numBands
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