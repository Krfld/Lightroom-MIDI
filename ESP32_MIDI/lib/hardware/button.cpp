#include "hardware.h"

DefaultButton::DefaultButton(Expander *expander, pin_t pin) : _expander(expander), _pin(pin), _state(Idle)
{
	_expander->pinMode(_pin, INPUT_PULLUP);
}

Button::Button(Expander *expander, pin_t pin, Led *led) : DefaultButton(expander, pin), _led(led)
{
	// Init queue and task
}

// ----------------------------------------------------------------------------------------------------

ReadState DefaultButton::read()
{
	ReadState state = !_expander->digitalRead(_pin) ? Pressed : Released;
	return state == _state ? Idle : _state = state;
}

void Button::write(WriteState state)
{
	if (_led)
		_led->write(state);
}