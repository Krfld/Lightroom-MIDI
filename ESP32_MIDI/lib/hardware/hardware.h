#ifndef HARDWARE_H
#define HARDWARE_H

#include <map>
#include <Arduino.h>

#include "Adafruit_MCP23X17.h"

typedef uint8_t id_t;
typedef uint8_t pin_t;
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
	id_t expanderId;
	pin_t pin;
};

struct button_s
{
	id_t expanderId;
	pin_t pin;
	led_s led;
};

struct knob_s
{
	id_t expanderId;
	pin_t pinA;
	pin_t pinB;
	led_s led;
	button_s button;
};

// ----------------------------------------------------------------------------------------------------

class Led
{
private:
	Expander _expander;
	pin_t _pin;

public:
	Led(Expander, pin_t);
	void set(LedState);
};

// ----------------------------------------------------------------------------------------------------

class Button
{
private:
	Expander _expander;
	pin_t _pin;

	Led *_led;

	DeviceState _state;

public:
	Button(Expander, pin_t, Led *);
	DeviceState getState();
	void ledSet(LedState);
};

// ----------------------------------------------------------------------------------------------------

class Knob
{
private:
	Expander _expander;
	pin_t _pinA;
	pin_t _pinB;

	Button *_button;
	Led *_led;

	uint8_t _pinState;
	int8_t _value;

	uint8_t _readPins();

public:
	Knob(Expander, pin_t A, pin_t B, Button *, Led *);
	DeviceState getState();
	void ledSet(LedState);
};

// ----------------------------------------------------------------------------------------------------

class Devices
{
private:
	Devices();
	~Devices();

	static std::map<id_t, Expander> _expanders;
	static std::map<id_t, Led *> _leds;
	static std::map<id_t, Button *> _buttons;
	static std::map<id_t, Knob *> _knobs;

	static Expander _getExpander(id_t);

	static Led *_setupLed(led_s);
	static Button *_setupButton(button_s);
	static Knob *_setupKnob(knob_s);

public:
	// Add all expanders first
	static bool addExpander(id_t, uint8_t);
	static size_t removeExpander(id_t);

	static bool addLed(id_t, led_s);
	static size_t removeLed(id_t);

	static bool addButton(id_t, button_s);
	static size_t removeButton(id_t);

	static bool addKnob(id_t, knob_s);
	static size_t removeKnob(id_t);
};

#endif // HARDWARE_H