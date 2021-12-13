#include "hardware.h"

RotaryEncoder::RotaryEncoder(Adafruit_MCP23X17 *mcp, int encoderPinA, int encoderPinB, Button button, Led led) : mcp(mcp), button(button), led(led) //, encoder()
{
}

bool RotaryEncoder::isPressed()
{
	return !mcp->digitalRead(button.isPressed());
}