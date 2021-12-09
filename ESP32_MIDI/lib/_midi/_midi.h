#ifndef MIDI_H
#define MIDI_H

enum Limits
{
	MIDI_CHANNEL_MIN = 0,
	MIDI_CHANNEL_MAX = 15,

	// Notes
	MIDI_NOTE_PITCH_MIN = 0,
	MIDI_NOTE_PITCH_MAX = 127,
	MIDI_NOTE_VELOCITY_MIN = 0,
	MIDI_NOTE_VELOCITY_MAX = 127,

	// Controls
	MIDI_CONTROL_NUMBER_MIN = 0,
	MIDI_CONTROL_NUMBER_MAX = 127,
	MIDI_CONTROL_VALUE_MIN = 0,
	MIDI_CONTROL_VALUE_MAX = 127,
};

#endif // MIDI_H