#include "hardware.h"

Knob::Knob(Adafruit_MCP23X17 *mcp, uint8_t pinA, uint8_t pinB, Button *button, Led *led)
	: _mcp(mcp), _pinA(pinA), _pinB(pinB), _button(button), _led(led)
{
	_mcp->pinMode(_pinA, INPUT_PULLUP);
	_mcp->pinMode(_pinB, INPUT_PULLUP);

	_pinState = _readPins();
}

Knob::Knob(Adafruit_MCP23X17 *mcp, uint8_t pinA, uint8_t pinB, Led *led)
	: Knob(mcp, pinA, pinB, NULL, led) {}

Knob::Knob(Adafruit_MCP23X17 *mcp, uint8_t pinA, uint8_t pinB, Button *button)
	: Knob(mcp, pinA, pinB, button, NULL) {}

Knob::Knob(Adafruit_MCP23X17 *mcp, uint8_t pinA, uint8_t pinB)
	: Knob(mcp, pinA, pinB, NULL, NULL) {}

// ----------------------------------------------------------------------------------------------------

uint8_t Knob::_readPins() { return _mcp->digitalRead(_pinA) << 1 | _mcp->digitalRead(_pinB) << 0; }

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