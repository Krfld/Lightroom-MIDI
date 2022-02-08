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

	devices.addExpander(0, 19, 18, 0x20);
	// devices.addKnob(0, new (knob_s){0, 0, 1}, new (button_s){0, 2}, f, NULL);
	devices.addButton(0, new (button_s){0, 3}, f, NULL);

	devices.init();

	log_i("Ready");
}

void loop()
{
}