#ifndef OLED_AUTO_FIT_TEXT_H
#define OLED_AUTO_FIT_TEXT_H

#include <Arduino.h>
#include <U8g2lib.h>
#include <vector>

struct FitResult {
    const uint8_t* font;
    std::vector<String> lines;
    uint16_t lineHeight;
    uint16_t totalHeight;
};

class OledAutoFitText {
public:
    OledAutoFitText(U8G2 &u8g2, const uint8_t* const* fonts, uint8_t fontCount,
                    uint16_t screenW, uint16_t screenH,
                    uint16_t paddingX = 2, uint16_t paddingY = 2);

    void setPadding(uint16_t paddingX, uint16_t paddingY);
    void draw(const String &text);

private:
    U8G2 &_u8g2;
    const uint8_t* const* _fonts;
    uint8_t _fontCount;
    uint16_t _screenW;
    uint16_t _screenH;
    uint16_t _paddingX;
    uint16_t _paddingY;

    std::vector<String> wrapText(const String &text, uint16_t maxWidth);
    bool tryFit(const String &text, const uint8_t* font,
                uint16_t maxWidth, uint16_t maxHeight, FitResult &result);
};

#endif // OLED_AUTO_FIT_TEXT_H