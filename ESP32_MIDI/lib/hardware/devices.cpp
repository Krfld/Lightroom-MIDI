#include "hardware.h"

std::map<id_t, MCP23017 *> Devices::_expanders;
std::map<id_t, Led *> Devices::_leds;
std::map<id_t, Button *> Devices::_buttons;
std::map<id_t, Knob *> Devices::_knobs;

// ----------------------------------------------------------------------------------------------------

MCP23017 *Devices::_getExpander(id_t id)
{
	MCP23017 *expander = _expanders[id];
	return expander != NULL ? expander : NULL;
}
Led *Devices::_setupLed(led_s led)
{
	MCP23017 *expander = _getExpander(led.expanderId);
	return expander != NULL ? new Led(expander, led.pin) : NULL;
}
Button *Devices::_setupButton(button_s button)
{
	MCP23017 *expander = _getExpander(button.expanderId);
	return expander != NULL ? new Button(expander, button.pin, _setupLed(button.led)) : NULL;
}
Knob *Devices::_setupKnob(knob_s knob)
{
	MCP23017 *expander = _getExpander(knob.expanderId);
	return expander != NULL ? new Knob(expander, knob.pinA, knob.pinB, _setupButton(knob.button), _setupLed(knob.led)) : NULL;
}

// ----------------------------------------------------------------------------------------------------

bool Devices::addExpander(id_t id, uint8_t address)
{
	MCP23017 *expander = new MCP23017();
	if (!expander->begin_I2C(address))
		return false;
	return _expanders.insert({id, expander}).second;
}
bool Devices::addLed(id_t id, led_s led) { return _leds.insert({id, _setupLed(led)}).second; }
bool Devices::addButton(id_t id, button_s button) { return _buttons.insert({id, _setupButton(button)}).second; }
bool Devices::addKnob(id_t id, knob_s knob) { return _knobs.insert({id, _setupKnob(knob)}).second; }

// ----------------------------------------------------------------------------------------------------

bool Devices::removeExpander(id_t id) { return _expanders.erase(id) != 0; }
bool Devices::removeLed(id_t id) { return _leds.erase(id) != 0; }
bool Devices::removeButton(id_t id) { return _buttons.erase(id) != 0; }
bool Devices::removeKnob(id_t id) { return _knobs.erase(id) != 0; }