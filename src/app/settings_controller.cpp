#include "settings_controller.h"
#include "app_state.h"
#include <Arduino.h>

void settingsController_onBrightnessChanged() {
    Serial.print(F("Brightness set to: "));
    Serial.println(appState.brightness);
}

void settingsController_onEnableWifiChanged() {
    Serial.print(F("Wifi set to: "));
    Serial.println(appState.enableWifi);
}

void settingsController_onAcceptUpdatesChanged() {
    Serial.print(F("Updates set to: "));
    Serial.println(appState.acceptUpdates);
}