#pragma once
#include <Arduino.h>

constexpr byte DISPLAY_SDA_PIN = 11;
constexpr byte DISPLAY_SCL_PIN = 10;
constexpr byte LEDS_PIN = 48;
constexpr byte BUTTON_PINS[] = { 0 };

constexpr byte NUM_BUTTONS = sizeof(BUTTON_PINS) / sizeof(BUTTON_PINS[0]);
constexpr byte NUM_LEDS = NUM_BUTTONS; // separate const for future expansion