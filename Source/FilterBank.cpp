#include "FilterBank.h"

void FilterBank::prepare(double sampleRate, int samplesPerBlock, int numChannels, int numBands,
    const std::vector<float>& centerFrequencies, const std::vector<float>& Qs)
{
    jassert(centerFrequencies.size() == static_cast<size_t>(numBands));
    jassert(Qs.size() == static_cast<size_t>(numBands));

    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = static_cast<juce::uint32>(samplesPerBlock);
    spec.numChannels = static_cast<juce::uint32>(numChannels);

    bands.clear();
    bands.resize(numBands);

    for (int b = 0; b < numBands; ++b) {
        bands[b].state = juce::dsp::IIR::Coefficients<float>::makeBandPass(sampleRate, centerFrequencies[b], Qs[b]);
        bands[b].prepare(spec);
    }
}

void FilterBank::process(juce::AudioBuffer<float>& buffer, std::vector<juce::AudioBuffer<float>>& bandBuffers)
{
    bandBuffers.resize(bands.size());
    int index = 0;
    for (auto& band : bands) {
        bandBuffers[index] = buffer; // Efficient copy constructor
        juce::dsp::AudioBlock<float> block(bandBuffers[index]);
        juce::dsp::ProcessContextReplacing<float> context(block);
        band.process(context);
        ++index;
    }
}

void FilterBank::reset()
{
    for (auto& band : bands)
        band.reset();
}