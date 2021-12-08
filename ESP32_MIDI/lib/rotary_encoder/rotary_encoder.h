#ifndef ROTARY_ENCODER_H
#define ROTARY_ENCODER_H

#include <map>
#include <functional>

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
	const int DEFAULT_VALUE = 64; // 63/64
	const int MIN_VALUE = 0;

	int value = DEFAULT_VALUE;

	std::map<Menus, std::function<void()>> functions;

protected:
public:
	RotaryEncoder(std::function<void()> *);

	void pressed();
	void released();
	void rotated(RotationDirection);
};

#endif // ROTARY_ENCODER_H