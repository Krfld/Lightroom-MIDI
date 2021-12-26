#include "main.h"

#include "hardware.h"

void setup()
{
	Serial.begin(115200);
	Serial.println("Setup");

	//! Something wrong with i2c

	Devices::addExpander({0, 19, 18, 0x20});

	Devices::addLed({0, 0, 7});

	Serial.println("Ready");
}

void loop()
{
	Serial.println("Led on");
	Devices::_leds[0]->set(On);
	delay(3000);
	Serial.println("Led off");
	Devices::_leds[0]->set(Off);
	delay(3000);
}