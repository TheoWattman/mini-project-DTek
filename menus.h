#pragma once

#include <pic32mx.h>
#include <stdint.h>
#include "IO.h"

void storeHighScore(char* initials, int score);

void menuScreenDisplay();

void scoreDisplay();

void controlDisplay();

void enterNameDisplay(char *initials, int pos);

void scores();

void controls();

void mainMenu();

void enterName(int score);
