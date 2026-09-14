#include "menu_button_1.h"
#include "app/buttons_menu_controller.h"
#include "menu_buttons.h"
#include "../app/app_state.h"

GEMPage pageButton1("Editing button 1", pageButtons);

GEMItem itemTime("Time", appState.button1Time, buttonsMenuController_onButton1TimeChanged);
GEMItem itemMomentary("Momentary", appState.button1Momentary,buttonsMenuController_onButton1MomentaryChanged);

SelectOptionByte functionOptions[] = {
    {"None",    0},
    {"Delay", 1},
    {"Gain",   2},
    {"Looper",   3}
};
GEMSelect selectFunction(sizeof(functionOptions) / sizeof(SelectOptionByte), functionOptions);

GEMItem itemFunction("Function", appState.button1FunctionIndex, selectFunction, buttonsMenuController_onButton1FunctionIndexChanged);

void button1Menu_init() {
    pageButton1.addMenuItem(itemFunction);
    pageButton1.addMenuItem(itemMomentary);
    pageButton1.addMenuItem(itemTime);
}
