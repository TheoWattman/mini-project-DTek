#pragma once

#include <pic32mx.h>
#include <stdint.h>
#include "IO.h"

// places the score and initials in the highscore list
void storeHighScore(char* initials, int score);

// updates the main meny screen
void menuScreenDisplay(int frame);

// updates the highscore list
void scoreDisplay();

// updates the game control screen
void controlDisplay();

// updates the screen where you enter your initials
void enterNameDisplay(char *initials, int pos);

// the highscore list menu
void scores();

// the control screen
void controls();

// the main menun
void mainMenu();

// the "enter you name" screen
void enterName(int score);

// updates the animation
void menuAnimation(int frame);