#pragma once
#include "Pacman.h"
#include <pic32mx.h>

// #include <windows.h>

#define button1 ((PORTF >> 1) & 0x1)	// 0001
#define button2 ((PORTD >> 5) & 0x1)	// 0010
#define button3 ((PORTD >> 6) & 0x1)	// 0100
#define button4 ((PORTD >> 7) & 0x1)	// 1000

int getBtns();

void handleInput(Pacman *pacman);