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

// ----------------------------------------------------------------------------------------------------

class Led
{
private:
	id_t _id;
	Expander *_expander;
	const pin_t _pin;

	QueueHandle_t _queueHandle;

	static void _task(void *pvParameters);

public:
	Led(id_t id, Expander *expander, pin_t pin);

	void write(WriteState value);
};

// ----------------------------------------------------------------------------------------------------

class IButton
{
protected:
	Expander *_expander;
	pin_t _pin;
	ReadState _state;

public:
	virtual ReadState read() = 0;
	virtual void write(WriteState state) = 0;
};

class Button : public IButton
{
public:
	Button(Expander *expander, pin_t pin, Led *led) {}
	ReadState read()
	{
		log_i("read");
		return Idle;
	}
	void write(WriteState state)
	{
		log_i("write");
	}
};

// ----------------------------------------------------------------------------------------------------

#endif // HARDWARE_H