#include "menus_sections.h"

//* Menu
Menus Menu::menu{Menus::FIRST_MENU};

Menus Menu::currentMenu() { return menu; }

void Menu::nextMenu()
{
	if (menu == Menus::LAST_MENU)
		menu = Menus::FIRST_MENU;
	else
		menu = Menus((int)menu + 1);
}

void Menu::previousMenu()
{
	if (menu == Menus::FIRST_MENU)
		menu = Menus::LAST_MENU;
	else
		menu = Menus((int)menu - 1);
}

//* Section
int Section::section{1};

int Section::currentSection() { return section; }

void Section::nextSection()
{
	if (Sections.at(Menu::currentMenu()) == section)
		section = 1;
	else
		section++;
}

void Section::previousSection()
{
	if (section == 1)
		section = Sections.at(Menu::currentMenu());
	else
		section--;
}