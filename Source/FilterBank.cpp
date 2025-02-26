#include "FilterBank.h"
#include <tuple>


// Constructor that fills the vector "filters" with [numBands] IIRFilters
FilterBank::FilterBank()
{
    for (int i = 0; i < numBands; ++i)
        filters.push_back(std::make_unique<juce::dsp::IIR::Filter<float>>());
}


// Loops through each filter in the bank, preparing it with the Process specifications passed into the method
void FilterBank::prepare(const juce::dsp::ProcessSpec& spec) 
{
    for (auto& filter : filters) {
        filter.reset(); // reset filter state, clearing history if there is any
        filter->prepare(spec);
    }
}


// Creates/applies IIRFilter coefficients for each IIRFilter in the bank, using a vector of center frequencies passed as a parameter
// centerFrequencies should have the same size as numBands
void FilterBank::setBandFrequencies(const std::vector<float>& centerFrequencies)
{
    double sampleRate = 44100.0; // Change this dynamically if needed
    double qFactor = 1.0;        // Adjust for filter sharpness
    
    
    const std::tuple<double, double> freqRange(20.0, 12000.0);// hardcoded for now, but we'll let the user change this later
    //convert qFactor to band width
    //space out center frequencies exponentially using band ranges (ouch)
    const std::vector<double> hardCodedCenterFrequencies = {100.0, 195.0, 380.25, 741.4875, 1445.90062, 2819.50622, 5498.03713, 10721.1724}; //hardcoded for now
    
    

    for (size_t i = 0; i < filters.size(); ++i)
    {
        auto coefficients = juce::dsp::IIR::Coefficients<float>::makeBandPass(
            sampleRate, hardCodedCenterFrequencies[i], qFactor);
        filters[i]->coefficients = coefficients;
    }
}




void FilterBank::process(juce::AudioBuffer<float>& buffer)
{
    juce::dsp::AudioBlock<float> block(buffer);

    for (auto& filter : filters)
        filter->process(juce::dsp::ProcessContextReplacing<float>(block));
}