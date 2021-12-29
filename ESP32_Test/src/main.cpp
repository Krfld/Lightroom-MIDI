#include <Arduino.h>

void task(void *args);

int x = false;
QueueHandle_t queue;

void setup()
{
	Serial.begin(115200);
	Serial.println("Setup");

	pinMode(13, OUTPUT);

	queue = xQueueCreate(1, sizeof(int));

	xTaskCreate(task, "task", configMINIMAL_STACK_SIZE, NULL, 1, NULL);

	Serial.println("Ready");
}

void loop()
{
	delay(100);
	xQueueSend(queue, &x, portMAX_DELAY);
	x = 1 - x;
}

void task(void *args)
{
	int value;

	for (;;)
	{
		xQueueReceive(queue, &value, portMAX_DELAY);
		Serial.print("Led: ");
		Serial.println(value);
		digitalWrite(13, value);
	}

	vTaskDelete(NULL);
}
