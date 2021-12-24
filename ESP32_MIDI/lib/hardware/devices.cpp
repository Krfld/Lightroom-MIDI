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
Led *Devices::_setupLed(led_s led_s)
{
	MCP23017 *expander = _getExpander(led_s.expanderId);
	return expander != NULL ? new Led(expander, led_s.pin) : NULL;
}
Button *Devices::_setupButton(button_s button_s)
{
	MCP23017 *expander = _getExpander(button_s.expanderId);
	return expander != NULL ? new Button(expander, button_s.pin, _setupLed(button_s.led)) : NULL;
}
Knob *Devices::_setupKnob(knob_s knob_s)
{
	MCP23017 *expander = _getExpander(knob_s.expanderId);
	return expander != NULL ? new Knob(expander, knob_s.pinA, knob_s.pinB, _setupButton(knob_s.button), _setupLed(knob_s.led)) : NULL;
}

// ----------------------------------------------------------------------------------------------------

bool Devices::addExpander(expander_s expander_s)
{
	if (expander_s.sda < 0 || expander_s.scl < 0)
		return false;

	Wire.setPins(expander_s.sda, expander_s.scl);

	MCP23017 *expander = new MCP23017();
	if (!expander->begin_I2C(expander_s.address, &Wire))
		return false;
	return _expanders.insert({expander_s.id, expander}).second;
}
bool Devices::addLed(led_s led_s)
{
	Led *led = _setupLed(led_s);
	return led != NULL ? _leds.insert({led_s.id, led}).second : false;
}
bool Devices::addButton(button_s button_s)
{
	Button *button = _setupButton(button_s);
	return button != NULL ? _buttons.insert({button_s.id, button}).second : false;
}
bool Devices::addKnob(knob_s knob_s)
{
	Knob *knob = _setupKnob(knob_s);
	return knob != NULL ? _knobs.insert({knob_s.id, knob}).second : false;
}

// ----------------------------------------------------------------------------------------------------

bool Devices::removeExpander(id_t id) { return _expanders.erase(id) != 0; }
bool Devices::removeLed(id_t id) { return _leds.erase(id) != 0; }
bool Devices::removeButton(id_t id) { return _buttons.erase(id) != 0; }
bool Devices::removeKnob(id_t id) { return _knobs.erase(id) != 0; }