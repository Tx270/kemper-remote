#include "input.h"
#include <GEM_u8g2.h>   // for the GEM_KEY_* constants

bool input_poll(byte &key) {
    if (!Serial.available()) {
        return false;
    }

    char c = Serial.read();

    switch (c) {
        case 'w': key = GEM_KEY_UP;    return true;
        case 's': key = GEM_KEY_DOWN;  return true;
        case 'a': key = GEM_KEY_LEFT;  return true;
        case 'd': key = GEM_KEY_RIGHT; return true;

        case 'o':
        case '\r':
        case '\n':
            key = GEM_KEY_OK;
            return true;

        case 'c':
        case 'x':
            key = GEM_KEY_CANCEL;
            return true;

        default:
            // Ignore anything else (stray newlines, typos, etc.)
            return false;
    }
}