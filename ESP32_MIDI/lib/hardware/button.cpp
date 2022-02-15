#include "hardware.h"

GenericButton::GenericButton(Expander *expander, pin_t pin) : _expander(expander), _pin(pin)
{
	_expander->pinMode(_pin, INPUT_PULLUP);
	_state = _readState();
}

GenericButton::~GenericButton() { log_i("~GenericButton"); }

bits_t GenericButton::_readState() { return !_expander->digitalRead(_pin); }

ReadState GenericButton::readButton()
{
	bits_t oldState = _state;
	_state = _readState();
	return oldState == _state ? Idle : (_state ? Pressed : Released);
}
// ----------------------------------------------------------------------------------------------------

Button::
	Button(Expander *expander,
		   pin_t pin,
		   function_t function)
	: GenericButton(expander, pin),
	  Function(function) {}

Button::~Button() { log_i("~Button"); }
