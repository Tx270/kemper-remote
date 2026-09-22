#include "button_action_controller.h"
#include "../hal/buttons.h"
#include <Arduino.h>
#include "app/app_state.h"
#include "app/button_functions.h"
#include "hal/leds.h"
#include "midi/midi_queue.h"

byte buttonIndex;
bool buttonState;

constexpr unsigned long SWITCH_LONG_PRESS_MS = 600;

static bool          isOn[NUM_BUTTONS];
static unsigned long pressStartTime[NUM_BUTTONS];

void buttons_update() {
    if (!buttons_poll(buttonIndex, buttonState)) return;

    ButtonFunction function = BUTTON_FUNCTIONS[appState.settings.buttonsFunctions[buttonIndex]];

    if (buttonState) {
        // --- Press ---
        pressStartTime[buttonIndex] = millis();

        switch (function.mode) {
            case MODE_MOMENTARY:
                leds_set(buttonIndex, function.color);
                midiQueue_push(function.action);
                break;

            case MODE_SINGLE:
                leds_set(buttonIndex, function.color);
                midiQueue_push(function.action);
                break;

            case MODE_SWITCH:
            case MODE_SWITCH_MOMENTARY:
                isOn[buttonIndex] = !isOn[buttonIndex];
                if (isOn[buttonIndex]) {
                    leds_set(buttonIndex, function.color);
                    midiQueue_push(function.action);
                } else {
                    leds_set(buttonIndex, dimColor(function.color, 10));
                    midiQueue_push(function.revert);
                }
                break;

            case MODE_NONE:
            default:
                break;
        }

    } else {
        // --- Release ---
        unsigned long heldFor = millis() - pressStartTime[buttonIndex];

        switch (function.mode) {
            case MODE_MOMENTARY:
                leds_set(buttonIndex, dimColor(function.color, 10));
                midiQueue_push(function.revert);
                break;

            case MODE_SINGLE:
                leds_set(buttonIndex, dimColor(function.color, 10));
                break;

            case MODE_SWITCH:
                break;

            case MODE_SWITCH_MOMENTARY:
                if (isOn[buttonIndex] && heldFor >= SWITCH_LONG_PRESS_MS) {
                    isOn[buttonIndex] = false;
                    leds_set(buttonIndex, dimColor(function.color, 10));
                    midiQueue_push(function.revert);
                }
                break;

            case MODE_NONE:

            default:
                break;
        }
    }
}