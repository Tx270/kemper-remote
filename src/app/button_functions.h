#pragma once
#include "Arduino.h"
#include "../midi/midi_commands.h"
#include "hal/leds.h"

enum ButtonMode : byte {
    MODE_NONE,             // does nothing
    MODE_MOMENTARY,        // action on press, revert on release
    MODE_SINGLE,           // action on press only, nothing on release
    MODE_SWITCH,           // toggles on press, stays latched no matter how long held
    MODE_SWITCH_MOMENTARY  // toggles on press; a long hold makes it act momentary and switch back off on release
};

struct ButtonFunction {
    const char* name;
    ButtonMode  mode;
    Color       color;
    MidiCommand action;
    MidiCommand revert;   // ignored for MODE_NONE and MODE_SINGLE
};

const ButtonFunction BUTTON_FUNCTIONS[] = {
    { "None",          MODE_NONE,             { 0,   0,   0   }, { MIDI_CMD_NONE },                       { MIDI_CMD_NONE } },
    { "Next Bank",      MODE_SINGLE,           { 0,   0, 255   }, { MIDI_CMD_CONTROL_CHANGE, 0, 48, 0 },   { MIDI_CMD_NONE } },
    { "Tuner",         MODE_SWITCH_MOMENTARY, { 255,   0, 0   }, { MIDI_CMD_CONTROL_CHANGE, 0, 31, 1 },   { MIDI_CMD_CONTROL_CHANGE, 0, 31, 0 } },
};

const byte BUTTON_FUNCTION_COUNT = sizeof(BUTTON_FUNCTIONS) / sizeof(BUTTON_FUNCTIONS[0]);