#pragma once
#include "stdint.h"
#include <pic32mx.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>

// from the chipkit ref manual
uint8_t spi_put_byte(uint8_t bVal);

// Puts a pixel in the displayBuffer
void putPixel(uint8_t x, uint8_t y); // Theo

// Clears a pixel in the displayBuffer;
void putNotPixel(uint8_t x, uint8_t y);

// Displays a character.
void displayChar(const uint8_t x, const uint8_t y, char character, const uint8_t *font); // Theo

// Displays a String
void displayString(const uint8_t x, const uint8_t y, char *character, const uint8_t *font); // Theo

// Pauses the program for a few cycles
void sleep(int cyc);

// Displays array of bits at a given x and y coordinate.
void displayBitarray(const uint8_t x, const uint8_t y, const uint8_t *byteArray); // Theo

// Clears the display
void clearDisplay(void); // Theo

// from the chipkit ref manual
void displayRow(uint8_t byteAmount, uint8_t * buffer);

// Displays a line with a given x, y and length.
void displayLine(int x, int y, int len); // Theo
 
// Displays a rectangle with a given x, y, width and length.
void displayRect(int x, int y, int width, int height); // Theo

// Clears a line with a given x, y and length.
void displayNotLine(int x, int y, int len) ;

// Clears a rectangle with a given x, y, width and length.
void clearRect(int x, int y, int width, int height); // Theo

// Displays the score.
void displayScore(int score);

// converts an int to a string
void numToString(int score, char* str);

// Sends the displayBuffer to the display and updates it.
// from the chipkit ref manual
void updateDisplay();

// from the chipkit ref manual
void displayInit(void);

// From github at https://github.com/is1200-example-projects/hello-display/blob/master/main.c#L271
void SPIInit(void);