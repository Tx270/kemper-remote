#include "settings_controller.h"
#include "app/settings_store.h"
#include "app_state.h"
#include "hal/leds.h"
#include <Arduino.h>
#include <WiFi.h>

void settingsController_onBrightnessChanged() {
    leds_setBrightness(appState.settings.brightness);

    settingsStore_save();
}

void settingsController_onEnableWifiChanged() {
    if (appState.settings.enableWifi) {
        WiFi.mode(WIFI_AP);
        // WiFi.begin("kemper-remote", "esp32");
    } else {
        WiFi.disconnect(true);
        WiFi.mode(WIFI_OFF);
    }

    settingsStore_save();
}

void settingsController_onAcceptUpdatesChanged() {
    Serial.print(F("Updates set to: "));
    Serial.println(appState.settings.acceptUpdates);

    settingsStore_save();
}