#pragma once
#include "../config.h"
#include <Arduino.h>

constexpr byte DISPLAY_SDA_PIN = 11; 
constexpr byte DISPLAY_SCL_PIN = 10;
constexpr byte LEDS_PIN = 48;
constexpr byte BUTTON_PINS[] = { 0 };

static_assert(sizeof(BUTTON_PINS) / sizeof(BUTTON_PINS[0]) == NUM_BUTTONS, "Size of BUTTON_PINS doesn't match NUM_BUTTONS");