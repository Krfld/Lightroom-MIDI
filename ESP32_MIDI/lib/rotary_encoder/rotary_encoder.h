#ifndef ROTARY_ENCODER_H
#define ROTARY_ENCODER_H

#include <map>

#include "menu.h"

enum class RotationDirection
{
	CLOCKWISE = 1,
	COUNTER_CLOCKWISE = -1
};

class RotaryEncoder
{
private:
	const int id;

	const int MAX_VALUE = 127;
	const int DEFAULT_VALUE = 63; // 63/64
	const int MIN_VALUE = 0;

	std::map<Menus, int> values;

	/*std::map<Menus, void (*)(int)> functions;*/

protected:
public:
	RotaryEncoder(int /*void (*[9])(int)*/);

	bool isActive();
	void rotated(RotationDirection);
	void pressed();
	// void released();
};

#endif // ROTARY_ENCODER_H