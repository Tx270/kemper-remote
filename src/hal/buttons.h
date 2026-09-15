#pragma once
#include <Arduino.h>

void buttons_init();
bool buttons_poll(byte &buttonIndex, bool &buttonState);
