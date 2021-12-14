#include "hardware.h"

Led::Led(Expander expander, uint8_t pin) : _expander(expander), _pin(pin)
{
	_expander->pinMode(_pin, OUTPUT);

	set(Off);
}

// ----------------------------------------------------------------------------------------------------

void Led::set(LedState state)
{
	_expander->digitalWrite(_pin, state);
}