enum Menus
{
	Basic,
	ToneCurve,
	HSL_Color,
	ColorGrading,
	Detail,
	LensCorrections,
	Transform,
	Effects,
	Calibration
};

class Menu
{
private:
	Menu();
	static int menu;

public:
	static int getMenu();
	static void nextMenu();
	static void previousMenu();
};