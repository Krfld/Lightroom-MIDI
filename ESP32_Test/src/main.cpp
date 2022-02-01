#include <Arduino.h>
#include <esp32-hal.h>

#define LED 2

class QueueTask
{
protected:
	QueueHandle_t queue;
	static void task(void *pvParameters);


public:
	QueueTask()
	{
		queue = xQueueCreate(1, sizeof(int));
		xTaskCreate(task, "task", configMINIMAL_STACK_SIZE * 3, &queue, 1, NULL);
	}
	~QueueTask()
	{
		log_i("Destructor");
	}

	void send(int value)
	{
		xQueueOverwrite(queue, &value);
	}
};

void QueueTask::task(void *pvParameters)
{
	QueueHandle_t queue = *(QueueHandle_t *)pvParameters;
	int value = 0;

	log_i("Task %d", pvParameters);
	for (;;)
	{
		xQueueReceive(queue, &value, portMAX_DELAY);
		// log_i("Write: %d", value);
		digitalWrite(LED, value);
	}

	// vTaskDelete(NULL);
};

QueueTask queueTask;

void setup()
{
	log_i("Setup");

	pinMode(LED, OUTPUT);

	log_i("Ready");
}

int x = 0;

void loop()
{
	delay(100);
	x = 1 - x;
	queueTask.send(x);
}
