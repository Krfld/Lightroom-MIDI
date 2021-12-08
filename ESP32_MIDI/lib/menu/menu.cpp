#include "menu.h"

class Menu
{
private:
	static int menu;

public:
	static int getMenu()
	{
		return menu;
	}

	static void nextMenu()
	{
		if (menu == Calibration)
			menu = Basic;
		else
			menu++;
	}

	static void previusMenu()
	{
		if (menu == Basic)
			menu = Calibration;
		else
			menu--;
	}
};
