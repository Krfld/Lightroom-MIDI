#ifndef HARDWARE_H
#define HARDWARE_H

#include <Arduino.h>

#include "Adafruit_MCP23X17.h"

// class Devices
// {
// private:
// 	Devices();

// 	static Adafruit_MCP23X17 *mcps;
// 	static Button *buttons;
// 	static Knob *knobs;
// 	static Led *leds;

// public:
// static int get
// };

// ----------------------------------------------------------------------------------------------------

class Led
{
private:
	Adafruit_MCP23X17 *mcp;
	int pin;

public:
	Led(Adafruit_MCP23X17 *mcp, int pin);
	void set(bool state);
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
	bool state();
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

public:
	Knob(Adafruit_MCP23X17 *mcp, int pinA, int pinB);
	Knob(Adafruit_MCP23X17 *mcp, int pinA, int pinB, Button *button);
	Knob(Adafruit_MCP23X17 *mcp, int pinA, int pinB, Button *button, Led *led);
	bool state();
};

#endif // HARDWARE_H