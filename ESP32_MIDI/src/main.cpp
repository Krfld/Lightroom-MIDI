#include "main.h"

#include "hardware.h"

void setup()
{
	log_i("Setup");

	log_i("Expander: %d", Devices::addExpander({0, 22, 21, 0x20}));

	log_i("Led: %d", Devices::addLed({0, 0, 7}));

	log_i("Ready");
}

void loop()
{
	log_i("Led on");
	Devices::_leds[0]->set(On);
	delay(500);
	log_i("Led off");
	Devices::_leds[0]->set(Off);
	delay(500);
}