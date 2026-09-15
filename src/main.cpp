#include <Arduino.h>
#include "config.h"
#include "app/settings_controller.h"
#include "app/button_action_controller.h"
#include "hal/display_driver.h"
#include "hal/buttons.h"
#include "hal/leds.h"
#include "menu/menu_core.h"
#include "menu/menu_root.h"
#include "menu/menu_buttons.h"
#include "menu/menu_button_page.h"

void setup() {
    Serial.begin(115200);
    while (!Serial) { delay(10); }

    buttons_init();

    if (HAS_DISPLAY) {
        // setup screen
        displayDriver_init();
        // setup GEM menu
        buttonPages_init();   // builds pageButtonEdit[0..NUM_BUTTONS-1]
        buttonsMenu_init();   // links to each pageButtonEdit[i]
        rootMenu_init();      // links to pageButtons
        menuCore_init();      // actual menu logic and drawing
    }

    if (HAS_LEDS) {
        leds_init();
    }
    
    // init wifi based on saved appState
    settingsController_onEnableWifiChanged();
}

void loop() {
    if (HAS_DISPLAY) menuCore_update();    // all ui updates
    buttons_update();                      // reading foot buttons
}
