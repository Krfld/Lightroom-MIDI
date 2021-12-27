#ifndef HARDWARE_H
#define HARDWARE_H

#include <map>

// #include "FreeRTOS.h"

#include "Adafruit_MCP23X17.h"

typedef uint8_t id_t;
typedef uint8_t pin_t;
typedef Adafruit_MCP23X17 Expander; // TODO Change to MCP23008

enum ReadState : uint8_t
{
	Idle = 0,
	Released = 0b10,
	Pressed = 0b01,
	Clockwise = 0b01 << 2,
	CounterClockwise = 0b10 << 2,
};

enum WriteState : uint8_t
{
	Off,
	On,
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

struct button_s
{
	id_t id;
	id_t expanderId;
	pin_t pin;
	led_s led;
};

struct knob_s
{
	id_t id;
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
	Expander *_expander = NULL;
	const pin_t _pin;

	QueueHandle_t _queueHandle = NULL;
	TaskHandle_t _taskHandle = NULL;
	static void _task(void *pvParameters);

	struct taskParameters_s
	{
		Expander *expander;
		pin_t pin;
		QueueHandle_t queueHandle;
	};

public:
	Led(Expander *expander, pin_t pin);

	// pin_t getPin();
	// Expander *getExpander();
	// TaskHandle_t getTaskHandle();
	// QueueHandle_t getQueueHandle();

	void write(WriteState value);

	bool init();
	void deinit();
};

// ----------------------------------------------------------------------------------------------------

class Button
{
private:
	Expander *_expander;
	const pin_t _pin;

	Led *_led;

	ReadState _state;

public:
	Button(Expander *expander, pin_t pin, Led *led);
	ReadState read();
	void write(WriteState state);
};

// ----------------------------------------------------------------------------------------------------

class Knob
{
private:
	Expander *_expander;
	const pin_t _pinA;
	const pin_t _pinB;

	Button *_button;
	Led *_led;

	uint8_t _pinState;

	uint8_t _readPins();

public:
	Knob(Expander *expander, pin_t pinA, pin_t pinB, Button *button, Led *led);
	ReadState read();
	void write(WriteState state);
};

// ----------------------------------------------------------------------------------------------------

class Devices
{
private:
	std::map<id_t, Expander *> _expanders;
	std::map<id_t, Button *> _buttons;
	std::map<id_t, Knob *> _knobs;

	Led *_setupLed(led_s led_s);
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