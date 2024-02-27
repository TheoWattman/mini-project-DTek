#pragma once

#include <pic32mx.h>
#include <stdint.h>
#include "IO.h"

// places the score and initials in the highscore list
void storeHighScore(char* initials, int score); // Isac

// updates the main meny screen
void menuScreenDisplay(int frame); // Isac

// updates the highscore list
void scoreDisplay(); // Isac

// updates the game control screen
void controlDisplay(); // Isac

// updates the screen where you enter your initials
void enterNameDisplay(char *initials, int pos); // Isac

// the highscore list menu
void scores(); // Isac

// the control screen
void controls(); // Isac

// the main menun
void mainMenu(); // Isac

// the "enter you name" screen
void enterName(int score); // Isac

// updates the animation
void menuAnimation(int frame); // Theo