#include "rotary_encoder.h"

RotaryEncoder::RotaryEncoder(int id) : id(id) // TODO Define pins
{
	for (int i = 1; i < (int)Menus::TOTAL_MENUS; i++)
		this->values.at(Menus(i + 1)).at(Sections.at(Menus(i + 1))) = this->DEFAULT_VALUE; // Set default values for each menu
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

	int value = this->values.at(Menu::currentMenu()).at(Section::currentSection());

	if (rotation == RotationDirection::CLOCKWISE && value < this->MAX_VALUE)
		value++;
	else if (rotation == RotationDirection::COUNTER_CLOCKWISE && value > this->MIN_VALUE)
		value--;

	this->values.at(Menu::currentMenu()).at(Section::currentSection()) = value;

	// TODO Send MIDI
}

void RotaryEncoder::pressed()
{
	if (!isActive())
		return;

	this->values.at(Menu::currentMenu()).at(Section::currentSection()) = this->DEFAULT_VALUE; // Reset

	// TODO Send MIDI
}

// void RotaryEncoder::released() {} // ...