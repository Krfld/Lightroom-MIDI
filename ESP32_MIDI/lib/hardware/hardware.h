#ifndef HARDWARE_H
#define HARDWARE_H

#include <map>

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
	Led(Expander expander, pin_t pin);
	void set(LedState state);
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
	Button(Expander expander, pin_t pin, Led *led);
	DeviceState getState();
	void ledSet(LedState state);
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
	Knob(Expander expander, pin_t A, pin_t B, Button *button, Led *led);
	DeviceState getState();
	void setLed(LedState state);
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

	static Expander _getExpander(id_t id);
	static Led *_setupLed(led_s led);
	static Button *_setupButton(button_s button);
	static Knob *_setupKnob(knob_s knob);

public:
	static bool addExpander(id_t id, uint8_t address);
	static bool addLed(id_t id, led_s led);
	static bool addButton(id_t id, button_s button);
	static bool addKnob(id_t id, knob_s knob);

	static bool removeExpander(id_t id);
	static bool removeLed(id_t id);
	static bool removeButton(id_t id);
	static bool removeKnob(id_t id);
};

#endif // HARDWARE_H