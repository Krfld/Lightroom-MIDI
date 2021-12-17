#ifndef HARDWARE_H
#define HARDWARE_H

#include <map>
#include <Arduino.h>

#include "Adafruit_MCP23X17.h"

typedef uint8_t id;
typedef uint8_t pin;
typedef Adafruit_MCP23X17 *Expander;

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

struct led_s
{
	id expanderId;
	pin pin;
};

struct button_s
{
	id expanderId;
	pin pin;
	led_s led;
};

struct knob_s
{
	id expanderId;
	pin A;
	pin B;
	led_s led;
	button_s button;
};

// ----------------------------------------------------------------------------------------------------

class Led
{
private:
	Expander _expander;
	pin _pin;

public:
	Led(Expander, pin);
	void set(LedState);
};

// ----------------------------------------------------------------------------------------------------

class Button
{
private:
	Expander _expander;
	pin _pin;

	Led *_led;

	DeviceState _state;

public:
	Button(Expander, pin, Led *);
	DeviceState getState();
};

// ----------------------------------------------------------------------------------------------------

class Knob
{
private:
	Expander _expander;
	pin _pinA;
	pin _pinB;

	Button *_button;
	Led *_led;

	uint8_t _pinState;
	int8_t _value;

	uint8_t _readPins();

public:
	Knob(Expander, pin A, pin B, Button *, Led *);
	DeviceState getState();
	void set(LedState);
};

// ----------------------------------------------------------------------------------------------------

class Devices
{
private:
	Devices();

	static std::map<id, Expander> _expanders;
	static std::map<id, Led *> _leds;
	static std::map<id, Button *> _buttons;
	static std::map<id, Knob *> _knobs;

	// Add all expanders first
	static bool addExpander(id, uint8_t);
	static Expander getExpander(id);
	static size_t removeExpander(id);

public:
	static Led *setLed(led_s);
	static bool addLed(id, led_s);
	static size_t removeLed(id);

	static Button *setButton(button_s);
	static bool addButton(id, button_s);
	static size_t removeButton(id);

	static Knob *setKnob(knob_s);
	static bool addKnob(id, knob_s);
	static size_t removeKnob(id);
};

#endif // HARDWARE_H