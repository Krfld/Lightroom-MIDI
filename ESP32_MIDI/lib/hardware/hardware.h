#ifndef HARDWARE_H
#define HARDWARE_H

#include "Adafruit_MCP23X17.h"

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

typedef uint8_t id_t;
typedef uint8_t pin_t;
typedef uint8_t bits_t;
typedef void (*function_t)(ReadState);

// ----------------------------------------------------------------------------------------------------

class Expander
{
private:
	enum i2c_frequencies_e : size_t
	{
		K100HZ = 100000,
		K400HZ = 400000,
		K1700HZ = 1700000,
	};

	SemaphoreHandle_t _semaphore;
	Adafruit_MCP23X17 *_expander;

public:
	Expander(Adafruit_MCP23X17 *expander, pin_t sda, pin_t scl, bits_t address, size_t frequency = K100HZ);
	~Expander();

	void pinMode(pin_t pin, uint8_t mode);
	void digitalWrite(pin_t pin, uint8_t value);
	uint8_t digitalRead(pin_t pin);
};

class Function
{
private:
	enum settings_e
	{
		QUEUE_SIZE = 1,
		TASK_STACK_SIZE = 3,
	};

	QueueHandle_t _queue;
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
	enum settings_s
	{
		THRESHOLD = 1,
	};

	Expander *_expander;
	pin_t _pinA;
	pin_t _pinB;

	bits_t _state;
	int8_t _counts = 0;
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

#endif // HARDWARE_H