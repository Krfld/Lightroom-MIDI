#include "hardware.h"

GenericKnob::GenericKnob(Expander *expander, pin_t pinA, pin_t pinB) : _expander(expander), _pinA(pinA), _pinB(pinB)
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

	ReadState state = Idle;
	switch (oldState << 2 | _state)
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
		state = Idle;
		break;
	}

	if (state == Clockwise)
		_countClockwise++;
	else if (state == CounterClockwise)
		_countCounterClockwise++;

	if (_states++ < SENSITIVITY)
		return Idle;

	if (_countClockwise > _countCounterClockwise)
		state = Clockwise;
	else if (_countCounterClockwise > _countClockwise)
		state = CounterClockwise;

	_states = 0;
	_countClockwise = 0;
	_countCounterClockwise = 0;

	return state;
}

// ----------------------------------------------------------------------------------------------------

Knob::Knob(Expander *expander, pin_t pinA, pin_t pinB,
		   Expander *buttonExpander, pin_t buttonPin,
		   function_t function,
		   Led *led)
	: GenericKnob(expander, pinA, pinB),
	  GenericButton(buttonExpander, buttonPin),
	  Function(function),
	  _led(led) {}

Knob::~Knob() { log_i("~Knob"); }

void Knob::writeLed(WriteState state)
{
	if (_led)
		_led->writeLed(state);
}