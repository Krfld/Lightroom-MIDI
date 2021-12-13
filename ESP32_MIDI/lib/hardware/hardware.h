#ifndef HARDWARE_H
#define HARDWARE_H

#include <Arduino.h>

#include "Adafruit_MCP23X17.h"
#include "Encoder.h"

// _________
class Button
{
private:
	Adafruit_MCP23X17 *mcp;
	int pin;

public:
	Button(Adafruit_MCP23X17 *mcp, int pin);
	bool isPressed();
};

// ______
class Led
{
private:
	Adafruit_MCP23X17 *mcp;
	int pin;

public:
	Led(Adafruit_MCP23X17 *mcp, int pin);
	void set(bool state);
};

// ________________
class RotaryEncoder
{
private:
	Adafruit_MCP23X17 *mcp;
	// Encoder encoder;
	Button button;
	Led led;

public:
	RotaryEncoder(Adafruit_MCP23X17 *mcp, int encoderPinA, int encoderPinB, Button button, Led led);
	bool isPressed();
};

#endif // HARDWARE_H