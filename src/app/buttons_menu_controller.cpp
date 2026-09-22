#include "buttons_menu_controller.h"
#include "app/button_functions.h"
#include "app_state.h"
#include "hal/leds.h"
#include <Arduino.h>

void buttonsMenuController_onFunctionChanged(GEMCallbackData callbackData) {
    byte idx = callbackData.valByte;
    leds_set(idx, dimColor(BUTTON_FUNCTIONS[appState.buttons[idx].function].color, 10));
}

void buttonsMenuController_onMomentaryChanged(GEMCallbackData callbackData) {
    byte idx = callbackData.valByte;

    Serial.print(F("Button "));
    Serial.print(idx + 1);
    Serial.print(F(" momentary set to: "));
    Serial.println(appState.buttons[idx].momentary);
}

void buttonsMenuController_onTimeChanged(GEMCallbackData callbackData) {
    byte idx = callbackData.valByte;

    Serial.print(F("Button "));
    Serial.print(idx + 1);
    Serial.print(F(" time set to: "));
    Serial.println(appState.buttons[idx].time);
}
