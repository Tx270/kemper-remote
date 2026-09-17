#include "button_action_controller.h"
#include "../hal/buttons.h"
#include <Arduino.h>
#include "app/app_state.h"
#include "hal/leds.h"
#include "midi/midi_commands.h"
#include "midi/midi_queue.h"

byte buttonIndex;
bool buttonState;

void onButtonPressed(byte index) {
    ButtonConfig& cfg = appState.buttons[index];

    MidiCommand cmd;
    cmd.channel = 0;

    switch (cfg.function) {
        case 0:  // None
            return;

        case 1:  // Program Change
            cmd.type  = MIDI_CMD_PROGRAM_CHANGE;
            cmd.data1 = 5;  // example: 1st slot of 2nd bank
            cmd.data2 = 0;  // unused
            break;

        case 2:  // Control Change
            cmd.type  = MIDI_CMD_CONTROL_CHANGE;
            cmd.data1 = 31;   // example: tuner
            cmd.data2 = 1;    // 1 = on
            break;

        default:
            return;
    }

    midiQueue_push(cmd);
}

void buttons_update() {
    if (buttons_poll(buttonIndex, buttonState)) {
        if (buttonState) {
            leds_set(buttonIndex, 0, 255, 0);
            onButtonPressed(buttonIndex);
        } else {
            leds_set(buttonIndex, 0, 0, 0);
        }
    }
}