#include "menu_button_page.h"
#include "app/app_state.h"
#include "app/button_functions.h"
#include "app/buttons_menu_controller.h"
#include "menu_buttons.h"
#include <stdio.h>

GEMPage* pageButtonEdit[NUM_BUTTONS];

static SelectOptionByte functionOptions[BUTTON_FUNCTION_COUNT];

static GEMSelect selectFunc(BUTTON_FUNCTION_COUNT, functionOptions);

static char pageTitle[NUM_BUTTONS][20];

static void initFunctionOptions() {
    for (byte i = 0; i < BUTTON_FUNCTION_COUNT; i++) {
        functionOptions[i] = { BUTTON_FUNCTIONS[i].name, i };
    }
}

void buttonPages_init() {
    initFunctionOptions();

    for (byte i = 0; i < NUM_BUTTONS; i++) {
        snprintf(pageTitle[i], sizeof(pageTitle[i]), "Editing button %d", i + 1);

        pageButtonEdit[i] = new GEMPage(pageTitle[i], pageButtons);

        GEMItem* itemFunction = new GEMItem("Function", appState.buttons[i].function, selectFunc, buttonsMenuController_onFunctionChanged, i);
        GEMItem* itemMomentary = new GEMItem("Momentary", appState.buttons[i].momentary, buttonsMenuController_onMomentaryChanged, i);
        GEMItem* itemTime = new GEMItem("Time", appState.buttons[i].time, buttonsMenuController_onTimeChanged, i);

        pageButtonEdit[i]->addMenuItem(*itemFunction);
        pageButtonEdit[i]->addMenuItem(*itemMomentary);
        pageButtonEdit[i]->addMenuItem(*itemTime);
    }
}
