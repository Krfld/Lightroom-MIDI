#include "menu.h"

Menus Menu::menu{Menus::Basic};

Menus Menu::currentMenu() { return menu; }

void Menu::nextMenu()
{
	if (menu == Menus::Calibration)
		menu = Menus::Basic;
	else
		menu = Menus((int)menu + 1);
}

void Menu::previousMenu()
{
	if (menu == Menus::Basic)
		menu = Menus::Calibration;
	else
		menu = Menus((int)menu - 1);
}
