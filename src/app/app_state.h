#pragma once
#include "config.h"

enum ButtonFunctionOptions : byte {
    BTN_FUNC_NONE           = 0,
    BTN_FUNC_PROGRAM_CHANGE = 1,
    BTN_FUNC_CONTROL_CHANGE = 2
};

struct ButtonConfig {
    byte function       = BTN_FUNC_NONE;
    bool momentary      = false;
    byte time           = 0;
};

struct AppState {
    ButtonConfig buttons[NUM_BUTTONS];

    byte brightness    = 50;
    bool acceptUpdates = false;
    bool enableWifi    = false;

    char rigName[24]      = "Not connected";
    bool midiConnected    = false;
};

extern AppState appState;
