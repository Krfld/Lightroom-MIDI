#include "hardware.h"

// std::map<id_t, Expander *> Devices::_expanders;
// std::map<id_t, Led *> Devices::_leds;
// std::map<id_t, Button *> Devices::_buttons;
// std::map<id_t, Knob *> Devices::_knobs;

// ----------------------------------------------------------------------------------------------------

Expander *Devices::_setupExpander(expander_s expander_s)
{
	if (expander_s.sda < 0 || expander_s.scl < 0)
		return NULL;

	Wire.setPins(expander_s.sda, expander_s.scl);
	// Wire.setClock(I2C_FREQUENCY);

	Expander *expander = new Expander();
	return expander->begin_I2C(expander_s.address, &Wire) ? expander : NULL;
}
Led *Devices::_setupLed(led_s led_s)
{
	Expander *expander = _expanders[led_s.expanderId];
	return expander ? new Led(expander, led_s.pin) : NULL;
}
Button *Devices::_setupButton(button_s button_s, led_s led_s)
{
	//!...
	Expander *expander = _expanders[button_s.expanderId];
	return expander ? new Button(expander, button_s.pin, _setupLed(button_s.led)) : NULL;
}
// Knob *Devices::_setupKnob(knob_s knob_s)
// {
// 	Expander *expander = _expanders[knob_s.expanderId];
// 	return expander ? new Knob(expander, knob_s.pinA, knob_s.pinB, _setupDefaultButton(knob_s.defaultButton), _setupLed(knob_s.led)) : NULL;
// }

// ----------------------------------------------------------------------------------------------------

bool Devices::addExpander(expander_s expander_s)
{
	Expander *expander = _setupExpander(expander_s);
	return expander ? _expanders.insert({expander_s.id, expander}).second : false;
}
bool Devices::addLed(led_s led_s)
{
	Led *led = _setupLed(led_s);
	return led ? _leds.insert({led_s.id, led}).second : false;
}
bool Devices::addButton(button_s button_s, led_s led_s = (led_s){-1, -1, -1})
{
	Expander *expander = _expanders[button_s.expanderId];
	if (!expander)
		return false;

	Button *button = _setupButton(button_s);
	return button ? _buttons.insert({button_s.id, button}).second : false;
}
bool Devices::addKnob(knob_s knob_s, led_s led_s = (led_s){-1, -1, -1})
{
	Knob *knob = _setupKnob(knob_s);
	return knob ? _knobs.insert({knob_s.id, knob}).second : false;
}

// ----------------------------------------------------------------------------------------------------

bool Devices::removeExpander(id_t id)
{
	Expander *expander = _expanders[id];
	if (expander)
		free(expander);
	return _expanders.erase(id) != 0;
}
bool Devices::removeLed(id_t id)
{
	Led *led = _leds[id];
	if (led)
		free(led);
	return _leds.erase(id) != 0;
}
bool Devices::removeButton(id_t id)
{
	Button *button = _buttons[id];
	if (button)
		free(button);
	return _buttons.erase(id) != 0;
}
bool Devices::removeKnob(id_t id)
{
	Knob *knob = _knobs[id];
	if (knob)
		free(knob);
	return _knobs.erase(id) != 0;
}

// ----------------------------------------------------------------------------------------------------

bool Devices::init()
{
	// TODO init tasks to read pins
	return false;
}

void Devices::deinit()
{
}