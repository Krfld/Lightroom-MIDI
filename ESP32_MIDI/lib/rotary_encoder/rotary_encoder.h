#ifndef ROTARY_ENCODER_H
#define ROTARY_ENCODER_H

#include <map>

#include "menus_sections.h"

enum class RotationDirection
{
	CLOCKWISE = 1,
	COUNTER_CLOCKWISE = -1
};

enum class RotaryEncoderState
{
	Pressed,
	Rotated
};

class RotaryEncoder
{
private:
	const int id;

	const int MAX_VALUE = 127;
	const int DEFAULT_VALUE = 63; // 63/64
	const int MIN_VALUE = 0;

	std::map<Menus, std::map<int, int>> values; // {Menu: {Section: value}}

	// std::map<Menus, std::map<int, std::map<RotaryEncoderState, void (*)()>>> functions;

protected:
public:
	RotaryEncoder(int);

	bool isActive();
	void rotated(RotationDirection);
	void pressed();
	// void released();
};

#endif // ROTARY_ENCODER_H