#include "buttons.h"
#include "pins.h"
#include <Bounce2.h>

Bounce buttons[NUM_BUTTONS];

void buttons_init() {
    for (byte i = 0; i < NUM_BUTTONS; i++) {
        buttons[i].attach(BUTTON_PINS[i], INPUT_PULLUP);
        buttons[i].interval(30);
    }
}

bool buttons_poll(byte &buttonIndex, bool &buttonState) {
    for (byte i = 0; i < NUM_BUTTONS; i++) {
        buttons[i].update();
        bool pressed = buttons[i].fell();
        bool released = buttons[i].rose();

        if (pressed || released) {
            buttonIndex = i;
            buttonState = pressed;
            return true;
        }
    }
    return false;
}