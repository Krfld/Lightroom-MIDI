#ifndef HARDWARE_H
#define HARDWARE_H

#include <Arduino.h>

#include "Adafruit_MCP23X17.h"

enum DeviceState
{
	Idle = 0b000,
	Pressed = 0b001,
	RotatedRight = 0b010,
	RotatedLeft = 0b100,
};

enum LedState
{
	Off,
	On,
};

// ----------------------------------------------------------------------------------------------------

class Led
{
private:
	Adafruit_MCP23X17 *mcp;
	int pin;

public:
	Led(Adafruit_MCP23X17 *mcp, int pin);
	void set(LedState state);
};

// ----------------------------------------------------------------------------------------------------

class Button
{
private:
	Adafruit_MCP23X17 *mcp;
	int pin;
	Led *led;

public:
	Button(Adafruit_MCP23X17 *mcp, int pin);
	Button(Adafruit_MCP23X17 *mcp, int pin, Led *led);
	DeviceState state();
};

// ----------------------------------------------------------------------------------------------------

class Knob
{
private:
	Adafruit_MCP23X17 *mcp;
	int pinA;
	int pinB;
	Button *button;
	Led *led;

	int value;

public:
	Knob(Adafruit_MCP23X17 *mcp, int pinA, int pinB);
	Knob(Adafruit_MCP23X17 *mcp, int pinA, int pinB, Led *led);
	Knob(Adafruit_MCP23X17 *mcp, int pinA, int pinB, Button *button);
	Knob(Adafruit_MCP23X17 *mcp, int pinA, int pinB, Button *button, Led *led);
	DeviceState state();
	void set(LedState state);
};

#endif // HARDWARE_H