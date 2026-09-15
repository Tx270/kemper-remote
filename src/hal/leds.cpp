#include "leds.h"
#include "app/app_state.h"
#include "pins.h"
#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel leds(
    NUM_LEDS,
    LEDS_PIN,
    NEO_GRB + NEO_KHZ800
);

void leds_init() {
    leds.begin();
    leds.setBrightness(appState.brightness);
    leds.clear();
    leds.show();
}

void leds_set(byte index, byte red, byte green, byte blue)
{
    if (index >= NUM_LEDS) {
        return;
    }

    leds.setPixelColor(index, leds.Color(red, green, blue));
    leds.show();
}

void leds_setAll(byte red, byte green, byte blue)
{
    for (byte i = 0; i < NUM_LEDS; i++) {
        leds.setPixelColor(i, leds.Color(red, green, blue));
    }

    leds.show();
}

void leds_setBrightness(byte brightness){
    leds.setBrightness(appState.brightness);
    leds.show();
}