#pragma once
#include "Arduino.h"

void leds_init();

void leds_set(byte index, byte red, byte green, byte blue);
void leds_setAll(byte red, byte green, byte blue);
void leds_setBrightness(byte brightness);