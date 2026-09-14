#include "buttons_controller.h"
#include "app_state.h"
#include <Arduino.h>

void buttonsController_onButton1FunctionIndexChanged() {
    Serial.print(F("Button1 func set to: "));
    Serial.println(appState.button1FunctionIndex);
}

void buttonsController_onButton1MomentaryChanged() {
    Serial.print(F("Button1 momentary set to: "));
    Serial.println(appState.button1Momentary);
}

void buttonsController_onButton1TimeChanged() {
    Serial.print(F("Button1 time set to: "));
    Serial.println(appState.button1Time);
}