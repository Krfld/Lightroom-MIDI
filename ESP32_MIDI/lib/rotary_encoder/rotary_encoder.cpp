#include "rotary_encoder.h"

RotaryEncoder::RotaryEncoder(int id /*void (*functions[9])(int)*/) : id(id) // TODO Define pins
{
	// for (int i = 0; i < 9; i++)
	// 	this->functions.insert(std::make_pair(Menus(i + 1), functions[i]));

	for (int i = 1; i < (int)Menus::TOTAL_MENUS; i++)
		this->values[Menus(i + 1)] = this->DEFAULT_VALUE; // Set default values for each menu
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

	if (rotation == RotationDirection::CLOCKWISE && value < this->MAX_VALUE)
		value++;
	else if (rotation == RotationDirection::COUNTER_CLOCKWISE && value > this->MIN_VALUE)
		value--;

	this->values[Menu::currentMenu()] = value;

	// TODO Send MIDI
}

void RotaryEncoder::pressed()
{
	if (!isActive())
		return;

	this->values[Menu::currentMenu()] = this->DEFAULT_VALUE; // Reset

	// TODO Send MIDI
}

// void RotaryEncoder::released() {} // ...