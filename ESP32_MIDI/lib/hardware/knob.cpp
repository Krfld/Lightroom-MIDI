#include "hardware.h"

Knob::Knob(Adafruit_MCP23X17 *mcp, int pinA, int pinB, Button *button, Led *led)
	: mcp(mcp), pinA(pinA), pinB(pinB), button(button), led(led)
{
	mcp->pinMode(pinA, INPUT_PULLUP);
	mcp->pinMode(pinB, INPUT_PULLUP);
}

Knob::Knob(Adafruit_MCP23X17 *mcp, int pinA, int pinB, Led *led)
	: Knob(mcp, pinA, pinB, NULL, led) {}

Knob::Knob(Adafruit_MCP23X17 *mcp, int pinA, int pinB, Button *button)
	: Knob(mcp, pinA, pinB, button, NULL) {}

Knob::Knob(Adafruit_MCP23X17 *mcp, int pinA, int pinB)
	: Knob(mcp, pinA, pinB, NULL, NULL) {}

// ----------------------------------------------------------------------------------------------------

DeviceState Knob::state()
{
	// TODO Debounce state machine
	return (DeviceState)(button->state());
}

void Knob::set(LedState state)
{
	led->set(state);
}