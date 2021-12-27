#include "main.h"

#include "hardware.h"

Devices devices;

void setup()
{
	Serial.begin(115200);
	Serial.println("Setup");

	//! Something wrong with i2c

	// TODO Test removing devices to see if 'free' works properly

	bool e = devices.addExpander({1, 19, 18, 0x20});
	bool l = devices.addLed({1, 1, 7});
	bool i = devices._leds[1]->init();

	Serial.print("Expander: ");
	Serial.println(e);
	Serial.print("Led: ");
	Serial.println(l);
	Serial.print("Led init: ");
	Serial.println(i);

	Serial.println("Ready");
}

void loop()
{
	Serial.println("Led on");
	devices._leds[1]->write(On);
	delay(3000);
	Serial.println("Led off");
	devices._leds[1]->write(Off);
	delay(3000);
}