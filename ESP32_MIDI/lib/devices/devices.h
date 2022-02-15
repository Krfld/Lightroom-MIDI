#ifndef DEVICES_H
#define DEVICES_H

#include <map>
#include "hardware.h"

typedef struct
{
	id_t expanderId;
	pin_t pin;
} led_t;

typedef struct
{
	id_t expanderId;
	pin_t pin;
} button_t;

typedef struct
{
	id_t expanderId;
	pin_t pinA;
	pin_t pinB;
} knob_t;

led_t *LED(id_t expanderId, pin_t pin);
button_t *BUTTON(id_t expanderId, pin_t pin);
knob_t *KNOB(id_t expanderId, pin_t pinA, pin_t pinB);

class Devices
{
private:
	enum settings_e
	{
		DEBOUNCE_MS = 10,
		BUTTONS_TASK_STACK_SIZE = 3,
		KNOBS_TASK_STACK_SIZE = 3,
	};

	static void _buttonsTask(void *pvParameters);
	static void _knobsTask(void *pvParameters);

	std::map<id_t, Expander *> _expanders;
	std::map<id_t, Led *> _leds;
	std::map<id_t, Button *> _buttons;
	std::map<id_t, Knob *> _knobs;

	Expander *_getExpander(id_t id);

public:
	Devices();
	~Devices();

	bool addExpander(id_t id, pin_t sda, pin_t scl, bits_t address);
	bool addLed(id_t id, led_t *led_t);
	bool addButton(id_t id, button_t *button_t, function_t function);
	bool addKnob(id_t id, knob_t *knob_t, button_t *button_t, function_t function);

	bool removeExpander(id_t id);
	bool removeLed(id_t id);
	bool removeButton(id_t id);
	bool removeKnob(id_t id);

	bool init();
};

#endif // DEVICES_H