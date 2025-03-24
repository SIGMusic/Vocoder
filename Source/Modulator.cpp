#include "Modulator.h"

void Modulator::prepare(double sampleRate) {
    envelopeFollower.prepare({ sampleRate, static_cast<juce::uint32>(512), 1 });
}

void Modulator::applyModulation(juce::AudioBuffer<float>& carrierBand, juce::AudioBuffer<float>& modulatorBand,
    juce::AudioBuffer<float>& outputBand)
{
    for (int channel = 0; channel < outputBand.getNumChannels(); ++channel) {
        const float* car = carrierBand.getReadPointer(channel);
        const float* mod = modulatorBand.getReadPointer(channel);
        float* out = outputBand.getWritePointer(channel);

        for (int sample = 0; sample < outputBand.getNumSamples(); ++sample) {
            // Simple amplitude following (no smoothing here, you could add attack/release envelope)
            float modulatedGain = std::abs(mod[sample]);
            out[sample] = modulatedGain * car[sample];
        }
    }
}