#include <Arduino.h>
#include "hal/display_driver.h"
#include "menu/menu_core.h"
#include "menu/menu_root.h"
#include "menu/menu_buttons.h"
#include "menu/menu_button_page.h"

void setup() {
    Serial.begin(115200);
    while (!Serial) { delay(10); }

    displayDriver_init(); // setup screen

    // GEM menu setup
    buttonPages_init();   // builds pageButtonEdit[0..NUM_BUTTONS-1]
    buttonsMenu_init();   // links to each pageButtonEdit[i]
    rootMenu_init();      // links to pageButtons
    menuCore_init();      // actual menu logic and drawing
}

void loop() {
    menuCore_update();
}
