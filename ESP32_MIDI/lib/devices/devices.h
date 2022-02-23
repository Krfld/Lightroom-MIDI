#ifndef DEVICES_H
#define DEVICES_H

#include <map>
#include "hardware.h"

typedef uint8_t id_t;

enum Device
{
	BUTTON,
	KNOB,
};

typedef struct
{
	Device device;
	id_t id;
	ReadState state;
} params_t;

typedef void (*callback_t)(params_t);

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

led_t led(id_t expanderId, pin_t pin);
button_t button(id_t expanderId, pin_t pin);
knob_t knob(id_t expanderId, pin_t pinA, pin_t pinB);

// ----------------------------------------------------------------------------------------------------

class Devices
{
private:
	enum Settings
	{
		DEBOUNCE_MS = 10,
		QUEUE_SIZE = 1 << 4, // 16
		FUNCTION_TASK_STACK_SIZE = 3,
		BUTTONS_TASK_STACK_SIZE = 3,
		KNOBS_TASK_STACK_SIZE = 3,
	};

	const callback_t _function;
	const QueueHandle_t _functionQueue;
	static void _functionTask(void *pvParameters);

	static void _buttonsTask(void *pvParameters);
	static void _knobsTask(void *pvParameters);

	std::map<id_t, Expander *> _expanders;
	std::map<id_t, Led *> _leds;
	std::map<id_t, Button *> _buttons;
	std::map<id_t, Knob *> _knobs;

	Expander *_getExpander(id_t id);
	void _sendFunction(params_t params);

public:
	Devices(callback_t function);
	~Devices();

	bool addExpander(id_t id, pin_t sda, pin_t scl, bits_t address);
	bool addLed(id_t id, led_t led_t);
	bool addButton(id_t id, button_t button_t);
	bool addKnob(id_t id, knob_t knob_t, button_t button_t);

	bool removeExpander(id_t id);
	bool removeLed(id_t id);
	bool removeButton(id_t id);
	bool removeKnob(id_t id);

	bool writeLed(id_t id, WriteState state);
};

#endif // DEVICES_H