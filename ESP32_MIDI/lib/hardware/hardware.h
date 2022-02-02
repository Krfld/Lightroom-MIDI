#ifndef HARDWARE_H
#define HARDWARE_H

#include <map>
#include <Arduino.h>
#include "Adafruit_MCP23X17.h"

enum ReadState : bits_t
{
	Idle = 0b00,
	Released = 0b10,
	Pressed = 0b01,
	Clockwise = 0b01 << 2,
	CounterClockwise = 0b10 << 2,
};

enum WriteState : bits_t
{
	Off = LOW,
	On = HIGH,
};

struct expander_s
{
	id_t id;
	pin_t sda;
	pin_t scl;
	bits_t address;
};
struct led_s
{
	id_t id;
	id_t expanderId;
	pin_t pin;
};
struct button_s
{
	id_t id;
	id_t expanderId;
	pin_t pin;
};
struct knob_s
{
	id_t id;
	id_t expanderId;
	pin_t pinA;
	pin_t pinB;
	id_t buttonExpanderId;
	pin_t buttonPin;
};

typedef uint8_t id_t;
typedef uint8_t pin_t;
typedef uint8_t bits_t;
typedef Adafruit_MCP23X17 Expander;
typedef const void (*function_t)(ReadState state); //! Check if typedef works

// ----------------------------------------------------------------------------------------------------

class Function
{
private:
	size_t QUEUE_SIZE = 1;
	QueueHandle_t _queue;

	size_t TASK_STACK_SIZE = 3;
	static void _task(void *pvParameters);
	function_t _function;

public:
	Function(function_t function);
	~Function();

	void sendFunction(ReadState state);
};

class GenericButton
{
private:
	Expander *_expander;
	pin_t _pin;

	bits_t _state;
	bits_t _readState();

public:
	GenericButton(Expander *expander, pin_t pin);
	~GenericButton();

	ReadState readButton();
};

class GenericKnob
{
private:
	Expander *_expander;
	pin_t _pinA;
	pin_t _pinB;

	bits_t _state;
	bits_t _readState();

public:
	GenericKnob(Expander *expander, pin_t pinA, pin_t pinB);
	~GenericKnob();

	ReadState readKnob();
};

// ----------------------------------------------------------------------------------------------------

class Led
{
private:
	Expander *_expander;
	pin_t _pin;

public:
	Led(Expander *expander, pin_t pin);
	~Led();

	void writeLed(WriteState value);
};

class Button : public GenericButton, public Function
{
private:
	Led *_led;

public:
	Button(Expander *expander, pin_t pin, Led *led, function_t function);
	~Button();
};

class Knob : public GenericKnob, public GenericButton, public Function
{
private:
	Led *_led;

public:
	Knob(Expander *expander, pin_t pinA, pin_t pinB, Expander *buttonExpander, pin_t buttonPin, function_t function, Led *led);
	~Knob();
};

// ----------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------

/*
class DefaultButton
{
private:
	Expander *_expander;
	pin_t _pin;

	ReadState _state;

public:
	DefaultButton(Expander *expander, pin_t pin);
	ReadState read();
};

class Button : public DefaultButton
{
private:
	Led *_led;

public:
	Button(Expander *expander, pin_t pin, Led *led);
	void write(WriteState state);
};

// ----------------------------------------------------------------------------------------------------

class Knob
{
private:
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
*/

// ----------------------------------------------------------------------------------------------------

class Devices
{
private:
	std::map<id_t, Expander *> _expanders;
	std::map<id_t, Led *> _leds;
	std::map<id_t, Button *> _buttons;
	std::map<id_t, Knob *> _knobs;

	Expander *_setupExpander(expander_s expander_s);
	Led *_setupLed(led_s led_s);
	Button *_setupButton(button_s button_s, led_s led_s = (led_s){-1, -1, -1});
	Knob *_setupKnob(knob_s knob_s, led_s led_s = (led_s){-1, -1, -1});

public:
	bool addExpander(expander_s expander_s);
	bool addLed(led_s led_s);
	bool addButton(button_s button_s, led_s led_s = (led_s){-1, -1, -1});
	bool addKnob(knob_s knob_s, led_s led_s = (led_s){-1, -1, -1});

	bool removeExpander(id_t id);
	bool removeLed(id_t id);
	bool removeButton(id_t id);
	bool removeKnob(id_t id);

	bool init();
	void deinit();
};

#endif // HARDWARE_H