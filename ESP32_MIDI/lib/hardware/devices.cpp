#include "hardware.h"

// std::map<id_t, Expander *> Devices::_expanders;
// std::map<id_t, Led *> Devices::_leds;
// std::map<id_t, Button *> Devices::_buttons;
// std::map<id_t, Knob *> Devices::_knobs;

// ----------------------------------------------------------------------------------------------------

Expander *Devices::_getExpander(id_t id) { return _expanders[id]; }

Led *Devices::_setupLed(defaultLed_s defaultLed_s)
{
	if (defaultLed_s.expanderId < 0 || defaultLed_s.pin < 0)
		return NULL;

	Expander *expander = _getExpander(defaultLed_s.expanderId);
	return expander ? new Led(expander, defaultLed_s.pin) : NULL;
}

// Button *Devices::_setupButton(defaultButton_s defaultButton_s, defaultLed_s defaultLed_s)
// {
// 	Expander *expander = _expanders[defaultButton_s.expanderId];
// 	return expander ? new Button(expander, defaultButton_s.pin, _setupLed(defaultLed_s)) : NULL;
// }
// Knob *Devices::_setupKnob(defaultKnob_s defaultKnob_s, defaultButton_s defaultButton_s, defaultLed_s defaultLed_s)
// {
// 	Expander *buttonExpander = _expanders[defaultButton_s.expanderId];
// 	if (!buttonExpander)
// 		return NULL;

// 	Expander *expander = _expanders[defaultKnob_s.expanderId];
// 	if (!expander)
// 		return NULL;
// 	return expander ? new Knob(expander, defaultKnob_s.pinA, defaultKnob_s.pinB, _setupDefaultButton(knob_s.defaultButton), _setupLed(knob_s.led)) : NULL;
// }

// ----------------------------------------------------------------------------------------------------

bool Devices::addExpander(expander_s expander_s)
{
	Wire.setPins(expander_s.defaultExpander.sda, expander_s.defaultExpander.scl);
	// Wire.setClock(I2C_FREQUENCY);

	Expander *expander = new Expander();

	if (!expander->begin_I2C(expander_s.defaultExpander.address, &Wire))
		return false;

	return expander ? _expanders.insert({expander_s.id, expander}).second : false;
}
bool Devices::addButton(button_s button_s)
{
	Expander *expander = _getExpander(button_s.defaultButton.expanderId);
	if (!expander)
		return false;

	Button *button = new Button(expander, button_s.defaultButton.pin, button_s.function, _setupLed(button_s.defaultLed));
	return _buttons.insert({button_s.id, button}).second;
}
bool Devices::addKnob(knob_s knob_s)
{
	Expander *expander = _getExpander(knob_s.defaultKnob.expanderId);
	if (!expander)
		return false;

	Expander *buttonExpander = _getExpander(knob_s.defaultButton.expanderId);
	if (!buttonExpander)
		return false;

	Knob *knob = new Knob(expander, knob_s.defaultKnob.pinA, knob_s.defaultKnob.pinB, buttonExpander, knob_s.defaultButton.pin, knob_s.function, _setupLed(knob_s.defaultLed));
	return _knobs.insert({knob_s.id, knob}).second;
}

// ----------------------------------------------------------------------------------------------------

bool Devices::removeExpander(id_t id)
{
	Expander *expander = _expanders[id];
	if (expander)
		free(expander);
	return _expanders.erase(id) != 0;
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