#include "main.h"

//* Testing
#include "menu.h"
#include "rotary_encoder.h"

void bruh()
{
	Serial.println("bruh");
}

void setup()
{
	Serial.begin(115200);

	std::function<void()> functions[9] = {bruh};
	RotaryEncoder re(functions);
}

void loop()
{
	delay(2000);
}
