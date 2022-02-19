#include "devices.h"

led_t led(id_t expanderId, pin_t pin) { return (led_t){expanderId, pin}; }
button_t button(id_t expanderId, pin_t pin) { return (button_t){expanderId, pin}; }
knob_t knob(id_t expanderId, pin_t pinA, pin_t pinB) { return (knob_t){expanderId, pinA, pinB}; }

Devices::Devices(function_t function)
	: _function(function), _functionQueue(xQueueCreate(QUEUE_SIZE, sizeof(params_t)))
{
	if (!_functionQueue)
		log_i("{ERROR} [Function] xQueueCreate failed");
	if (!xTaskCreate(_functionTask, "Function", configMINIMAL_STACK_SIZE * FUNCTION_TASK_STACK_SIZE, this, 1, NULL))
		log_i("{ERROR} [Function] xTaskCreate failed");

	if (!xTaskCreate(_buttonsTask, "Buttons Task", configMINIMAL_STACK_SIZE * BUTTONS_TASK_STACK_SIZE, this, 1, NULL))
		log_i("{ERROR} [Buttons Task] xTaskCreate failed");

	if (!xTaskCreate(_knobsTask, "Knobs Task", configMINIMAL_STACK_SIZE * KNOBS_TASK_STACK_SIZE, this, 1, NULL))
		log_i("{ERROR} [Knobs Task] xTaskCreate failed");
}

Devices::~Devices() { log_i("~Devices"); }

Expander *Devices::_getExpander(id_t id) { return _expanders[id]; }

void Devices::_sendFunction(params_t params)
{
	if (!xQueueSend(_functionQueue, &params, 0))
		log_i("{ERROR} [Devices] Funtion queue is full");
}

// ----------------------------------------------------------------------------------------------------

bool Devices::addExpander(id_t id, pin_t sda, pin_t scl, bits_t address)
{
	Expander *expander = new Expander(new Adafruit_MCP23X17(), sda, scl, address);
	return _expanders.insert({id, expander}).second;
}
bool Devices::addLed(id_t id, led_t led_t)
{
	Expander *expander = _getExpander(led_t.expanderId);
	if (!expander)
		return false;

	Led *led = new Led(expander, led_t.pin);
	return _leds.insert({id, led}).second;
}
bool Devices::addButton(id_t id, button_t button_t)
{
	Expander *expander = _getExpander(button_t.expanderId);
	if (!expander)
		return false;

	Button *button = new Button(expander, button_t.pin);
	return _buttons.insert({id, button}).second;
}
bool Devices::addKnob(id_t id, knob_t knob_t, button_t button_t)
{
	Expander *expander = _getExpander(knob_t.expanderId);
	if (!expander)
		return false;

	Expander *buttonExpander = _getExpander(button_t.expanderId);
	if (!buttonExpander)
		return false;

	Knob *knob = new Knob(expander, knob_t.pinA, knob_t.pinB, buttonExpander, button_t.pin);
	return _knobs.insert({id, knob}).second;
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

bool Devices::writeLed(id_t id, WriteState state)
{
	Led *led = _leds[id];
	if (!led)
		return false;

	led->writeLed(state);
	return true;
}

// ----------------------------------------------------------------------------------------------------

void Devices::_functionTask(void *param)
{
	Devices *devices = (Devices *)param;

	params_t params;
	for (;;)
	{
		xQueueReceive(devices->_functionQueue, &params, portMAX_DELAY);

		devices->_function(params);
	}

	vTaskDelete(NULL);
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
				devices->_sendFunction((params_t){BUTTON, button.first, state});
		}

		// Read knob buttons
		for (const std::pair<const id_t, Knob *> &knob : devices->_knobs)
		{
			ReadState state = knob.second->readButton();
			if (state != Idle)
				devices->_sendFunction((params_t){KNOB, knob.first, state});
		}

		vTaskDelayUntil(&ticks, pdMS_TO_TICKS(DEBOUNCE_MS));
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
				devices->_sendFunction((params_t){KNOB, knob.first, state});
		}

		vTaskDelayUntil(&ticks, pdMS_TO_TICKS(1));
	}

	vTaskDelete(NULL);
}