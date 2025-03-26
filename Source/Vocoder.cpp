#include "Vocoder.h"

void Vocoder::prepare(const juce::dsp::ProcessSpec& spec)
{
    const std::vector<float> centerFrequencies = { 100.0f, 195.0f, 380.25f, 741.49f, 1445.90f, 2819.51f, 5498.04f, 10721.17f };
    const std::vector<float> Qs(centerFrequencies.size(), 50.0f); // Q = 1.0 for all bands

    filterBank_.prepare(spec.sampleRate, spec.maximumBlockSize, spec.numChannels, numBands_, centerFrequencies, Qs);
    modulator_.prepare(spec.sampleRate);
}

void Vocoder::process(juce::AudioBuffer<float>& carrier, juce::AudioBuffer<float>& modulator, juce::AudioBuffer<float>& output)
{
    filterBank_.process(carrier, carrierBands);

    juce::AudioBuffer<float> tempOut(carrier.getNumChannels(), carrier.getNumSamples());

    tempOut.clear();
    
    for (auto& band : carrierBands) {
        for (int channel = 0; channel < carrier.getNumChannels(); ++channel) {
            const float* car = band.getReadPointer(channel);
            float* out = tempOut.getWritePointer(channel);
            for (int sample = 0; sample < carrier.getNumSamples(); ++sample) {
                out[sample] += car[sample];
            }
        }
    }

    output = tempOut;

    /*filterBank_.process(modulator, modulatorBands);*/

    /*outputBands.resize(numBands_);
    for (int i = 0; i < numBands_; ++i) {
        outputBands[i].setSize(carrier.getNumChannels(), carrier.getNumSamples(), false, false, true);
        modulator_.applyModulation(carrierBands[i], modulatorBands[i], outputBands[i]);
    }

    mixOutput(output);*/
}

void Vocoder::mixOutput(juce::AudioBuffer<float>& output)
{
    output.clear();

    for (int band = 0; band < numBands_; ++band) {
        for (int channel = 0; channel < output.getNumChannels(); ++channel) {
            const float* bandData = outputBands[band].getReadPointer(channel);
            float* out = output.getWritePointer(channel);
            for (int sample = 0; sample < output.getNumSamples(); ++sample) {
                out[sample] += bandData[sample];
            }

        }
    }
}