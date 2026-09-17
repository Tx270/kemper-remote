#include "OledAutoFitText.h"

OledAutoFitText::OledAutoFitText(U8G2 &u8g2, const uint8_t* const* fonts, uint8_t fontCount,
                                 uint16_t screenW, uint16_t screenH,
                                 uint16_t paddingX, uint16_t paddingY)
  : _u8g2(u8g2), _fonts(fonts), _fontCount(fontCount),
    _screenW(screenW), _screenH(screenH),
    _paddingX(paddingX), _paddingY(paddingY) {}

void OledAutoFitText::setPadding(uint16_t paddingX, uint16_t paddingY) {
    _paddingX = paddingX;
    _paddingY = paddingY;
}

std::vector<String> OledAutoFitText::wrapText(const String &text, uint16_t maxWidth) {
    std::vector<String> lines;
    int start = 0;
    int len = text.length();

    while (start < len) {
        int end = len;
        String candidate = text.substring(start, end);

        // Zapobieganie ścinaniu/zawijaniu ostatniego glifu:
        // U8g2 mierzy "advance width", ale krawędź litery może wystawać o 1-2px.
        // Dlatego dodajemy małą poprawkę (2px) do testowanej szerokości.
        while ((_u8g2.getStrWidth(candidate.c_str()) + 2) > maxWidth && end > start) {
            int spacePos = text.lastIndexOf(' ', end - 1);
            if (spacePos > start) {
                end = spacePos;
            } else {
                end--;
            }
            candidate = text.substring(start, end);
        }

        lines.push_back(candidate);
        start = end;
        while (start < len && text[start] == ' ') start++;
    }

    return lines;
}

bool OledAutoFitText::tryFit(const String &text, const uint8_t* font,
                             uint16_t maxWidth, uint16_t maxHeight, FitResult &result) {
    _u8g2.setFont(font);
    
    // Obliczanie wysokości linii na podstawie Ascent/Descent
    int ascent  = _u8g2.getAscent();
    int descent = _u8g2.getDescent(); // wartość ujemna
    int lineHeight = ascent - descent;

    std::vector<String> lines = wrapText(text, maxWidth);
    int totalHeight = lines.size() * lineHeight;

    if (totalHeight > maxHeight) return false;

    // Dodatkowa weryfikacja czy żaden wiersz nie przekracza maxWidth
    for (auto &l : lines) {
        if ((_u8g2.getStrWidth(l.c_str()) + 2) > maxWidth) return false;
    }

    result.font = font;
    result.lines = lines;
    result.lineHeight = lineHeight;
    result.totalHeight = totalHeight;
    return true;
}

void OledAutoFitText::draw(const String &text) {
    // Uwzględnienie wbudowanego paddingu
    uint16_t maxWidth  = (_screenW > 2 * _paddingX) ? (_screenW - 2 * _paddingX) : _screenW;
    uint16_t maxHeight = (_screenH > 2 * _paddingY) ? (_screenH - 2 * _paddingY) : _screenH;

    FitResult best;
    bool found = false;

    for (uint8_t i = 0; i < _fontCount; i++) {
        if (tryFit(text, _fonts[i], maxWidth, maxHeight, best)) {
            found = true;
            break; // Wybiera pierwszą (największą) pasującą czcionkę
        }
    }

    if (!found) {
        // Jeśli żadna się nie mieści, użyj najmniejszej dostępnej
        const uint8_t* smallest = _fonts[_fontCount - 1];
        _u8g2.setFont(smallest);
        int ascent  = _u8g2.getAscent();
        int descent = _u8g2.getDescent();
        best.font = smallest;
        best.lines = wrapText(text, maxWidth);
        best.lineHeight = ascent - descent;
        best.totalHeight = best.lines.size() * best.lineHeight;
    }

    // Ustawienia do wyrenderowania tekstu
    _u8g2.setFont(best.font);
    _u8g2.setFontPosTop(); // Pozycjonowanie od górnej krawędzi (kluczowe dla poprawnego $Y$)

    // Wyznaczenie pozycji początkowej $Y$ z uwzględnieniem wyśrodkowania i paddingu
    int startY = _paddingY + (maxHeight - best.totalHeight) / 2;

    for (auto &line : best.lines) {
        int w = _u8g2.getStrWidth(line.c_str());
        int x = _paddingX + (maxWidth - w) / 2; // Wyśrodkowanie w poziomie wewnątrz obszaru paddingu
        
        _u8g2.drawStr(x, startY, line.c_str());
        startY += best.lineHeight;
    }
}