#include "hardware.h"

Knob::Knob(Expander *expander, pin_t pinA, pin_t pinB, Button *button, Led *led)
	: _expander(expander), _pinA(pinA), _pinB(pinB), _button(button), _led(led)
{
	_expander->pinMode(_pinA, INPUT_PULLUP);
	_expander->pinMode(_pinB, INPUT_PULLUP);

	_pinState = _readPins();
}

// ----------------------------------------------------------------------------------------------------

uint8_t Knob::_readPins() { return _expander->digitalRead(_pinA) << 1 | _expander->digitalRead(_pinB) << 0; }

// ----------------------------------------------------------------------------------------------------

DeviceState Knob::getState()
{
	/*
	Debounce knob
	_pinState = (old)(old)(new)(new)

	old	old		new	new
	A	B		A	B

	Clockwise
	0	0		0	1
	0	1		1	1
	1	0		0	0
	1	1		1	0

	CounterClockwise
	0	0		1	0
	0	1		0	0
	1	0		1	1
	1	1		0	1
	*/

	DeviceState turnState = Idle;

	_pinState = (_pinState & 0b11) << 2 | _readPins();
	switch (_pinState)
	{
	case 0b0001:
	case 0b0111:
	case 0b1000:
	case 0b1110:
		turnState = Clockwise;
		break;
	case 0b0010:
	case 0b0100:
	case 0b1011:
	case 0b1101:
		turnState = CounterClockwise;
		break;

	default:
		// rotation = Idle;
		break;
	}

	DeviceState buttonState = Idle;
	if (_button != NULL)
		buttonState = _button->getState();

	return (DeviceState)(turnState | buttonState);
}

void Knob::setLed(LedState state)
{
	if (_led != NULL)
		_led->set(state);
}