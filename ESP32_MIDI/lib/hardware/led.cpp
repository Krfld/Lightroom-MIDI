#include "hardware.h"

Led::Led(Expander *expander, pin_t pin) : _expander(expander), _pin(pin)
{
	_expander->pinMode(_pin, OUTPUT);
	_expander->digitalWrite(_pin, Off);
}

Led::~Led() { log_i("~Led"); }

void Led::writeLed(WriteState state) { _expander->digitalWrite(_pin, state); }