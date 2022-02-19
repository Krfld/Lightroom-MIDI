#include "main.h"

void test(params_t params)
{
	switch (params.device)
	{
	case BUTTON:
		switch (params.state)
		{
		case Idle:
			log_i("Button %d Idle", params.id);
			break;
		case Pressed:
			log_i("Button %d Pressed", params.id);
			break;
		case Released:
			log_i("Button %d Released", params.id);
			break;
		default:
			break;
		}
		break;

	case KNOB:
		switch (params.state)
		{
		case Idle:
			log_i("Knob %d Idle", params.id);
			break;
		case Pressed:
			log_i("Knob %d Pressed", params.id);
			break;
		case Released:
			log_i("Knob %d Released", params.id);
			break;
		case Clockwise:
			log_i("Knob %d Clockwise", params.id);
			break;
		case CounterClockwise:
			log_i("Knob %d CounterClockwise", params.id);
			break;
		}
		break;
	}
}

Devices devices = Devices(&test);

void setup()
{
	log_i("Setup");

	devices.addExpander(0, 14, 12, 0x20);
	devices.addButton(0, button(0, 3));
	devices.addKnob(0, knob(0, 0, 1), button(0, 2));

	log_i("Free Heap Size: %d", esp_get_free_heap_size());

	log_i("Ready");
}

void loop()
{
}