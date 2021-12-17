#include "main.h"

// #include "hardware.h"

#include <map>

// Setup MCPs
// Setup devices

void setup()
{
	Serial.begin(115200);
	Serial.println("Setup");

	// Serial.println(map.erase(1));

	// Devices::addExpander(0, 0x20);

	// Adafruit_MCP23X17 mcp1;
	// mcp1.begin_I2C(0x20);
	// Button button1 = Button(&mcp1, 1);
	// Knob knob1 = Knob(&mcp1, 2, 3, &Button(&mcp1, 4));

	// void (*f[9])(int) = {bruh};
}

void loop()
{
	delay(2000);
}