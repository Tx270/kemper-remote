#pragma once
#include <Arduino.h>


constexpr byte buttonPins[] = {
    0
};

constexpr byte ledPins[] = {
    48
};

constexpr byte NUM_BUTTONS = sizeof(buttonPins) / sizeof(buttonPins[0]);
constexpr byte NUM_LEDS = sizeof(ledPins) / sizeof(ledPins[0]);

static_assert(NUM_BUTTONS == NUM_LEDS, "Number of LEDs must match number of buttons");

constexpr byte displaySdaPin = 11;
constexpr byte displaySclPin = 10;