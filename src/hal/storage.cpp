#include "storage.h"
#include <LittleFS.h>

void storage_init() {
    if (!LittleFS.begin(true)) {
        Serial.println(F("[Storage] LittleFS mount failed even after format"));
    }
}

bool storage_writeFile(const char* path, const void* data, size_t len) {
    File f = LittleFS.open(path, "w");
    if (!f) {
        Serial.print(F("[Storage] Failed to open for write: "));
        Serial.println(path);
        return false;
    }
    size_t written = f.write((const uint8_t*)data, len);
    f.close();

    if (written != len) {
        Serial.print(F("[Storage] Short write on: "));
        Serial.println(path);
        return false;
    }
    return true;
}

bool storage_readFile(const char* path, void* data, size_t len) {
    if (!LittleFS.exists(path)) return false;

    File f = LittleFS.open(path, "r");
    if (!f) return false;

    size_t readLen = f.read((uint8_t*)data, len);
    f.close();
    return readLen == len;
}

bool storage_exists(const char* path) { return LittleFS.exists(path); }
bool storage_remove(const char* path) { return LittleFS.remove(path); }