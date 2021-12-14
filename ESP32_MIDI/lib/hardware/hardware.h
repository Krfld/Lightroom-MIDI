#ifndef HARDWARE_H
#define HARDWARE_H

#include <map>
#include <Arduino.h>

#include "Adafruit_MCP23X17.h"

typedef uint8_t id;
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

// ----------------------------------------------------------------------------------------------------

struct led_s
{
	id expanderId;
	uint8_t pin;
};

class Led
{
private:
	Expander _expander;
	uint8_t _pin;

public:
	Led(Expander expander, uint8_t pin);
	void set(LedState state);
};

// ----------------------------------------------------------------------------------------------------

struct button_s
{
	id expanderId;
	uint8_t pin;
};

class Button
{
private:
	Expander _expander;
	uint8_t _pin;

	Led *_led;

	DeviceState _state;

public:
	Button(Expander expander, uint8_t pin);
	Button(Expander expander, uint8_t pin, Led *led);
	DeviceState getState();
};

// ----------------------------------------------------------------------------------------------------

class Knob
{
private:
	Expander _expander;
	uint8_t _pinA;
	uint8_t _pinB;

	Button *_button;
	Led *_led;

	uint8_t _pinState;
	int8_t _value;

	uint8_t _readPins();

public:
	Knob(Expander expander, uint8_t pinA, uint8_t pinB);
	Knob(Expander expander, uint8_t pinA, uint8_t pinB, Led *led);
	Knob(Expander expander, uint8_t pinA, uint8_t pinB, Button *button);
	Knob(Expander expander, uint8_t pinA, uint8_t pinB, Button *button, Led *led);
	DeviceState getState();
	void set(LedState state);
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

public:
	static bool addExpander(id id, uint8_t address);
	static void removeExpander(id id);

	static bool addLed(id expanderId, uint8_t pin);

	//? Maybe use structs

	static bool addButton(id expanderId, uint8_t pin, id ledId);

	static bool addKnob(id expanderId, uint8_t pinA, uint8_t pinB, id buttonId, id ledId);
};

#endif // HARDWARE_H