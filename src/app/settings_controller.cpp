#include "settings_controller.h"
#include "app_state.h"
#include "hal/leds.h"
#include <Arduino.h>
#include <WiFi.h>

void settingsController_onBrightnessChanged() {
    leds_setBrightness(appState.settings.brightness);
    Serial.print(F("Brightness set to: "));
    Serial.println(appState.settings.brightness);
}

void settingsController_onEnableWifiChanged() {
    if (appState.settings.enableWifi) {
        WiFi.mode(WIFI_AP_STA);
    } else {
        WiFi.disconnect(true);
        WiFi.mode(WIFI_OFF);
    }
    Serial.print(F("Wifi set to: "));
    Serial.println(appState.settings.enableWifi);
}

void settingsController_onAcceptUpdatesChanged() {
    Serial.print(F("Updates set to: "));
    Serial.println(appState.settings.acceptUpdates);
}