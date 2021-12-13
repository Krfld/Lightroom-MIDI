#include "button.h"

Button::Button(int id) : id(id)
{
	// TODO Define pins & config inputs and outputs
}

bool Button::isActive()
{
	// TODO
	return true;
}

void Button::pressed()
{
	if (!isActive())
		return;

	// TODO Send MIDI
	/*
	int menu = (int)Menus::currentMenu();
	MIDI.sendNoteOn(menu, id, 127);
	*/
}