#ifndef MENU_H
#define MENU_H

#include <map>

#include "button.h"
#include "rotary_encoder.h"

#define EDIT_BUTTONS_NUM 4
#define EDIT_ROTARY_ENCODERS_NUM 8

//* Devices
struct Devices
{
	Button buttons[EDIT_BUTTONS_NUM];
	RotaryEncoder rotaryEncoders[EDIT_ROTARY_ENCODERS_NUM];
};

//* Menus
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

	FIRST_MENU = Basic,
	LAST_MENU = Calibration,
	TOTAL_MENUS = 9
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

//* Sections
const std::map<Menus, int> Sections = {
	{Menus::Basic, 2},
	{Menus::ToneCurve, 1},
	{Menus::HSL_Color, 1},
	{Menus::ColorGrading, 1},
	{Menus::Detail, 2},
	{Menus::LensCorrections, 2},
	{Menus::Transform, 1},
	{Menus::Effects, 1},
	{Menus::Calibration, 1},
};

class Section
{
private:
	Section();
	static int section;

protected:
public:
	static int currentSection();
	static void nextSection();
	static void previousSection();
};

#endif // MENU_H