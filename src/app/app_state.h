#pragma once
#include <Arduino.h>

constexpr byte NUM_BUTTONS = 1;

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
