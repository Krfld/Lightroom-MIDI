#include "main.h"

#include <map>
#include "hardware.h"

Devices devices;

void setup()
{
	log_i("Setup");

	std::map<int, int> x;

	try
	{
		log_i("%d", x.erase(1));
	}
	catch (const std::exception &e)
	{
		log_i("Error");
	}

	log_i("%d", x.size());

	// devices.addExpander({0, 19, 18, 0x20});
	// devices.addLed({0, 0, 7});

	log_i("Ready");
}

void loop()
{
	// devices._leds[0]->write(On);
	// delay(500);
	// devices._leds[0]->write(Off);
	// delay(500);
}