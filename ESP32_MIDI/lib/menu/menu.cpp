#include "menu.h"

class Menu
{

private:
	int menu;

public:
	int getMenu()
	{
		return menu;
	}

	void nextMenu()
	{
		if (menu == Calibration)
			menu = Basic;
		else
			menu++;
	}

	void previusMenu()
	{
		if (menu == Basic)
			menu = Calibration;
		else
			menu--;
	}
};
