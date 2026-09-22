#include "settings_store.h"
#include "app/button_functions.h"
#include "app_state.h"
#include "../hal/storage.h"
#include "config.h"
#include "hal/leds.h"
#include <Arduino.h>

static const char* SETTINGS_PATH = "/settings.dat";

static const byte SETTINGS_VERSION = 2;

struct SettingsFile {
    byte version;
    Settings data;
};

void settingsStore_load() {
    SettingsFile file;

    if (!storage_readFile(SETTINGS_PATH, &file, sizeof(file))) {
        Serial.println(F("[Settings] No saved settings, using defaults"));
        return;
    }

    if (file.version != SETTINGS_VERSION) {
        Serial.println(F("[Settings] Saved version mismatch, using defaults"));
        return;
    }

    appState.settings = file.data;

    for (byte i = 0; i < NUM_BUTTONS; i++) {
        leds_set(i, dimColor(BUTTON_FUNCTIONS[appState.settings.buttonsFunctions[i]].color, 10));
    }

    Serial.println(F("[Settings] Loaded from flash"));
}

void settingsStore_save() {
    SettingsFile file;
    file.version = SETTINGS_VERSION;
    file.data    = appState.settings;

    if (storage_writeFile(SETTINGS_PATH, &file, sizeof(file))) {
        Serial.println(F("[Settings] Saved"));
    } else {
        Serial.println(F("[Settings] Save FAILED"));
    }
}