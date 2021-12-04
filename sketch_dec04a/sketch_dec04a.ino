#include <Control_Surface.h>
 
USBMIDI_Interface midi;
 
void setup() {
    midi.begin();
}

const MIDIAddress note = MIDI_Notes::C(4); // C(4) is middle C
const uint8_t velocity = 127;              // 127 is maximum velocity

void loop() {
    midi.sendNoteOn(note, velocity);
    delay(5000);
    midi.sendNoteOff(note, velocity);
    delay(5000);
    
    midi.update();
}
