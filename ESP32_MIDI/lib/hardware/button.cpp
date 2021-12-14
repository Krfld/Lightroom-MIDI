#include "hardware.h"

Button::Button(Adafruit_MCP23X17 *mcp, uint8_t pin, Led *led) : _mcp(mcp), _pin(pin), _led(led)
{
	_mcp->pinMode(_pin, INPUT_PULLUP);
}

// ----------------------------------------------------------------------------------------------------

DeviceState Button::getState()
{
	DeviceState state = !_mcp->digitalRead(_pin) ? Pressed : Released;

	if (state == _state)
		return Idle;

	return _state = state;
}