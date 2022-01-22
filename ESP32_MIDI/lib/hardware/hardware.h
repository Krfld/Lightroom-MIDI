#ifndef HARDWARE_H
#define HARDWARE_H

#include <map>
#include <Arduino.h>
#include "Adafruit_MCP23X17.h"

typedef uint8_t id_t;
typedef uint8_t pin_t;
typedef Adafruit_MCP23X17 Expander;

enum ReadState : uint8_t
{
	Idle = 0b00,
	Released = 0b10,
	Pressed = 0b01,
	Clockwise = 0b01 << 2,
	CounterClockwise = 0b10 << 2,
};

enum WriteState : uint8_t
{
	Off = LOW,
	On = HIGH,
};

struct expander_s
{
	id_t id;
	pin_t sda;
	pin_t scl;
	uint8_t address;
};
struct led_s
{
	id_t id;
	id_t expanderId;
	pin_t pin;
};
struct defaultButton_s
{
	id_t expanderId;
	pin_t pin;
};
struct button_s
{
	id_t id;
	defaultButton_s defaultButton;
	led_s led;
};
struct knob_s
{
	id_t id;
	id_t expanderId;
	pin_t pinA;
	pin_t pinB;
	led_s led;
	defaultButton_s defaultButton;
};

// struct taskParameters_s
// {
// 	id_t id;
// 	Expander *expander;
// 	pin_t pin;
// 	QueueHandle_t *queueHandle;
// };

// ----------------------------------------------------------------------------------------------------

class Led
{
protected:
	id_t _id;
	Expander *_expander;
	pin_t _pin;

public:
	Led(id_t id, Expander *expander, pin_t pin);

	void write(WriteState value);
};

// ----------------------------------------------------------------------------------------------------

class DefaultButton
{
protected:
	Expander *_expander;
	pin_t _pin;

	ReadState _state;

public:
	DefaultButton(Expander *expander, pin_t pin);
	ReadState read();
};

class Button : public DefaultButton
{
protected:
	Led *_led;

public:
	Button(Expander *expander, pin_t pin, Led *led);
	void write(WriteState state);
};

// ----------------------------------------------------------------------------------------------------

class Knob
{
protected:
	Expander *_expander;
	pin_t _pinA;
	pin_t _pinB;

	DefaultButton *_button;
	Led *_led;

	uint8_t _pinState;

	uint8_t _readPins();

public:
	Knob(Expander *expander, pin_t pinA, pin_t pinB, DefaultButton *button, Led *led);
	ReadState read();
	void write(WriteState state);
};

// ----------------------------------------------------------------------------------------------------

class Devices
{
protected:
	std::map<id_t, Expander *> _expanders;
	std::map<id_t, Button *> _buttons;
	std::map<id_t, Knob *> _knobs;

	Expander *_setupExpander(expander_s expander_s);
	Led *_setupLed(led_s led_s);
	DefaultButton *_setupDefaultButton(defaultButton_s defaultButton_s);
	Button *_setupButton(button_s button_s);
	Knob *_setupKnob(knob_s knob_s);

public:
	std::map<id_t, Led *> _leds; // Testing

	bool addExpander(expander_s expander_s);
	bool addLed(led_s led_s);
	bool addButton(button_s button_s);
	bool addKnob(knob_s knob_s);

	bool removeExpander(id_t id);
	bool removeLed(id_t id);
	bool removeButton(id_t id);
	bool removeKnob(id_t id);

	bool init();
	void deinit();
};

#endif // HARDWARE_H