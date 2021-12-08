#ifndef ROTARY_ENCODER_H
#define ROTARY_ENCODER_H

enum class RotationDirection
{
	CLOCKWISE = 1,
	COUNTER_CLOCKWISE = -1
};

class RotaryEncoder
{
private:
	const int DEFAULT_VALUE = 64;

	int value = DEFAULT_VALUE;

protected:
public:
	RotaryEncoder();

	void pressed();
	void released();
	void rotated(RotationDirection rotation);
};

#endif // ROTARY_ENCODER_H