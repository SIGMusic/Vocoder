#include "Vocoder.h"

void Vocoder::prepare(const juce::dsp::ProcessSpec& spec)
{
    filterBank.prepare(spec);
}

void Vocoder::process(juce::AudioBuffer<float>& modulator, juce::AudioBuffer<float>& carrier)
{
    filterBank.process(modulator);
    filterBank.process(carrier);
}