#pragma once
#include "midi_commands.h"

constexpr byte MIDI_QUEUE_SIZE = 8;

void midiQueue_init();
bool midiQueue_push(const MidiCommand& cmd);   // returns false if full
bool midiQueue_pop(MidiCommand& out);          // returns false if empty
bool midiQueue_isEmpty();