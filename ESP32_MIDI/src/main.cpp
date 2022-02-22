#include "main.h"

void setup()
{
	log_i("Setup");

	Lightroom();

	log_i("Free Heap Size: %d", esp_get_free_heap_size());
	log_i("Ready");
}

void loop() {}