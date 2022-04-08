#ifndef HARDWARE_H
#define HARDWARE_H

#include "Adafruit_MCP23X17.h"

typedef uint8_t pin_t;
typedef uint8_t bits_t;

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

// ----------------------------------------------------------------------------------------------------

class Expander
{
private:
	enum I2C_frequencies
	{
		K100HZ = 100000,
		K400HZ = 400000,
		K1700HZ = 1700000,
	};

	Adafruit_MCP23X17 *_expander;
	const SemaphoreHandle_t _semaphore;

public:
	Expander(Adafruit_MCP23X17 *expander, pin_t sda, pin_t scl, bits_t address, size_t frequency = K100HZ);
	~Expander();

	void pinMode(pin_t pin, uint8_t mode);
	void digitalWrite(pin_t pin, uint8_t value);
	uint8_t digitalRead(pin_t pin);
};

class GenericButton
{
private:
	Expander *_expander;
	const pin_t _pin;

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
	enum Settings
	{
		THRESHOLD = 1,
	};

	Expander *_expander;
	const pin_t _pinA;
	const pin_t _pinB;

	bits_t _state;
	int8_t _counts = 0;
	bits_t _readState();

public:
	GenericKnob(Expander *expander, pin_t pinA, pin_t pinB);
	~GenericKnob();

	ReadState readKnob();
};

// ----------------------------------------------------------------------------------------------------

class Led // TODO change to LED strip
{
private:
	Expander *_expander;
	const pin_t _pin;

public:
	Led(Expander *expander, pin_t pin);
	~Led();

	void writeLed(WriteState value);
};

class Button : public GenericButton
{
private:
public:
	Button(Expander *expander, pin_t pin);
	~Button();
};

class Knob : public GenericKnob, public GenericButton
{
private:
public:
	Knob(Expander *expander, pin_t pinA, pin_t pinB, Expander *buttonExpander, pin_t buttonPin);
	~Knob();
};

#endif // HARDWARE_H