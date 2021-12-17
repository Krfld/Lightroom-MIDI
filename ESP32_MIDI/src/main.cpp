#include "main.h"

#include "hardware.h"

#define tag "main"

void setup()
{
	Serial.begin(115200);

	ESP_LOGI(tag, "Setup");

	// Devices devices = Devices();
	// devices.addExpander(0, 0x20);

	// Devices::addExpander(0, 0x20);
	// Serial.println("1");
	// Devices::addExpander(1, 0x21);
	// Devices::addExpander(2, 0x22);

	// Serial.println(map.erase(1));

	// Devices::addExpander(0, 0x20);

	// Adafruit_MCP23X17 mcp1;
	// mcp1.begin_I2C(0x20);
	// Button button1 = Button(&mcp1, 1);
	// Knob knob1 = Knob(&mcp1, 2, 3, &Button(&mcp1, 4));

	// void (*f[9])(int) = {bruh};
	ESP_LOGI(tag, "Ready");
}

void loop()
{
	delay(2000);
}