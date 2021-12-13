#ifndef LIGHTROOM_H
#define LIGHTROOM_H

#include "button.h"
#include "rotary_encoder.h"

#define EDIT_BUTTONS 3
#define EDIT_ROTARY_ENCODERS 8

//* Devices
class Devices final
{
	const Button buttons[EDIT_BUTTONS] = {
		Button(1),
		Button(2),
		Button(3),
	};

	const RotaryEncoder rotaryEncoders[EDIT_ROTARY_ENCODERS] = {
		RotaryEncoder(1),
		RotaryEncoder(2),
		RotaryEncoder(3),
		RotaryEncoder(4),
		RotaryEncoder(5),
		RotaryEncoder(6),
		RotaryEncoder(7),
		RotaryEncoder(8),
	};
};

#endif // LIGHTROOM_H