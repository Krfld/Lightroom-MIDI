#include "hardware.h"

Knob::Knob(Expander expander, uint8_t pinA, uint8_t pinB, Button *button, Led *led)
	: _expander(expander), _pinA(pinA), _pinB(pinB), _button(button), _led(led)
{
	_expander->pinMode(_pinA, INPUT_PULLUP);
	_expander->pinMode(_pinB, INPUT_PULLUP);

	_pinState = _readPins();
}

Knob::Knob(Expander expander, uint8_t pinA, uint8_t pinB, Led *led)
	: Knob(expander, pinA, pinB, NULL, led) {}

Knob::Knob(Expander expander, uint8_t pinA, uint8_t pinB, Button *button)
	: Knob(expander, pinA, pinB, button, NULL) {}

Knob::Knob(Expander expander, uint8_t pinA, uint8_t pinB)
	: Knob(expander, pinA, pinB, NULL, NULL) {}

// ----------------------------------------------------------------------------------------------------

uint8_t Knob::_readPins() { return _expander->digitalRead(_pinA) << 1 | _expander->digitalRead(_pinB) << 0; }

// ----------------------------------------------------------------------------------------------------

DeviceState Knob::getState()
{
	/*
	pinState

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

	DeviceState state = Idle;

	_pinState = (_pinState & 0b11) << 2 | _readPins();
	switch (_pinState)
	{
	case 0b0001:
	case 0b0111:
	case 0b1000:
	case 0b1110:
		state = Clockwise;
		break;
	case 0b0010:
	case 0b0100:
	case 0b1011:
	case 0b1101:
		state = CounterClockwise;
		break;

	default:
		// rotation = Idle;
		break;
	}

	return (DeviceState)(state | _button->getState());
}

void Knob::set(LedState state)
{
	_led->set(state);
}