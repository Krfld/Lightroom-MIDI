#include "hardware.h"

Button::Button(Adafruit_MCP23X17 *mcp, int pin) : mcp(mcp), pin(pin)
{
	mcp->pinMode(pin, INPUT_PULLUP);
}

bool Button::isPressed()
{
	return !mcp->digitalRead(pin);
}