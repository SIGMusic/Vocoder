#pragma once

#include <JuceHeader.h>
#include "FilterBank.h"
#include "EnvelopeFollower.h"

class Modulator
{
public:
    Modulator(std::vector<float> audio, std::vector<float> amplitude);

    float applyModulation();

private:
	std::vector<float> audio_;
	std::vector<float> amplitude_;
	float modulatedAudio_ = 0.0f;
};