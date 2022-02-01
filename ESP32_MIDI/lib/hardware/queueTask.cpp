#include "hardware.h"

QueueTask::QueueTask(const void (*function)(ReadState state)) : _queue(xQueueCreate(QUEUE_SIZE, sizeof(ReadState))), _function(function)
{
	if (!_queue)
		log_i("{ERROR} [QueueTask] xQueueCreate failed");

	if (!xTaskCreate(_task, "QueueTask", configMINIMAL_STACK_SIZE * TASK_STACK_SIZE, this, 1, NULL))
		log_i("{ERROR} [QueueTask] xTaskCreate failed");
}

QueueTask::~QueueTask() { log_i("~QueueTask"); }

void QueueTask::_task(void *pvParameters)
{
	QueueTask *queueTask = (QueueTask *)pvParameters;

	ReadState state = Idle;
	for (;;)
	{
		xQueueReceive(queueTask->_queue, &state, portMAX_DELAY);

		queueTask->_function(state);

		//? Maybe delay
	}

	vTaskDelete(NULL);
}

void QueueTask::sendQueue(ReadState state) { xQueueOverwrite(_queue, &state); }