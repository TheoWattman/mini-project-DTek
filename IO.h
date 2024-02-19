#pragma once
#include "Pacman.h"
#include <pic32mx.h>

// Buttons, will be 1 if its currently pressed, 0 if not.
#define button1 ((PORTF >> 1) & 0x1)	// 0001
#define button2 ((PORTD >> 5) & 0x1)	// 0010
#define button3 ((PORTD >> 6) & 0x1)	// 0100
#define button4 ((PORTD >> 7) & 0x1)	// 1000

// Returns a 4 bit integer with one byte for each button.
int getBtns();
// Moves pacman based on what buttons are currently pressed.
void handleInput(Pacman *pacman);