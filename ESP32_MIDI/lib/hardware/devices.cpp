#include "hardware.h"

Devices::Devices() {}
Devices::~Devices() {}

std::map<id_t, Expander> Devices::_expanders;
std::map<id_t, Led *> Devices::_leds;
std::map<id_t, Button *> Devices::_buttons;
std::map<id_t, Knob *> Devices::_knobs;

// ----------------------------------------------------------------------------------------------------

Expander Devices::_getExpander(id_t id)
{
	Expander expander = _expanders[id];
	return expander != NULL ? expander : NULL;
}

bool Devices::addExpander(id_t id, uint8_t address)
{
	Expander expander = new Adafruit_MCP23X17();

	if (!expander->begin_I2C(address))
		return false;

	return _expanders.insert({id, expander}).second;
}

size_t Devices::removeExpander(id_t id) { return _expanders.erase(id); }

// ----------------------------------------------------------------------------------------------------

Led *Devices::_setupLed(led_s led)
{
	Expander expander = _getExpander(led.expanderId);
	return expander != NULL ? new Led(expander, led.pin) : NULL;
}

bool Devices::addLed(id_t id, led_s led) { return _leds.insert({id, _setupLed(led)}).second; }

size_t Devices::removeLed(id_t id) { return _leds.erase(id); }

// ----------------------------------------------------------------------------------------------------

Button *Devices::_setupButton(button_s button)
{
	Expander expander = _getExpander(button.expanderId);
	return expander != NULL ? new Button(expander, button.pin, _setupLed(button.led)) : NULL;
}

bool Devices::addButton(id_t id, button_s button) { return _buttons.insert({id, _setupButton(button)}).second; }

size_t Devices::removeButton(id_t id) { return _buttons.erase(id); }

// ----------------------------------------------------------------------------------------------------

Knob *Devices::_setupKnob(knob_s knob)
{
	Expander expander = _getExpander(knob.expanderId);
	return expander != NULL ? new Knob(expander, knob.pinA, knob.pinB, _setupButton(knob.button), _setupLed(knob.led)) : NULL;
}

bool Devices::addKnob(id_t id, knob_s knob) { return _knobs.insert({id, _setupKnob(knob)}).second; }

size_t Devices::removeKnob(id_t id) { return _knobs.erase(id); }