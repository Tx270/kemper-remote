#include "menu_buttons.h"
#include "menu_root.h"
#include "menu_button_page.h"
#include "../app/app_state.h"
#include <stdio.h>

GEMPage pageButtons("Choose button to edit", pageRoot);

static char linkTitle[NUM_BUTTONS][12];

void buttonsMenu_init() {
    for (byte i = 0; i < NUM_BUTTONS; i++) {
        snprintf(linkTitle[i], sizeof(linkTitle[i]), "Button %d", i + 1);

        GEMItem* itemGoButton = new GEMItem(linkTitle[i], *pageButtonEdit[i]);
        pageButtons.addMenuItem(*itemGoButton);
    }
}
