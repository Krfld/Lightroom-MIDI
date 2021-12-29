#include "main.h"

#include "hardware.h"

Devices devices;

void setup()
{
	Serial.begin(115200);
	Serial.println("Setup");

	//! Something wrong with i2c

	// TODO Test removing devices to see if 'free' works properly

	if (devices.addExpander({1, 19, 18, 0x20}))
	{
		Serial.println("Expander 1 added");
		if (devices.addLed({1, 1, 7}))
		{
			Serial.println("Led 1 added");
			if (devices._leds[1]->init())
			{
				Serial.println("Led 1 init");

				Serial.println("Led on");
				devices._leds[1]->write(On);
				delay(3000);
				Serial.println("Led off");
				devices._leds[1]->write(Off);
				delay(3000);
			}
		}
	}

	Serial.println(esp_get_free_heap_size());
	Serial.println("Ready");
}

void loop()
{
}