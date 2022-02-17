#ifndef LIGHTROOM_H
#define LIGHTROOM_H

//#include midi

#include "devices.h"

#define BASIC "Basic"
#define TONE_CURVE "Tone Curve"
#define HSL_COLOR "HSL/Color"
#define COLOR_GRADING "Color Grading"
#define DETAIL "Detail"
#define LENS_CORRECTION "Lens Correction"
#define TRANSFORM "Transform"
#define EFFECTS "Effects"
#define CALIBRATION "Calibration"

class Lightroom
{
private:
	enum menus_e
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
	};

	enum menuSettings_e
	{
		FIRST_MENU = Basic,
		LAST_MENU = Calibration,
	};

	menus_e _menu = Basic;

	Devices _devices;

public:
	Lightroom();
};

#endif // LIGHTROOM_H