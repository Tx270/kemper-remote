#pragma once
#include "config.h"

struct AppState {
    byte buttonsFunctions[NUM_BUTTONS];

    byte brightness    = 50;
    bool acceptUpdates = false;
    bool enableWifi    = false;

    char rigName[24]      = "Not connected";
    bool midiConnected    = false;
};

extern AppState appState;
