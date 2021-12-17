#include "hardware.h"

bool Devices::addExpander(id id, uint8_t address = 0x20)
{
	Expander expander = Expander();

	if (!expander->begin_I2C(address))
		return false;

	return _expanders.insert({id, expander}).second;
}

Expander Devices::getExpander(id id)
{
	try
	{
		return _expanders.at(id);
	}
	catch (const std::exception &e)
	{
		return NULL;
	}
}

size_t Devices::removeExpander(id id) { return _expanders.erase(id); }

// ----------------------------------------------------------------------------------------------------

Led *Devices::setLed(led_s led)
{
	try
	{
		Expander expander = getExpander(led.expanderId);

		return &Led(expander, led.pin);
	}
	catch (const std::exception &e)
	{
		return NULL;
	}
}

bool Devices::addLed(id id, led_s led)
{
	return _leds.insert({id, setLed(led)}).second;
}

size_t Devices::removeLed(id id) { return _leds.erase(id); }

// ----------------------------------------------------------------------------------------------------

Button *setButton(button_s button)
{
	try
	{
		Expander expander = getExpander(button.expanderId);

		return &Button(expander, button.pin, setLed(button.led));
	}
	catch (const std::exception &e)
	{
		return NULL;
	}
}

bool Devices::addButton(id id, button_s button)
{
	return _buttons.insert({id, setButton(button)}).second;
}

size_t Devices::removeButton(id id) { return _buttons.erase(id); }