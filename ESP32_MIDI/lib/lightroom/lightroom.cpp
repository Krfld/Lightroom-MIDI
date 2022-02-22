#include "lightroom.h"

Lightroom::Lightroom() : _devices(Devices(&_logic))
{
	// TODO add devices
}

Lightroom::~Lightroom() { log_i("~Lightroom"); }

current_t Lightroom::_current = (current_t){Basic, 1};

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
		//* Changing menu updates leds
		break;
	case 10:
		//* Changing menu updates leds
		break;
	case 11:
		if (_current.subMenu > SubMenus.at(_current.menu))
			_current.subMenu--;
		else
			_current.subMenu = SubMenus.at(_current.menu);
		break;
	case 12:
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