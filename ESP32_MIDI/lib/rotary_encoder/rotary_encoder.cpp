#include "rotary_encoder.h"

RotaryEncoder::RotaryEncoder(std::function<void()> *functions)
{
	for (int i = 0; i < 9; i++)
		this->functions.insert(std::make_pair(Menus(i + 1), functions[i]));

	// Define pins
}

void RotaryEncoder::pressed()
{
	value = DEFAULT_VALUE; // Reset

	// Send MIDI
}

void RotaryEncoder::released() {} // ...

void RotaryEncoder::rotated(RotationDirection rotation)
{
	if (rotation == RotationDirection::CLOCKWISE && value < MAX_VALUE)
		value++;
	else if (rotation == RotationDirection::COUNTER_CLOCKWISE && value > MIN_VALUE)
		value--;

	// Send MIDI
}