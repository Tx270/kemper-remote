#include "home_screen.h"
#include "../hal/display_driver.h"
#include "../app/app_state.h"
#include "../config.h"
#include <OledAutoFitText.h>

const uint8_t* fontList[] = {
  u8g2_font_helvB24_tr,
  u8g2_font_helvB18_tr,
  u8g2_font_helvB14_tr,
  u8g2_font_helvB10_tr,
  u8g2_font_helvB08_tr
};
const uint8_t fontCount = sizeof(fontList) / sizeof(fontList[0]);


void homeScreen_draw() {
    static OledAutoFitText autofit(u8g2, fontList, fontCount, DISPLAY_W, DISPLAY_H, 20, 20);
    u8g2.clearBuffer();
    autofit.draw(appState.rigName);
    u8g2.sendBuffer();
}