#include <Arduino.h>
#include "hal/display_driver.h"
#include "menu/menu_core.h"
#include "menu/menu_root.h"


void setup() {
    Serial.begin(115200);
    while (!Serial) { delay(10); }

    displayDriver_init();

    rootMenu_init();

    menuCore_init();
    
    Serial.println(F("Menu ready."));
}

void loop() {
    menuCore_update();
}