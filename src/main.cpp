#include <Arduino.h>
#include "hal/display_driver.h"
#include "menu/menu_core.h"
#include "menu/menu_root.h"
#include "menu/menu_buttons.h"
#include "menu/menu_button_1.h"


void setup() {
    Serial.begin(115200);
    while (!Serial) { delay(10); }

    displayDriver_init();

    button1Menu_init();
    buttonsMenu_init();
    rootMenu_init();

    menuCore_init();
    
    Serial.println(F("Menu ready."));
}

void loop() {
    menuCore_update();
}