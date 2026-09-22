#include <Arduino.h>
#include "WiFi.h"
#include "app/app_state.h"
#include "app/settings_store.h"
#include "config.h"
#include "app/settings_controller.h"
#include "app/button_action_controller.h"
#include "hal/display_driver.h"
#include "hal/buttons.h"
#include "hal/leds.h"
#include "hal/storage.h"
#include "menu/menu_core.h"
#include "menu/menu_root.h"
#include "menu/menu_buttons.h"
#include "menu/menu_button_page.h"
#include "midi/midi_state_machine.h"
#include "midi/midi_transport.h"

void setup() {
    Serial.begin(115200);
    while (!Serial) { delay(10); }

    if (HAS_LEDS) leds_init();

    storage_init();                                 // mount LittleFS
    settingsStore_load();
    
    buttons_init();
    midiSM_init();                                  // midi state mashine

    if (appState.settings.enableWifi) {
        settingsController_onEnableWifiChanged();   // init wifi based on saved appState
    } else {    
        WiFi.mode(WIFI_OFF);
    }

    if (HAS_DISPLAY) {
        // setup screen
        displayDriver_init();
        // setup GEM menu
        buttonPages_init();   // builds pageButtonEdit[0..NUM_BUTTONS-1]
        buttonsMenu_init();   // links to each pageButtonEdit[i]
        rootMenu_init();      // links to pageButtons
        menuCore_init();      // actual menu logic and drawing
    }
}

void loop() {
    midiTransport_read();                  // read incoming midi
    midiSM_update();                       // update midi state mashine
    if (HAS_DISPLAY) menuCore_update();    // all ui updates
    buttons_update();                      // reading foot buttons
}
