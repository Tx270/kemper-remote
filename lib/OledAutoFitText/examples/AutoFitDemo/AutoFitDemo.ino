/*
  OledAutoFitText demo
  ---------------------
  Type a line in Serial Monitor (115200 baud) and press Enter —
  it's rendered centered, word-wrapped, and as large as possible.

  Library needed: U8g2 (by olikraus), plus this OledAutoFitText library.
*/

#include <Wire.h>
#include <U8g2lib.h>
#include <OledAutoFitText.h>

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

const uint16_t SCREEN_W = 128;
const uint16_t SCREEN_H = 64;

// Fonts tried largest -> smallest. Swap in any u8g2 fonts you like,
// just keep them ordered biggest to smallest.
const uint8_t* fontList[] = {
  u8g2_font_ncenB24_tr,
  u8g2_font_ncenB18_tr,
  u8g2_font_ncenB14_tr,
  u8g2_font_ncenB10_tr,
  u8g2_font_ncenB08_tr
};
const uint8_t fontCount = sizeof(fontList) / sizeof(fontList[0]);

OledAutoFitText autofit(u8g2, fontList, fontCount, SCREEN_W, SCREEN_H);

void setup() {
  Serial.begin(115200);
  delay(300);

  Wire.begin(11, 10);

  u8g2.begin();

  Serial.println(F("Type text and press Enter to render it centered/auto-fit."));
  autofit.draw("Hello!");
}

void loop() {
  if (Serial.available()) {
    String line = Serial.readStringUntil('\n');
    line.trim();
    if (line.length() > 0) {
      autofit.draw(line);
    }
  }
}
