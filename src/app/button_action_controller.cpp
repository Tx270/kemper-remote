#include "button_action_controller.h"
#include "../hal/buttons.h"
#include "Arduino.h"

byte buttonIndex;
bool buttonState;


void buttons_update() {
    if (buttons_poll(buttonIndex, buttonState)) {
        Serial.print(buttonIndex);
        Serial.print(" is ");
        Serial.println(buttonState);
    }    
}