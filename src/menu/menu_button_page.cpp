// menu_button_page.cpp
#include "menu_button_page.h"
#include "app/app_state.h"
#include "app/button_functions.h"
#include "hal/leds.h"
#include "menu_buttons.h"
#include "menu_core.h"
#include <Arduino.h>
#include <stdio.h>

GEMPage* pageButtonEdit[NUM_BUTTONS];

static char pageTitle[NUM_BUTTONS][20];

static int packCallbackVal(byte buttonIndex, byte functionIndex) {
    return (int)((buttonIndex << 8) | functionIndex);
}

static void onFunctionSelected(GEMCallbackData callbackData) {
    int packed = callbackData.valInt;

    byte buttonIndex   = (packed >> 8) & 0xFF;
    byte functionIndex = packed & 0xFF;

    appState.buttonsFunctions[buttonIndex] = functionIndex;

    leds_set(buttonIndex, dimColor(BUTTON_FUNCTIONS[functionIndex].color, 10));
    menuCore_homescreen();
}

void buttonPages_init() {
    for (byte i = 0; i < NUM_BUTTONS; i++) {
        snprintf(pageTitle[i], sizeof(pageTitle[i]), "Editing button %d", i + 1);

        pageButtonEdit[i] = new GEMPage(pageTitle[i], pageButtons);

        for (byte j = 0; j < BUTTON_FUNCTION_COUNT; j++) {
            GEMItem* itemFunction = new GEMItem(
                BUTTON_FUNCTIONS[j].name,
                onFunctionSelected,
                packCallbackVal(i, j));

            pageButtonEdit[i]->addMenuItem(*itemFunction);
        }
    }
}