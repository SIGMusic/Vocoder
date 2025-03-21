#include "Modulator.h"

Modulator::Modulator(std::vector<float> audio, std::vector<float> amplitude) :
	audio_(audio),
	amplitude_(amplitude)
{
}

float Modulator::applyModulation() {
	for (unsigned int i = 0; i < audio_.size(); i++) {
		modulatedAudio_ += audio_[i] * amplitude_[i];
	}
	return modulatedAudio_;
}