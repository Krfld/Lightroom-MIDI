#include "hardware.h"

Led::Led(id_t id, Expander *expander, pin_t pin) : _id(id), _expander(expander), _pin(pin)
{
	_expander->pinMode(_pin, OUTPUT);
	_expander->digitalWrite(_pin, Off);

	// if (!(_queueHandle = xQueueCreate(1, sizeof(WriteState))))
	// 	log_i("{ERROR} [Led %d] xQueueCreate failed", _id);

	// if (!xTaskCreate(_task, "Led Task", configMINIMAL_STACK_SIZE * 3, new (taskParameters_s){_id, _expander, _pin, &_queueHandle}, 1, &_taskHandle))
	// 	log_i("{ERROR} [Led %d] xTaskCreate failed", _id);
}

// ----------------------------------------------------------------------------------------------------

// void Led::_task(void *pvParameters)
// {
// 	taskParameters_s *taskParameters = (taskParameters_s *)pvParameters;

// 	WriteState state = Off;
// 	for (;;)
// 	{
// 		xQueueReceive(*taskParameters->queueHandle, &state, portMAX_DELAY);

// 		taskParameters->expander->digitalWrite(taskParameters->pin, state);
// 	}

// 	vTaskDelete(NULL);
// }

// ----------------------------------------------------------------------------------------------------

void Led::write(WriteState state) { _expander->digitalWrite(_pin, state); }