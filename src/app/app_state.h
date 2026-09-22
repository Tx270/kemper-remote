#pragma once
#include "config.h"

struct Settings {
    byte buttonsFunctions[NUM_BUTTONS] = {0};
    byte brightness    = 50;
    bool acceptUpdates = false;
    bool enableWifi    = false;
};

struct AppState {
    Settings settings;   // saved to /settings.dat

    char rigName[255]  = "Not connected";
    bool midiConnected = false;
};

extern AppState appState;
