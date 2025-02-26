#include "EnvelopeFollower.h"
#include <cmath>

EnvelopeFollower::EnvelopeFollower() {}

void EnvelopeFollower::prepare(double newSampleRate)
{
    sampleRate = newSampleRate;
    setAttackRelease(10.0f, 100.0f); // Default attack/release in ms
}

void EnvelopeFollower::setAttackRelease(float attackMs, float releaseMs)
{
    // Convert attack and release times from milliseconds to coefficient values
    attackCoeff = std::exp(-1.0f / ((attackMs / 1000.0f) * sampleRate));
    releaseCoeff = std::exp(-1.0f / ((releaseMs / 1000.0f) * sampleRate));
}

float EnvelopeFollower::processSample(float inputSample)
{
    // Full-wave rectification (absolute value)
    float rectified = std::abs(inputSample);

    // Choose attack or release coefficient based on signal increase or decrease
    if (rectified > envelope)
        envelope = attackCoeff * (envelope - rectified) + rectified;
    else
        envelope = releaseCoeff * (envelope - rectified) + rectified;

    return envelope;
}
