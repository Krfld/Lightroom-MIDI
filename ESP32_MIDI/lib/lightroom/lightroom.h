#ifndef LIGHTROOM_H
#define LIGHTROOM_H

#include "devices.h"

//#include midi

#define BASIC "Basic"					  // 1
#define TONE_CURVE "Tone Curve"			  // 2
#define HSL_COLOR "HSL/Color"			  // 3
#define COLOR_GRADING "Color Grading"	  // 4
#define DETAIL "Detail"					  // 5
#define LENS_CORRECTION "Lens Correction" // 6
#define TRANSFORM "Transform"			  // 7
#define EFFECTS "Effects"				  // 8
#define CALIBRATION "Calibration"		  // 9

class Lightroom
{
private:
	uint8_t _menu;

public:
};

#endif // LIGHTROOM_H