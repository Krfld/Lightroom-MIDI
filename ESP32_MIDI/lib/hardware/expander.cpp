#include "hardware.h"

Expander::Expander(Adafruit_MCP23X17 *expander, pin_t sda, pin_t scl, bits_t address, size_t frequency)
	: _semaphore(xSemaphoreCreateMutex()), _expander(expander)
{
	if (!_semaphore)
		log_i("{ERROR} [Expander] xSemaphoreCreateMutex failed");

	xSemaphoreTake(_semaphore, portMAX_DELAY);

	TwoWire *wire = new TwoWire(0);
	wire->setPins(sda, scl);
	wire->setClock(frequency);

	if (!_expander->begin_I2C(address, wire))
		log_i("{ERROR} [Expander] begin_I2C failed");

	xSemaphoreGive(_semaphore);
}

Expander::~Expander() { log_i("~Expander"); }

void Expander::pinMode(pin_t pin, uint8_t mode)
{
	xSemaphoreTake(_semaphore, portMAX_DELAY);
	_expander->pinMode(pin, mode);
	xSemaphoreGive(_semaphore);
}

void Expander::digitalWrite(pin_t pin, uint8_t value)
{
	xSemaphoreTake(_semaphore, portMAX_DELAY);
	_expander->digitalWrite(pin, value);
	xSemaphoreGive(_semaphore);
}

uint8_t Expander::digitalRead(pin_t pin)
{
	xSemaphoreTake(_semaphore, portMAX_DELAY);
	uint8_t value = _expander->digitalRead(pin);
	xSemaphoreGive(_semaphore);
	return value;
}