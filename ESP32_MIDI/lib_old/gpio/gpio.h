#ifndef GPIO_H
#define GPIO_H

#include <Arduino.h>
#include <wire.h>
#include "Adafruit_MCP23X17.h"

// {Led: {Row, Col}}

class Led
{
private:
	int address;
	int pin;

protected:
public:
	Led(int address, int pin);

	void set(bool state);
};

#endif // GPIO_H