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
#include "midi/midi_state_machine.h"
#include "midi/midi_transport.h"

void setup() {
    Serial.begin(115200);
    while (!Serial) { delay(10); }

    buttons_init();
    midiSM_init();    // midi state mashine
    settingsController_onEnableWifiChanged(); // init wifi based on saved appState

    if (HAS_DISPLAY) {
        // setup screen
        displayDriver_init();
        // setup GEM menu
        buttonPages_init();   // builds pageButtonEdit[0..NUM_BUTTONS-1]
        buttonsMenu_init();   // links to each pageButtonEdit[i]
        rootMenu_init();      // links to pageButtons
        menuCore_init();      // actual menu logic and drawing
    }

    if (HAS_LEDS) leds_init();
}

void loop() {
    midiTransport_read();                  // read incoming midi
    midiSM_update();                       // update midi state mashine
    if (HAS_DISPLAY) menuCore_update();    // all ui updates
    buttons_update();                      // reading foot buttons
}
