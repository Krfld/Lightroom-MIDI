#include "rotary_encoder.h"

RotaryEncoder::RotaryEncoder(int id /*void (*functions[9])(int)*/) : id(id)
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
	return true;
}

void RotaryEncoder::rotated(RotationDirection rotation)
{
	if (!isActive())
		return;

	int value = this->values[Menu::currentMenu()];

	if (rotation == RotationDirection::CLOCKWISE && value < MAX_VALUE)
		value++;
	else if (rotation == RotationDirection::COUNTER_CLOCKWISE && value > MIN_VALUE)
		value--;

	this->values[Menu::currentMenu()] = value;

	// TODO Send MIDI
}

void RotaryEncoder::pressed()
{
	if (!isActive())
		return;

	this->values[Menu::currentMenu()] = DEFAULT_VALUE; // Reset

	// TODO Send MIDI
}

// void RotaryEncoder::released() {} // ...