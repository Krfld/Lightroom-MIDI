#ifndef GPIO_H
#define GPIO_H

#include <Arduino.h>

// {Led: {Row, Col}}

class Gpio final
{
private:
	Gpio();

protected:
public:
	void setLedState(int led, bool state);
};

#endif // GPIO_H