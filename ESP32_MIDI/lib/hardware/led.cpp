#include "hardware.h"

Led::Led(Expander *expander, pin_t pin) : _expander(expander), _pin(pin)
{
	_expander->pinMode(_pin, OUTPUT);

	write(Off);
}

// ----------------------------------------------------------------------------------------------------

// pin_t Led::getPin() { return _pin; }
// Expander *Led::getExpander() { return _expander; }
// TaskHandle_t Led::getTaskHandle() { return _taskHandle; }
// QueueHandle_t Led::getQueueHandle() { return _queueHandle; }

void Led::_task(void *pvParameters)
{
	Led::taskParameters_s *taskParameters = (Led::taskParameters_s *)pvParameters;

	WriteState state;

	for (;;)
	{
		xQueueReceive(taskParameters->queueHandle, &state, portMAX_DELAY);

		taskParameters->expander->digitalWrite(taskParameters->pin, state);
	}

	vTaskDelete(NULL);
}

// ----------------------------------------------------------------------------------------------------

// void Led::write(WriteState state) { _expander->digitalWrite(_pin, state); }
void Led::write(WriteState state)
{
	if (_queueHandle != NULL)
		xQueueOverwrite(_queueHandle, &state);
}

bool Led::init()
{
	// Queue

	if (_queueHandle)
	{
		Serial.println("{WARNING} Led queue already initialized");
		return false;
	}

	_queueHandle = xQueueCreate(1, sizeof(WriteState));

	if (!_queueHandle)
	{
		Serial.println("{WARNING} Led queue create failed");
		return false;
	}

	// Task

	if (_taskHandle)
	{
		Serial.println("{WARNING} Led task already initialized");
		return false;
	}

	if (!xTaskCreate(_task,
					 "Led",
					 configMINIMAL_STACK_SIZE,
					 new (Led::taskParameters_s){_expander, _pin, _queueHandle},
					 1,
					 &_taskHandle))
	{
		Serial.println("{WARNING} Led task create failed");
		vQueueDelete(_queueHandle);
		_queueHandle = NULL;
		return false;
	}

	return true;
}

void Led::deinit()
{
	if (_taskHandle)
	{
		vTaskDelete(_taskHandle);
		_taskHandle = NULL;
	}

	//? Might need to guarantee that task is deleted before queue

	if (_queueHandle)
	{
		vQueueDelete(_queueHandle);
		_queueHandle = NULL;
	}
}