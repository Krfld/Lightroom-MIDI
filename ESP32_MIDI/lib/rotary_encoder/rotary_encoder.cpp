#include "rotary_encoder.h"

RotaryEncoder::RotaryEncoder()
{
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
	value += static_cast<int>(rotation);
	// Send MIDI
}