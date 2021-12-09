#include "main.h"

//* Testing
#include "button.h"
#include "rotary_encoder.h"

void bruh(int x)
{
	Serial.println("bruh");
}

void setup()
{
	Serial.begin(115200);

	RotaryEncoder res[8] = {
		RotaryEncoder(1),
		RotaryEncoder(2),
		RotaryEncoder(3),
		RotaryEncoder(4),
		RotaryEncoder(5),
		RotaryEncoder(6),
		RotaryEncoder(7),
		RotaryEncoder(8),
	};

	Button btns[5] = {
		Button(1),
		Button(2),
		Button(3),
		Button(4),
		Button(5),
	};

	btns[0].pressed();

	Serial.println(Sections.at(Menus::Basic));
	// void (*f[9])(int) = {bruh};
}

void loop()
{
	delay(2000);
}