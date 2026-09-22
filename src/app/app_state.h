#pragma once
#include "config.h"

struct ButtonConfig {
    byte function       = 0;
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
