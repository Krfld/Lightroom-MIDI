#include "lightroom.h"

Lightroom::Lightroom() : _devices(Devices(&_logic))
{
	// TODO add devices
}

Lightroom::~Lightroom() { log_i("~Lightroom"); }

current_t Lightroom::_current = (current_t){Basic, 1};

std::map<Menu, std::map<id_t, std::map<id_t, value_t>>> Lightroom::_knobsValues = {
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

// ----------------------------------------------------------------------------------------------------

void Lightroom::_test(params_t params)
{
	switch (params.device)
	{
	case BUTTON:
		switch (params.state)
		{
		case Idle:
			log_i("Button %d Idle", params.id);
			break;
		case Pressed:
			log_i("Button %d Pressed", params.id);
			break;
		case Released:
			log_i("Button %d Released", params.id);
			break;
		default:
			break;
		}
		break;

	case KNOB:
		switch (params.state)
		{
		case Idle:
			log_i("Knob %d Idle", params.id);
			break;
		case Pressed:
			log_i("Knob %d Pressed", params.id);
			break;
		case Released:
			log_i("Knob %d Released", params.id);
			break;
		case Clockwise:
			log_i("Knob %d Clockwise", params.id);
			break;
		case CounterClockwise:
			log_i("Knob %d CounterClockwise", params.id);
			break;
		}
		break;
	}
}

void Lightroom::_logic(params_t params)
{
	_test(params);

	if (params.device == BUTTON)
		_buttonsLogic(params.id, params.state);
	else if (params.device == KNOB)
		_knobsLogic(params.id, params.state);
}

void Lightroom::_buttonsLogic(id_t id, ReadState state)
{
	switch (id)
	{
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;
	case 6:
		break;
	case 7:
		break;
	case 8:
		break;
	case 9:
		//* Changing menu updates leds and LCD
		break;
	case 10:
		//* Changing menu updates leds and LCD
		break;
	case 11:
		//* Changing menu updates leds and LCD
		if (_current.subMenu > SubMenus.at(_current.menu))
			_current.subMenu--;
		else
			_current.subMenu = SubMenus.at(_current.menu);
		break;
	case 12:
		//* Changing menu updates leds and LCD
		if (_current.subMenu < SubMenus.at(_current.menu))
			_current.subMenu++;
		else
			_current.subMenu = 1;
		break;
	default:
		break;
	}
}

void Lightroom::_knobsLogic(id_t id, ReadState state)
{
	switch (id)
	{
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;
	case 6:
		break;
	case 7:
		break;
	case 8:
		break;
	default:
		break;
	}
}