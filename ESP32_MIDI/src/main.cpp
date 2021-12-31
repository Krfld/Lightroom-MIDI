#include "main.h"

#include "hardware.h"

Devices devices;

void setup()
{
	log_i("Setup");

	// TODO Test removing devices to see if 'free' works properly

	devices.addExpander({0, 19, 18, 0x20});
	devices.addLed({0, 0, 7});

	log_i("Ready");
}

void loop()
{
	devices._leds[0]->write(On);
	delay(500);
	devices._leds[0]->write(Off);
	delay(500);
}