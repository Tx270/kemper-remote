#include "home_screen.h"
#include "../hal/display_driver.h"
#include "../app/app_state.h"
#include <stdio.h>

void homeScreen_draw() {
    u8g2.clearBuffer();

    u8g2.setFont(u8g2_font_ncenB08_tr);
    u8g2.drawStr(0, 12, appState.rigName);

    u8g2.setFont(u8g2_font_6x10_tr);
    char line[32];
    snprintf(line, sizeof(line), "Brightness: %d", appState.brightness);
    u8g2.drawStr(0, 30, line);

    u8g2.sendBuffer();
}