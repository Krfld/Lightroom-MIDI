#include "hardware.h"

Expander *Devices::_getExpander(id_t id) { return _expanders[id]; }

Led *Devices::_setupLed(defaultLed_s defaultLed_s)
{
	if (defaultLed_s.expanderId == (id_t)-1 || defaultLed_s.pin == (id_t)-1)
		return NULL;

	Expander *expander = _getExpander(defaultLed_s.expanderId);
	return expander ? new Led(expander, defaultLed_s.pin) : NULL;
}

// ----------------------------------------------------------------------------------------------------

bool Devices::addExpander(expander_s expander_s)
{
	Expander *expander = new Expander(new Adafruit_MCP23X17(), expander_s.defaultExpander.sda, expander_s.defaultExpander.scl, expander_s.defaultExpander.address);

	return _expanders.insert({expander_s.id, expander}).second;
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
	bool error = false;
	if (!xTaskCreate(_buttonsTask, "Buttons Task", configMINIMAL_STACK_SIZE * BUTTONS_TASK_STACK_SIZE, this, 1, NULL))
	{
		log_i("{ERROR} [Buttons Task] xTaskCreate failed");
		error = true;
	}

	if (!xTaskCreate(_knobsTask, "Knobs Task", configMINIMAL_STACK_SIZE * KNOBS_TASK_STACK_SIZE, this, 1, NULL))
	{
		log_i("{ERROR} [Knobs Task] xTaskCreate failed");
		error = true;
	}

	return error;
}

void Devices::_buttonsTask(void *pvParameters)
{
	Devices *devices = (Devices *)pvParameters;

	TickType_t ticks = xTaskGetTickCount();
	for (;;)
	{
		// Read buttons
		for (const std::pair<const id_t, Button *> &button : devices->_buttons)
		{
			ReadState state = button.second->readButton();
			if (state != Idle)
				button.second->sendFunction(state);
		}

		// Read knob buttons
		for (const std::pair<const id_t, Knob *> &knob : devices->_knobs)
		{
			ReadState state = knob.second->readButton();
			if (state != Idle)
				knob.second->sendFunction(state);
		}

		vTaskDelayUntil(&ticks, pdMS_TO_TICKS(devices->DEBOUNCE_MS));
	}

	vTaskDelete(NULL);
}

void Devices::_knobsTask(void *pvParameters)
{
	Devices *devices = (Devices *)pvParameters;

	TickType_t ticks = xTaskGetTickCount();
	for (;;)
	{
		for (const std::pair<const id_t, Knob *> &knob : devices->_knobs)
		{
			ReadState state = knob.second->readKnob();
			if (state != Idle)
				knob.second->sendFunction(state);
		}

		vTaskDelayUntil(&ticks, pdMS_TO_TICKS(1)); //? Delay
	}

	vTaskDelete(NULL);
}