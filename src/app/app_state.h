#pragma once
#include "../hal/pins.h"

struct ButtonConfig {
    byte functionIndex  = 0;
    bool momentary      = false;
    byte time           = 0;
};


struct AppState {
    ButtonConfig buttons[NUM_BUTTONS];

    byte brightness    = 128;
    bool acceptUpdates = false;
    bool enableWifi    = false;
};

extern AppState appState;
