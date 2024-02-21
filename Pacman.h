#pragma once
#include ".globals.h"
#include <stdint.h>
#include "display.h"
#include <stdio.h>

// Player Object
typedef struct 
{
    // Precise position
    int x;
    int y;

    // Target grid, Pacman will in the direction of the target grid until it arrives at the given grid
    int targetX;
    int targetY;
    // The direction that Pacman will travel, will always be towards the target grid.
    int dirX;
    int dirY;
    // The position of the camera
    int cameraX;
    int cameraY;

    int lives;
} Pacman;

// Intializes Pacman
void initPacman(Pacman *pacman);

// Checks if the given position is a wall or not
uint8_t checkCollision(int x, int y);

// Displays Pacman
void displayPacman(Pacman *pacman);

// Updates the position of Pacman and the camera
void updatePacman(Pacman* pacman);

// Teleports Pacman to a given grid
void teleport(Pacman *pacman, int targetX, int targetY);

void gameOverAnimation(Pacman *pacman);