#pragma once
#include <Arduino.h>

constexpr bool HAS_DISPLAY = true;
constexpr bool HAS_LEDS = true;

constexpr byte NUM_BUTTONS = 1;
constexpr byte NUM_LEDS = NUM_BUTTONS; // separate const for future expansion