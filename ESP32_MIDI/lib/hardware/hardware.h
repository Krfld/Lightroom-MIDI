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

struct expander_s
{
	id id;
	uint8_t address;
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
	pin pinA;
	pin pinB;
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

struct button_s
{
	id expanderId;
	pin pin;
};

class Button
{
private:
	Expander _expander;
	pin _pin;

	Led *_led;

	DeviceState _state;

public:
	Button(Expander, pin);
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
	Knob(Expander, pin pinA, pin pinB);
	Knob(Expander, pin pinA, pin pinB, Led *);
	Knob(Expander, pin pinA, pin pinB, Button *);
	Knob(Expander, pin pinA, pin pinB, Button *, Led *);
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

	static bool addExpander(id, uint8_t);
	static void removeExpander(id);

public:
	static bool addLed(led_s);
	static void removeLed(id);

	static bool addButton(button_s, led_s);
	static void removeButton(id);

	static bool addKnob(knob_s, button_s, led_s);
	static void removeKnob(id);
};

#endif // HARDWARE_H