#ifndef LIGHTROOM_H
#define LIGHTROOM_H

#include "button.h"
#include "rotary_encoder.h"

#define EDIT_BUTTONS 4
#define EDIT_ROTARY_ENCODERS 8

//* Devices
struct Devices
{
	Button buttons[EDIT_BUTTONS];
	RotaryEncoder rotaryEncoders[EDIT_ROTARY_ENCODERS];
};

#endif // LIGHTROOM_H