#include "hardware.h"

Button::Button(Adafruit_MCP23X17 *mcp, int pin, Led *led) : mcp(mcp), pin(pin), led(led)
{
	mcp->pinMode(pin, INPUT_PULLUP);
}

// ----------------------------------------------------------------------------------------------------

DeviceState Button::state()
{
	return (DeviceState)!mcp->digitalRead(pin);
}