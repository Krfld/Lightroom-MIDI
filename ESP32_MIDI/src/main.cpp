#include "main.h"

//* Testing
#include "menu.h"
#include "rotary_encoder.h"

class Logic
{
private:
	Logic();

protected:
public:
	static void rotaryEncoderOnRotated(int);
	static void rotaryEncoderOnPressed();
	static void buttonOnPressed();
};

void bruh(int x)
{
	Serial.println("bruh");
}

void setup()
{
	Serial.begin(115200);

	// void (*f[9])(int) = {bruh};
}

void loop()
{
	delay(2000);
}
