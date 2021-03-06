#include "hardware.h"

GenericKnob::GenericKnob(Expander *expander, pin_t pinA, pin_t pinB)
	: _expander(expander), _pinA(pinA), _pinB(pinB)
{
	_expander->pinMode(_pinA, INPUT_PULLUP);
	_expander->pinMode(_pinB, INPUT_PULLUP);
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
	0	0		1	0
	0	1		0	0
	1	0		1	1
	1	1		0	1

	CounterClockwise
	0	0		0	1
	0	1		1	1
	1	0		0	0
	1	1		1	0
	*/

	bits_t oldState = _state;
	_state = _readState();

	ReadState state = Idle;
	switch (oldState << 2 | _state)
	{
	case 0b0010:
	case 0b0100:
	case 0b1011:
	case 0b1101:
		_counts++; // Clockwise
		break;

	case 0b0001:
	case 0b0111:
	case 0b1000:
	case 0b1110:
		_counts--; // CounterClockwise
		break;

	default:
		break;
	}

	if (abs(_counts) > THRESHOLD)
	{
		state = _counts > 0 ? Clockwise : CounterClockwise;
		_counts = 0;
	}

	return state;
}

// ----------------------------------------------------------------------------------------------------

Knob::Knob(Expander *expander, pin_t pinA, pin_t pinB, Expander *buttonExpander, pin_t buttonPin)
	: GenericKnob(expander, pinA, pinB), GenericButton(buttonExpander, buttonPin) {}

Knob::~Knob() { log_i("~Knob"); }
