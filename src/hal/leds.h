#pragma once
#include <Arduino.h>

void leds_init();

struct Color {
    byte red;
    byte green;
    byte blue;
};

Color dimColor(Color color, byte percent);

void leds_set(byte index, Color color);
void leds_setAll(Color color);
void leds_setBrightness(byte brightness);