#include "menu.h"

Menus Menu::menu{Menus::Basic};

Menus Menu::getMenu() { return menu; }

void Menu::nextMenu()
{
	if (menu == Menus::Calibration)
		menu = Menus::Basic;
	else
		menu = Menus(static_cast<int>(menu) + 1);
}

void Menu::previousMenu()
{
	if (menu == Menus::Basic)
		menu = Menus::Calibration;
	else
		menu = Menus(static_cast<int>(menu) - 1);
}
