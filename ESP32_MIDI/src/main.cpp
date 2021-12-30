#include "main.h"

#include "hardware.h"

//! Something wrong with expander

Devices devices;

void setup()
{
	log_i("Setup");

	// TODO Test removing devices to see if 'free' works properly

	if (devices.addExpander({0, 19, 18, 0x20}))
	{
		log_i("Expander added");
		devices.addLed({0, 0, 7});
	}

	log_i("Ready");
}

void loop()
{
	if (devices._leds[0])
	{
		log_i("Led %d", On);
		devices._leds[0]->write(On);
		delay(500);
		log_i("Led %d", Off);
		devices._leds[0]->write(Off);
		delay(500);
	}
}