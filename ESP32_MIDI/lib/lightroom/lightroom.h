#ifndef LIGHTROOM_H
#define LIGHTROOM_H

//#include midi

#include <map>
#include "devices.h"

typedef uint8_t value_t;
typedef uint8_t subMenu_t;

#define NO_VALUE (value_t)(-1)
#define MIN_VALUE 0
#define MAX_VALUE 127
#define DEFAULT_VALUE 63

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
	None,
	Basic,
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
	subMenu_t subMenu;
} current_t;

class Lightroom
{
private:
	static current_t _current;

	const Devices _devices;

	static void _test(params_t params);
	static void _logic(params_t params);

	static void _buttonsLogic(id_t id, ReadState state);
	static void _knobsLogic(id_t id, ReadState state);

	static std::map<Menu, std::map<subMenu_t, std::map<id_t, value_t>>> _buttonsValues;
	static std::map<Menu, std::map<subMenu_t, std::map<id_t, value_t>>> _knobsValues;

public:
	Lightroom();
	~Lightroom();
};

#endif // LIGHTROOM_H