#pragma once
#include <Arduino.h>

struct AppState {
    byte button1FunctionIndex = 0;
    bool button1Momentary = false;
    byte button1Time = 0;

    byte brightness    = 128;
    bool acceptUpdates = false;
    bool enableWifi = false;
};

extern AppState appState;
