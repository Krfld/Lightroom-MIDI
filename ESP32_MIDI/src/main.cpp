#include "main.h"

#include "hardware.h"

void setup()
{
	log_i("Setup");

	Devices::addExpander(0, 0x20);
	Devices::removeExpander(0);

	log_i("Ready");
}

void loop()
{
	delay(2000);
}