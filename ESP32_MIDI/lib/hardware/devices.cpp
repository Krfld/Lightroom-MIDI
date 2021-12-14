#include "hardware.h"

bool Devices::addExpander(id id = 1, uint8_t address = 0x20)
{
	Expander expander = Expander();

	if (!expander->begin_I2C(address))
		return false;

	return _expanders.insert({id, expander}).second;
}

void Devices::removeExpander(id id) { _expanders.erase(id); }

// ----------------------------------------------------------------------------------------------------
