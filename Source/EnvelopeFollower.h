#pragma once

#include <juce_dsp/juce_dsp.h>
#include <juce_core/juce_core.h>

class EnvelopeFollower {
public:
    EnvelopeFollower();
    void prepare(double sampleRate);
    float processSample(float inputSample);
    void setAttackRelease(float attackMs, float releaseMs);

private:
    double sampleRate = 44100.0;
    float envelope = 0.0f;
    float attackCoeff = 0.0f;
    float releaseCoeff = 0.0f;
};