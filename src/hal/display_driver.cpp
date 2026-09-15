#include "display_driver.h"
#include "pins.h"

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

void displayDriver_init() {
    Wire.setPins(DISPLAY_SDA_PIN, DISPLAY_SCL_PIN);
    u8g2.begin();
}