#ifndef HARDWARE_H
#define HARDWARE_H

#include <map>
#include "Adafruit_MCP23X17.h"

enum ReadState
{
	Idle = 0b00,
	Released = 0b10,
	Pressed = 0b01,
	Clockwise = 0b01 << 2,
	CounterClockwise = 0b10 << 2,
};
enum WriteState
{
	Off = LOW,
	On = HIGH,
};

typedef uint8_t id_t;
typedef uint8_t pin_t;
typedef uint8_t bits_t;
typedef Adafruit_MCP23X17 Expander;
typedef void (*function_t)(ReadState);

struct defaultExpander_s
{
	pin_t sda;
	pin_t scl;
	bits_t address;
};
struct defaultLed_s
{
	id_t expanderId = -1;
	pin_t pin = -1;
};
struct defaultButton_s
{
	id_t expanderId;
	pin_t pin;
};
struct defaultKnob_s
{
	id_t expanderId;
	pin_t pinA;
	pin_t pinB;
};
struct expander_s
{
	id_t id;
	defaultExpander_s defaultExpander;
};
struct led_s
{
	id_t id;
	defaultLed_s defaultLed;
};
struct button_s
{
	id_t id;
	defaultButton_s defaultButton;
	function_t function;
	defaultLed_s defaultLed;
};
struct knob_s
{
	id_t id;
	defaultKnob_s defaultKnob;
	defaultButton_s defaultButton;
	function_t function;
	defaultLed_s defaultLed;
};

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
	Button(Expander *expander, pin_t pin, function_t function, Led *led);
	~Button();

	void writeLed(WriteState state);
};

class Knob : public GenericKnob, public GenericButton, public Function
{
private:
	Led *_led;

public:
	Knob(Expander *expander, pin_t pinA, pin_t pinB, Expander *buttonExpander, pin_t buttonPin, function_t function, Led *led);
	~Knob();

	void writeLed(WriteState state);
};

class Devices
{
private:
	size_t I2C_FREQUENCY = 1.7e6;
	size_t TASKS_STACK_SIZE = 3;
	size_t DEBOUNCE_MS = 20;

	static void _buttonsTask(void *pvParameters);
	static void _knobsTask(void *pvParameters);

	std::map<id_t, Expander *> _expanders;
	std::map<id_t, Button *> _buttons;
	std::map<id_t, Knob *> _knobs;

	Expander *_getExpander(id_t id);
	Led *_setupLed(defaultLed_s defaultLed_s);

public:
	bool addExpander(expander_s expander_s);
	bool addButton(button_s button_s);
	bool addKnob(knob_s knob_s);

	bool removeExpander(id_t id);
	bool removeButton(id_t id);
	bool removeKnob(id_t id);

	bool init();
};

#endif // HARDWARE_H