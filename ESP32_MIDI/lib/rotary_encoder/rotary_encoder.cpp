#include "rotary_encoder.h"

RotaryEncoder::RotaryEncoder(/*void (*functions[9])(int)*/)
{
	// for (int i = 0; i < 9; i++)
	// 	this->functions.insert(std::make_pair(Menus(i + 1), functions[i]));

	// TODO Define pins

	for (int i = 0; i < (int)Menus::MENUS_COUNT; i++)
		this->values.insert(std::make_pair(Menus(i + 1), DEFAULT_VALUE)); // Reset values for each menu
}

bool RotaryEncoder::isActive()
{
	// TODO
}

void RotaryEncoder::rotated(RotationDirection rotation)
{
	if (!isActive())
		return;

	if (rotation == RotationDirection::CLOCKWISE && this->values[Menu::currentMenu()] < MAX_VALUE)
		this->values[Menu::currentMenu()]++;
	else if (rotation == RotationDirection::COUNTER_CLOCKWISE && this->values[Menu::currentMenu()] > MIN_VALUE)
		this->values[Menu::currentMenu()]--;

	// TODO Send MIDI
}

void RotaryEncoder::pressed()
{
	if (!isActive())
		return;

	this->values[Menu::currentMenu()] = DEFAULT_VALUE; // Reset

	// TODO Send MIDI
}

void RotaryEncoder::released() {} // ...