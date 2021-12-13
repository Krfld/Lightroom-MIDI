#include "main.h"

#include "Adafruit_MCP23X17.h"

#include "hardware.h"

// Setup MCPs
// Setup devices

void setup()
{
	Serial.begin(115200);

	Adafruit_MCP23X17 mcp1;
	mcp1.begin_I2C(0x20); // TODO Check if retruns true

	Button button1 = Button(&mcp1, 1);
	Knob knob1 = Knob(&mcp1, 2, 3, &Button(&mcp1, 4));

	// void (*f[9])(int) = {bruh};
}

void loop()
{
	delay(2000);
}