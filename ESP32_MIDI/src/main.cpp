#include "main.h"

Devices devices;

void f(ReadState state)
{
	switch (state)
	{
	case Idle:
		log_i("State: Idle");
		break;
	case Pressed:
		log_i("State: Pressed");
		break;
	case Released:
		log_i("State: Released");
		break;
	case Clockwise:
		log_i("State: Clockwise");
		break;
	case CounterClockwise:
		log_i("State: CounterClockwise");
		break;
	}
}

void setup()
{
	log_i("Setup");

	// TODO try cout

	devices.addExpander((expander_s){0, (defaultExpander_s){19, 18, 0x20}});
	devices.addKnob((knob_s){0, (defaultKnob_s){0, 0, 1}, (defaultButton_s){0, 2}, f});

	devices.init();

	log_i("Ready");
}

void loop()
{
}