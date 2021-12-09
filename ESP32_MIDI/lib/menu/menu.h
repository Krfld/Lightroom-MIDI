#ifndef MENU_H
#define MENU_H

enum class Menus
{
	None,
	Basic = 1,
	ToneCurve,
	HSL_Color,
	ColorGrading,
	Detail,
	LensCorrections,
	Transform,
	Effects,
	Calibration,
	MENUS_COUNT = 9
};

class Menu
{
private:
	Menu();
	static Menus menu;

protected:
public:
	static Menus currentMenu();
	static void nextMenu();
	static void previousMenu();
};

#endif // MENU_H