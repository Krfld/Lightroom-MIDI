#ifndef LIGHTROOM_H
#define LIGHTROOM_H

//#include midi

#include <map>
#include "devices.h"

// #define BASIC "Basic"
// #define TONE_CURVE "Tone Curve"
// #define HSL_COLOR "HSL/Color"
// #define COLOR_GRADING "Color Grading"
// #define DETAIL "Detail"
// #define LENS_CORRECTION "Lens Correction"
// #define TRANSFORM "Transform"
// #define EFFECTS "Effects"
// #define CALIBRATION "Calibration"

enum Menu
{
	Basic = 1,
	ToneCurve,
	HSL_Color,
	ColorGrading,
	Detail,
	LensCorrection,
	Transform,
	Effects,
	Calibration,
	FIRST_MENU = Basic,
	LAST_MENU = Calibration,
};

const std::map<Menu, id_t> SubMenus = {
	{Basic, 2},
	{ToneCurve, 1},
	{HSL_Color, 1},
	{ColorGrading, 1},
	{Detail, 2},
	{LensCorrection, 2},
	{Transform, 1},
	{Effects, 1},
	{Calibration, 1},
};

typedef struct
{
	Menu menu;
	id_t subMenu;
} current_t;

typedef void (*buttonFunction_t)();
typedef void (*knobFunction_t)();

const std::map<id_t, std::map<Menu, buttonFunction_t>> buttonsFunctions = {
	{1,
	 {{Basic, []() {}},
	  {ToneCurve, []() {}},
	  {HSL_Color, []() {}},
	  {ColorGrading, []() {}},
	  {Detail, []() {}},
	  {LensCorrection, []() {}},
	  {Transform, []() {}},
	  {Effects, []() {}},
	  {Calibration, []() {}}}},
	{2,
	 {{Basic, []() {}},
	  {ToneCurve, []() {}},
	  {HSL_Color, []() {}},
	  {ColorGrading, []() {}},
	  {Detail, []() {}},
	  {LensCorrection, []() {}},
	  {Transform, []() {}},
	  {Effects, []() {}},
	  {Calibration, []() {}}}},
	{3,
	 {{Basic, []() {}},
	  {ToneCurve, []() {}},
	  {HSL_Color, []() {}},
	  {ColorGrading, []() {}},
	  {Detail, []() {}},
	  {LensCorrection, []() {}},
	  {Transform, []() {}},
	  {Effects, []() {}},
	  {Calibration, []() {}}}},
	{4,
	 {{Basic, []() {}},
	  {ToneCurve, []() {}},
	  {HSL_Color, []() {}},
	  {ColorGrading, []() {}},
	  {Detail, []() {}},
	  {LensCorrection, []() {}},
	  {Transform, []() {}},
	  {Effects, []() {}},
	  {Calibration, []() {}}}},
	{5,
	 {{Basic, []() {}},
	  {ToneCurve, []() {}},
	  {HSL_Color, []() {}},
	  {ColorGrading, []() {}},
	  {Detail, []() {}},
	  {LensCorrection, []() {}},
	  {Transform, []() {}},
	  {Effects, []() {}},
	  {Calibration, []() {}}}},
	{6,
	 {{Basic, []() {}},
	  {ToneCurve, []() {}},
	  {HSL_Color, []() {}},
	  {ColorGrading, []() {}},
	  {Detail, []() {}},
	  {LensCorrection, []() {}},
	  {Transform, []() {}},
	  {Effects, []() {}},
	  {Calibration, []() {}}}},
	{7,
	 {{Basic, []() {}},
	  {ToneCurve, []() {}},
	  {HSL_Color, []() {}},
	  {ColorGrading, []() {}},
	  {Detail, []() {}},
	  {LensCorrection, []() {}},
	  {Transform, []() {}},
	  {Effects, []() {}},
	  {Calibration, []() {}}}},
	{8,
	 {{Basic, []() {}},
	  {ToneCurve, []() {}},
	  {HSL_Color, []() {}},
	  {ColorGrading, []() {}},
	  {Detail, []() {}},
	  {LensCorrection, []() {}},
	  {Transform, []() {}},
	  {Effects, []() {}},
	  {Calibration, []() {}}}},
	{9,
	 {{Basic, []() {}},
	  {ToneCurve, []() {}},
	  {HSL_Color, []() {}},
	  {ColorGrading, []() {}},
	  {Detail, []() {}},
	  {LensCorrection, []() {}},
	  {Transform, []() {}},
	  {Effects, []() {}},
	  {Calibration, []() {}}}},
	{10,
	 {{Basic, []() {}},
	  {ToneCurve, []() {}},
	  {HSL_Color, []() {}},
	  {ColorGrading, []() {}},
	  {Detail, []() {}},
	  {LensCorrection, []() {}},
	  {Transform, []() {}},
	  {Effects, []() {}},
	  {Calibration, []() {}}}},
	{11,
	 {{Basic, []() {}},
	  {ToneCurve, []() {}},
	  {HSL_Color, []() {}},
	  {ColorGrading, []() {}},
	  {Detail, []() {}},
	  {LensCorrection, []() {}},
	  {Transform, []() {}},
	  {Effects, []() {}},
	  {Calibration, []() {}}}},
	{12,
	 {{Basic, []() {}},
	  {ToneCurve, []() {}},
	  {HSL_Color, []() {}},
	  {ColorGrading, []() {}},
	  {Detail, []() {}},
	  {LensCorrection, []() {}},
	  {Transform, []() {}},
	  {Effects, []() {}},
	  {Calibration, []() {}}}},
};

const std::map<id_t, std::map<Menu, knobFunction_t>> knobsFunctions = {
	{1,
	 {{Basic, []() {}},
	  {ToneCurve, []() {}},
	  {HSL_Color, []() {}},
	  {ColorGrading, []() {}},
	  {Detail, []() {}},
	  {LensCorrection, []() {}},
	  {Transform, []() {}},
	  {Effects, []() {}},
	  {Calibration, []() {}}}},
	{2,
	 {{Basic, []() {}},
	  {ToneCurve, []() {}},
	  {HSL_Color, []() {}},
	  {ColorGrading, []() {}},
	  {Detail, []() {}},
	  {LensCorrection, []() {}},
	  {Transform, []() {}},
	  {Effects, []() {}},
	  {Calibration, []() {}}}},
	{3,
	 {{Basic, []() {}},
	  {ToneCurve, []() {}},
	  {HSL_Color, []() {}},
	  {ColorGrading, []() {}},
	  {Detail, []() {}},
	  {LensCorrection, []() {}},
	  {Transform, []() {}},
	  {Effects, []() {}},
	  {Calibration, []() {}}}},
	{4,
	 {{Basic, []() {}},
	  {ToneCurve, []() {}},
	  {HSL_Color, []() {}},
	  {ColorGrading, []() {}},
	  {Detail, []() {}},
	  {LensCorrection, []() {}},
	  {Transform, []() {}},
	  {Effects, []() {}},
	  {Calibration, []() {}}}},
	{5,
	 {{Basic, []() {}},
	  {ToneCurve, []() {}},
	  {HSL_Color, []() {}},
	  {ColorGrading, []() {}},
	  {Detail, []() {}},
	  {LensCorrection, []() {}},
	  {Transform, []() {}},
	  {Effects, []() {}},
	  {Calibration, []() {}}}},
	{6,
	 {{Basic, []() {}},
	  {ToneCurve, []() {}},
	  {HSL_Color, []() {}},
	  {ColorGrading, []() {}},
	  {Detail, []() {}},
	  {LensCorrection, []() {}},
	  {Transform, []() {}},
	  {Effects, []() {}},
	  {Calibration, []() {}}}},
	{7,
	 {{Basic, []() {}},
	  {ToneCurve, []() {}},
	  {HSL_Color, []() {}},
	  {ColorGrading, []() {}},
	  {Detail, []() {}},
	  {LensCorrection, []() {}},
	  {Transform, []() {}},
	  {Effects, []() {}},
	  {Calibration, []() {}}}},
	{8,
	 {{Basic, []() {}},
	  {ToneCurve, []() {}},
	  {HSL_Color, []() {}},
	  {ColorGrading, []() {}},
	  {Detail, []() {}},
	  {LensCorrection, []() {}},
	  {Transform, []() {}},
	  {Effects, []() {}},
	  {Calibration, []() {}}}},
};

class Lightroom
{
private:
	static current_t _current;

	const Devices _devices;

	static void _test(params_t params);
	static void _logic(params_t params);

	static void _buttonsLogic(id_t id, ReadState state);
	static void _knobsLogic(id_t id, ReadState state);

public:
	Lightroom();
	~Lightroom();
};

#endif // LIGHTROOM_H