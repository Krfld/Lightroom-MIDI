#include "menu.h"

int Menu::getMenu()
{
	return menu;
};

void Menu::nextMenu()
{
	if (menu == Calibration)
		menu = Basic;
	else
		menu++;
};

void Menu::previousMenu()
{
	if (menu == Basic)
		menu = Calibration;
	else
		menu--;
};
