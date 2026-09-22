#pragma once
#include <Arduino.h>

void storage_init();

bool storage_writeFile(const char* path, const void* data, size_t len);
bool storage_readFile(const char* path, void* data, size_t len);
bool storage_exists(const char* path);
bool storage_remove(const char* path);