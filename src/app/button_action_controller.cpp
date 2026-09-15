#include "button_action_controller.h"
#include "../hal/buttons.h"
#include "Arduino.h"
#include "hal/leds.h"

byte buttonIndex;
bool buttonState;

void buttons_update() {
    if (buttons_poll(buttonIndex, buttonState)) {
        if (buttonState) {
            leds_set(buttonIndex, 255, 0, 255);
        } else {
            leds_set(buttonIndex, 0, 0, 0);
        }
    }    
}