#include "hardware.h"

Button::Button(Expander expander, uint8_t pin, Led *led) : _expander(expander), _pin(pin), _led(led)
{
	_expander->pinMode(_pin, INPUT_PULLUP);
}

// ----------------------------------------------------------------------------------------------------

DeviceState Button::getState()
{
	DeviceState state = !_expander->digitalRead(_pin) ? Pressed : Released;

	if (state == _state)
		return Idle;

	return _state = state;
}