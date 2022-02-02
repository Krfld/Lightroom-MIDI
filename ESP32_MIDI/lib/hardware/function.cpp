#include "hardware.h"

Function::Function(function_t function) : _queue(xQueueCreate(QUEUE_SIZE, sizeof(ReadState))), _function(function)
{
	if (!_queue)
		log_i("{ERROR} [Function] xQueueCreate failed");

	if (!xTaskCreate(_task, "Function", configMINIMAL_STACK_SIZE * TASK_STACK_SIZE, this, 1, NULL))
		log_i("{ERROR} [Function] xTaskCreate failed");
}

Function::~Function() { log_i("~Function"); }

void Function::_task(void *pvParameters)
{
	Function *function = (Function *)pvParameters;

	ReadState state = Idle;
	for (;;)
	{
		xQueueReceive(function->_queue, &state, portMAX_DELAY);

		function->_function(state); //! Check if error (private function)

		//? Maybe delay
	}

	vTaskDelete(NULL);
}

void Function::sendFunction(ReadState state) { xQueueOverwrite(_queue, &state); }