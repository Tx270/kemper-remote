#include "menu_button_page.h"
#include "app/app_state.h"
#include "app/buttons_menu_controller.h"
#include "menu_buttons.h"
#include <stdio.h>

GEMPage* pageButtonEdit[NUM_BUTTONS];

static SelectOptionByte functionOptions[] = {
    {"None",           BTN_FUNC_NONE},
    {"Program Change", BTN_FUNC_PROGRAM_CHANGE},
    {"Control Change", BTN_FUNC_CONTROL_CHANGE}
};
GEMSelect selectFunc(sizeof(functionOptions) / sizeof(SelectOptionByte), functionOptions);

static char pageTitle[NUM_BUTTONS][20];

void buttonPages_init() {
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
