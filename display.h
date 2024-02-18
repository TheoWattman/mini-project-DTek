#pragma once
#include "stdint.h"

void putPixel(int x, int y);
void clearDisplay();
void displayChar(const uint8_t x, const uint8_t y, char character, const uint8_t *font);
void displayString(const uint8_t x, const uint8_t y, char *character, const uint8_t *font);
void displayBitarray(const int x, const int y, const uint8_t *byteArray);