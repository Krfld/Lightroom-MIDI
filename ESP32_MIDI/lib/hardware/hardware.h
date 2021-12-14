#ifndef HARDWARE_H
#define HARDWARE_H

#include <Arduino.h>

#include "Adafruit_MCP23X17.h"

enum DeviceState : uint8_t
{
	Idle = 0,
	Released = 0b10,
	Pressed = 0b01,
	Clockwise = 0b01 << 2,
	CounterClockwise = 0b10 << 2,
};

enum LedState : uint8_t
{
	Off,
	On,
};

// ----------------------------------------------------------------------------------------------------

class Led
{
private:
	Adafruit_MCP23X17 *_mcp;
	uint8_t _pin;

public:
	Led(Adafruit_MCP23X17 *mcp, uint8_t pin);
	void set(LedState state);
};

// ----------------------------------------------------------------------------------------------------

class Button
{
private:
	Adafruit_MCP23X17 *_mcp;
	uint8_t _pin;

	Led *_led;

	DeviceState _state;

public:
	Button(Adafruit_MCP23X17 *mcp, uint8_t pin);
	Button(Adafruit_MCP23X17 *mcp, uint8_t pin, Led *led);
	DeviceState getState();
};

// ----------------------------------------------------------------------------------------------------

class Knob
{
private:
	Adafruit_MCP23X17 *_mcp;
	uint8_t _pinA;
	uint8_t _pinB;

	Button *_button;
	Led *_led;

	uint8_t _pinState;
	int8_t _value;

	uint8_t _readPins();

public:
	Knob(Adafruit_MCP23X17 *mcp, uint8_t pinA, uint8_t pinB);
	Knob(Adafruit_MCP23X17 *mcp, uint8_t pinA, uint8_t pinB, Led *led);
	Knob(Adafruit_MCP23X17 *mcp, uint8_t pinA, uint8_t pinB, Button *button);
	Knob(Adafruit_MCP23X17 *mcp, uint8_t pinA, uint8_t pinB, Button *button, Led *led);
	DeviceState getState();
	void set(LedState state);
};

#endif // HARDWARE_H