#include "hardware.h"

Led::Led(Adafruit_MCP23X17 *mcp, uint8_t pin) : _mcp(mcp), _pin(pin)
{
	_mcp->pinMode(_pin, OUTPUT);

	set(Off);
}

// ----------------------------------------------------------------------------------------------------

void Led::set(LedState state)
{
	_mcp->digitalWrite(_pin, state);
}