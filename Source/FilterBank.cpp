#include "FilterBank.h"
#include <tuple>


// Constructor that fills the vector "filters" with [numBands] IIRFilters
FilterBank::FilterBank()
{
    for (int i = 0; i < numBands; ++i)
        filters.push_back(juce::dsp::IIR::Filter<float>());
}


// Loops through each filter in the bank, preparing it with the Process specifications passed into the method and setting coefficients
void FilterBank::prepare(const juce::dsp::ProcessSpec& spec) 
{
    for (auto& filter : filters) {
        filter.reset(); // reset filter state, clearing history if there is any
        setBandFrequencies(); // set the coefficients of each filter, using the default center frequencies calculated from the frequency range of (20, 12000)
        filter.prepare(spec);
    }
}


// Creates/applies IIRFilter coefficients for each IIRFilter in the bank, calculating center frequencies based off of the frequency range.
// This is called right after filter.prepare()
void FilterBank::setBandFrequencies()
{    
    const std::tuple<double, double> freqRange(20.0, 12000.0);// hardcoded for now, but we'll let the user change this later
    //to do here:
    //convert qFactor to band width
    //space out center frequencies exponentially using band ranges (ouch) so that they are spread evenly to human perception
    const std::vector<double> centerFrequencies = {100.0, 195.0, 380.25, 741.4875, 1445.90062, 2819.50622, 5498.03713, 10721.1724}; //hardcoded for now (n+1 = 1.95n)
    
    for (size_t i = 0; i < filters.size(); ++i)
    {
        auto coefficients = juce::dsp::IIR::Coefficients<float>::makeBandPass(
            sampleRate, centerFrequencies[i], qFactor);
        filters[i].coefficients = coefficients;
    }
}


// Same as setBandFrequencies(), but allows the center frequencies to be passed in directly instead of calculated. 
// In case the user wants to set their own center frequencies for some reason. 
void FilterBank::setBandFrequencies(const std::vector<float>& centerFrequencies)
{
    for (size_t i = 0; i < filters.size(); ++i)
    {
        auto coefficients = juce::dsp::IIR::Coefficients<float>::makeBandPass(
            sampleRate, centerFrequencies[i], qFactor);
        filters[i].coefficients = coefficients;
        filters[i].reset();
    }
}


// These setters don't do anything to the filters by themselves.
// setBandFrequences() or its overload must be called again after calling these setters in order to update the filters' coefficients.
void FilterBank::setQFactor(double q) {
    qFactor = q;
}
void FilterBank::setSampleRate(double rate) {
    sampleRate = rate;
}


// Runs the passed AudioBuffer through each filter
void FilterBank::process(juce::AudioBuffer<float>& buffer)
{
    juce::dsp::AudioBlock<float> block(buffer);

    for (auto& filter : filters)
        filter.process(juce::dsp::ProcessContextReplacing<float>(block));
}