#include "hardware.h"

Led::Led(Adafruit_MCP23X17 *mcp, int pin) : mcp(mcp), pin(pin)
{
	mcp->pinMode(pin, OUTPUT);
}

// ----------------------------------------------------------------------------------------------------

void Led::set(LedState state)
{
	mcp->digitalWrite(pin, state);
}