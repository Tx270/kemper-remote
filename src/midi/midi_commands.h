#pragma once
#include <Arduino.h>

enum MidiCommandType : byte {
    MIDI_CMD_NONE              = 0,
    MIDI_CMD_PROGRAM_CHANGE    = 1,
    MIDI_CMD_CONTROL_CHANGE    = 2,
    MIDI_CMD_SYSEX_RIG_NAME    = 3,  // sends a request, expects a reply
    // MIDI_CMD_SYSEX_TEMPO    = 4  // future example
};

struct MidiCommand {
    MidiCommandType type;
    byte channel;
    byte data1;   // program number, CC number, etc.
    byte data2;   // CC value, velocity, etc. (0 if unused)
};

struct MidiResponse {
    char text[255];
    byte value;
    bool valid;       // false if the reply was garbled
};

static const byte KEMPER_RIG_NAME_REQUEST[] = {
    0x00, 0x20, 0x33,  // Kemper manufacturer ID
    0x02, 0x7F,            // device ID, broadcast
    0x43,                      // function: get string
    0x00,                      // instance (always 0)
    0x00, 0x01             // parameter: rig name
};
static const byte KEMPER_RIG_NAME_REQUEST_LEN = sizeof(KEMPER_RIG_NAME_REQUEST);