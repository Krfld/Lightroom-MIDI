#include <map>

typedef uint8_t id_t;
typedef uint8_t value_t;

#define NO_VALUE (value_t)(-1)
#define MIN_VALUE 0
#define MAX_VALUE 127
#define DEFAULT_VALUE 63

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

// typedef void (*buttonFunction_t)();
// typedef void (*knobFunction_t)();

const std::map<Menu, std::map<id_t, void (*)()>> buttonsFunctions = {
	{None,
	 {{0, []() {}}}},
	{Basic,
	 {{1, []() {}},
	  {2, []() {}},
	  {3, []() {}},
	  {4, []() {}},
	  {5, []() {}},
	  {6, []() {}},
	  {7, []() {}},
	  {8, []() {}}}},
	{ToneCurve,
	 {{1, []() {}},
	  {2, []() {}},
	  {3, []() {}},
	  {4, []() {}},
	  {5, []() {}},
	  {6, []() {}},
	  {7, []() {}},
	  {8, []() {}}}},
	{HSL_Color,
	 {{1, []() {}},
	  {2, []() {}},
	  {3, []() {}},
	  {4, []() {}},
	  {5, []() {}},
	  {6, []() {}},
	  {7, []() {}},
	  {8, []() {}}}},
	{ColorGrading,
	 {{1, []() {}},
	  {2, []() {}},
	  {3, []() {}},
	  {4, []() {}},
	  {5, []() {}},
	  {6, []() {}},
	  {7, []() {}},
	  {8, []() {}}}},
	{Detail,
	 {{1, []() {}},
	  {2, []() {}},
	  {3, []() {}},
	  {4, []() {}},
	  {5, []() {}},
	  {6, []() {}},
	  {7, []() {}},
	  {8, []() {}}}},
	{LensCorrection,
	 {{1, []() {}},
	  {2, []() {}},
	  {3, []() {}},
	  {4, []() {}},
	  {5, []() {}},
	  {6, []() {}},
	  {7, []() {}},
	  {8, []() {}}}},
	{Transform,
	 {{1, []() {}},
	  {2, []() {}},
	  {3, []() {}},
	  {4, []() {}},
	  {5, []() {}},
	  {6, []() {}},
	  {7, []() {}},
	  {8, []() {}}}},
	{Effects,
	 {{1, []() {}},
	  {2, []() {}},
	  {3, []() {}},
	  {4, []() {}},
	  {5, []() {}},
	  {6, []() {}},
	  {7, []() {}},
	  {8, []() {}}}},
	{Calibration,
	 {{1, []() {}},
	  {2, []() {}},
	  {3, []() {}},
	  {4, []() {}},
	  {5, []() {}},
	  {6, []() {}},
	  {7, []() {}},
	  {8, []() {}}}},
};

const std::map<Menu, std::map<id_t, void (*)()>> knobsFunctions = {
	{None,
	 {{0, []() {}}}},
	{Basic,
	 {{1, []() {}},
	  {2, []() {}},
	  {3, []() {}},
	  {4, []() {}},
	  {5, []() {}},
	  {6, []() {}},
	  {7, []() {}},
	  {8, []() {}}}},
	{ToneCurve,
	 {{1, []() {}},
	  {2, []() {}},
	  {3, []() {}},
	  {4, []() {}},
	  {5, []() {}},
	  {6, []() {}},
	  {7, []() {}},
	  {8, []() {}}}},
	{HSL_Color,
	 {{1, []() {}},
	  {2, []() {}},
	  {3, []() {}},
	  {4, []() {}},
	  {5, []() {}},
	  {6, []() {}},
	  {7, []() {}},
	  {8, []() {}}}},
	{ColorGrading,
	 {{1, []() {}},
	  {2, []() {}},
	  {3, []() {}},
	  {4, []() {}},
	  {5, []() {}},
	  {6, []() {}},
	  {7, []() {}},
	  {8, []() {}}}},
	{Detail,
	 {{1, []() {}},
	  {2, []() {}},
	  {3, []() {}},
	  {4, []() {}},
	  {5, []() {}},
	  {6, []() {}},
	  {7, []() {}},
	  {8, []() {}}}},
	{LensCorrection,
	 {{1, []() {}},
	  {2, []() {}},
	  {3, []() {}},
	  {4, []() {}},
	  {5, []() {}},
	  {6, []() {}},
	  {7, []() {}},
	  {8, []() {}}}},
	{Transform,
	 {{1, []() {}},
	  {2, []() {}},
	  {3, []() {}},
	  {4, []() {}},
	  {5, []() {}},
	  {6, []() {}},
	  {7, []() {}},
	  {8, []() {}}}},
	{Effects,
	 {{1, []() {}},
	  {2, []() {}},
	  {3, []() {}},
	  {4, []() {}},
	  {5, []() {}},
	  {6, []() {}},
	  {7, []() {}},
	  {8, []() {}}}},
	{Calibration,
	 {{1, []() {}},
	  {2, []() {}},
	  {3, []() {}},
	  {4, []() {}},
	  {5, []() {}},
	  {6, []() {}},
	  {7, []() {}},
	  {8, []() {}}}},
};

const std::map<id_t, std::map<Menu, void (*)()>> buttonsFunctions2 = {
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

const std::map<id_t, std::map<Menu, void (*)()>> knobsFunctions2 = {
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

std::map<Menu, std::map<id_t, std::map<id_t, value_t>>> _knobsValues = {
	{None,
	 {{1,
	   {{0, DEFAULT_VALUE}}}}},

	{Basic,
	 {{1,
	   {{1, DEFAULT_VALUE},
		{2, DEFAULT_VALUE},
		{3, DEFAULT_VALUE},
		{4, DEFAULT_VALUE},
		{5, DEFAULT_VALUE},
		{6, DEFAULT_VALUE},
		{7, DEFAULT_VALUE},
		{8, DEFAULT_VALUE}}},
	  {2,
	   {{1, DEFAULT_VALUE},
		{2, DEFAULT_VALUE},
		{3, DEFAULT_VALUE},
		{4, DEFAULT_VALUE},
		{5, DEFAULT_VALUE},
		{6, NO_VALUE},
		{7, NO_VALUE},
		{8, NO_VALUE}}}}},

	{ToneCurve,
	 {{1,
	   {{1, DEFAULT_VALUE},
		{2, DEFAULT_VALUE},
		{3, DEFAULT_VALUE},
		{4, DEFAULT_VALUE},
		{5, DEFAULT_VALUE},
		{6, DEFAULT_VALUE},
		{7, DEFAULT_VALUE},
		{8, NO_VALUE}}}}},

	{HSL_Color,
	 {{1,
	   {{1, DEFAULT_VALUE},
		{2, DEFAULT_VALUE},
		{3, DEFAULT_VALUE},
		{4, DEFAULT_VALUE},
		{5, DEFAULT_VALUE},
		{6, DEFAULT_VALUE},
		{7, DEFAULT_VALUE},
		{8, DEFAULT_VALUE}}}}},

	{ColorGrading,
	 {{1,
	   {{1, DEFAULT_VALUE},
		{2, DEFAULT_VALUE},
		{3, DEFAULT_VALUE},
		{4, DEFAULT_VALUE},
		{5, DEFAULT_VALUE},
		{6, NO_VALUE},
		{7, NO_VALUE},
		{8, NO_VALUE}}}}},

	{Detail,
	 {{1,
	   {{1, DEFAULT_VALUE},
		{2, DEFAULT_VALUE},
		{3, DEFAULT_VALUE},
		{4, DEFAULT_VALUE},
		{5, NO_VALUE},
		{6, NO_VALUE},
		{7, NO_VALUE},
		{8, NO_VALUE}}},
	  {2,
	   {{1, DEFAULT_VALUE},
		{2, DEFAULT_VALUE},
		{3, DEFAULT_VALUE},
		{4, DEFAULT_VALUE},
		{5, DEFAULT_VALUE},
		{6, DEFAULT_VALUE},
		{7, NO_VALUE},
		{8, NO_VALUE}}}}},

	{LensCorrection,
	 {{1,
	   {{1, DEFAULT_VALUE},
		{2, DEFAULT_VALUE},
		{3, DEFAULT_VALUE},
		{4, DEFAULT_VALUE},
		{5, DEFAULT_VALUE},
		{6, DEFAULT_VALUE},
		{7, DEFAULT_VALUE},
		{8, NO_VALUE}}},
	  {2,
	   {{1, DEFAULT_VALUE},
		{2, DEFAULT_VALUE},
		{3, NO_VALUE},
		{4, NO_VALUE},
		{5, NO_VALUE},
		{6, NO_VALUE},
		{7, NO_VALUE},
		{8, NO_VALUE}}}}},

	{Transform,
	 {{1,
	   {{1, DEFAULT_VALUE},
		{2, DEFAULT_VALUE},
		{3, DEFAULT_VALUE},
		{4, DEFAULT_VALUE},
		{5, DEFAULT_VALUE},
		{6, DEFAULT_VALUE},
		{7, DEFAULT_VALUE},
		{8, NO_VALUE}}}}},

	{Effects,
	 {{1,
	   {{1, DEFAULT_VALUE},
		{2, DEFAULT_VALUE},
		{3, DEFAULT_VALUE},
		{4, DEFAULT_VALUE},
		{5, DEFAULT_VALUE},
		{6, DEFAULT_VALUE},
		{7, DEFAULT_VALUE},
		{8, DEFAULT_VALUE}}}}},

	{Calibration,
	 {{1,
	   {{1, DEFAULT_VALUE},
		{2, DEFAULT_VALUE},
		{3, DEFAULT_VALUE},
		{4, DEFAULT_VALUE},
		{5, DEFAULT_VALUE},
		{6, DEFAULT_VALUE},
		{7, DEFAULT_VALUE},
		{8, NO_VALUE}}}}},
};