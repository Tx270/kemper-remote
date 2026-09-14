#include "display_driver.h"

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

void displayDriver_init() {
    Wire.setPins(11, 10);
    u8g2.begin();

    Serial.println(F("Ready. Waiting for input."));
}