#include "hardware.h"

GenericKnob::GenericKnob(Expander *expander, pin_t pinA, pin_t pinB) : _expander(expander), _pinA(pinA), _pinB(pinB)
{
	_expander->pinMode(_pinA, INPUT);
	_expander->pinMode(_pinB, INPUT);

	_expander->digitalWrite(_pinA, Off);
	_expander->digitalWrite(_pinB, Off);

	_state = _readState();
}

GenericKnob::~GenericKnob() { log_i("~GenericKnob"); }

bits_t GenericKnob::_readState() { return _expander->digitalRead(_pinA) << 1 | _expander->digitalRead(_pinB) << 0; }

ReadState GenericKnob::readKnob()
{
	/*
	Debounce knob
	state -> (old)(old)(new)(new)

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

	bits_t oldState = _state;
	_state = _readState();

	switch (oldState | _state)
	{
	case 0b0001:
	case 0b0111:
	case 0b1000:
	case 0b1110:
		return Clockwise;
		break;

	case 0b0010:
	case 0b0100:
	case 0b1011:
	case 0b1101:
		return CounterClockwise;
		break;

	default:
		return Idle;
		break;
	}
}

// ----------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------

Knob::Knob(Expander *expander, pin_t pinA, pin_t pinB, DefaultButton *button, Led *led)
	: _expander(expander), _pinA(pinA), _pinB(pinB), _button(button), _led(led)
{
	_expander->pinMode(_pinA, INPUT_PULLUP);
	_expander->pinMode(_pinB, INPUT_PULLUP);

	_pinState = _readPins();
}

// ----------------------------------------------------------------------------------------------------

uint8_t Knob::_readPins() { return _expander->digitalRead(_pinA) << 1 | _expander->digitalRead(_pinB) << 0; }

// ----------------------------------------------------------------------------------------------------

ReadState Knob::read()
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

	ReadState turnState = Idle;

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
		turnState = Idle;
		break;
	}

	ReadState buttonState = Idle;
	if (_button)
		buttonState = _button->read();

	return (ReadState)(turnState | buttonState);
}

void Knob::write(WriteState state)
{
	if (_led)
		_led->write(state);
}