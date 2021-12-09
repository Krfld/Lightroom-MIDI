#ifndef BUTTON_H
#define BUTTON_H

class Button
{
private:
	const int id;

	const int MAX_VELOCITY = 127;

protected:
public:
	Button(int);

	bool isActive();
	void pressed();
};

#endif // BUTTON_H