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
	const int MAX_VALUE = 127;
	const int DEFAULT_VALUE = 63; // 63/64
	const int MIN_VALUE = 0;

	std::map<Menus, int> values;

	/*std::map<Menus, void (*)(int)> functions;*/

protected:
public:
	RotaryEncoder(/*void (*[9])(int)*/);

	void pressed();
	void released();
	void rotated(RotationDirection);
};

#endif // ROTARY_ENCODER_H