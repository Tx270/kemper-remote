#include "menu_buttons.h"
#include "menu_root.h"
#include "menu_button_1.h"

GEMPage pageButtons("Choose button to edit", pageRoot);

GEMItem itemGoButton1("Button 1", pageButton1);

void buttonsMenu_init() {
    pageButtons.addMenuItem(itemGoButton1);
}