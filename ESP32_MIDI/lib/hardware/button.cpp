#include "hardware.h"

Button::Button(Expander *expander, pin_t pin, Led *led) : _expander(expander), _pin(pin), _led(led)
{
	_expander->pinMode(_pin, INPUT_PULLUP);
}

// ----------------------------------------------------------------------------------------------------

ReadState Button::read()
{
	ReadState state = !_expander->digitalRead(_pin) ? Pressed : Released;

	if (state == _state)
		return Idle;

	return _state = state;
}

void Button::write(WriteState state)
{
	if (_led)
		_led->write(state);
}