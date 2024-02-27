#pragma once
#include <stdint.h>
#include ".globals.h"
#include "Pacman.h"
#include <stdio.h>
#include <stdbool.h>

// Ghost states
#define SCATTER 0
#define CHASE   1
#define FLEE    2
#define DEAD    3

// Ghost types
#define BLINKY  0
#define INKY    1
#define PINKY   2
#define CLYDE   3

// Ghost counter
// Defines how long each state is.
#define CHASE_COUNTER 500
#define SCATTER_COUNTER 200
#define FLEE_COUNTER 200

typedef struct {
    // Precise position
    int x;
    int y;
    // Target grid, the ghost will in the direction of the target grid until it arrives at the given grid
    int targetX;
    int targetY;
    // The direction that the ghost will travel, will always be towards the target grid.
    int dirX;
    int dirY;
    // The grid that the ghost travels to during SCATTER mode
    int scatterX;
    int scatterY;
    // The current state of the ghost,
    // SCATTER - Marches around a given grid
    // CHASE - Chases Pacman
    // FLEE - Flees from Pacman, usually after Pacman eats a power pallet
    uint8_t state;
    // Counter, will count towards a new state
    int counter;
    // Type of ghost,
    // BLINKY - Will chase player directly 
    // INKY - Will work together with Blinky to try to cut of the player
    // PINKY - Will chase a few grids ahead of the player.
    // CLYDE - Will chase pacman if far enough away, flees otherwise.
    uint8_t ghost_type;
} Ghost; // Theo

// Initializes the Ghost
void initGhost(Ghost *ghost, int type); // Theo

// Pathfinding for the Ghost, finds the next target grid depending on state.
// - Chase: Next grid is the adjacent grid closest to the final target
// - Flee: Next grid is the adjacent grid furthest to the final target
void findGhostPath(Ghost *ghost, int targetX, int targetY, uint8_t type); // Theo

// Displays the ghost
void displayGhost(Ghost *ghost, Pacman *pacman); // Theo

// Teleports the ghost to a given grid
void teleportGhost(Ghost *ghost, int targetX, int targetY); // Theo

// Updates the ghost's path, position, direction etc. 
void updateGhosts(Ghost *ghost, Pacman *pacman); // Theo

// Checks if ghost is colliding with pacman, if so it handles it accordingly.
// Ghost dies if currently fleeing otherwise pacman dies.
int handlePacmanGhostCollision(Ghost *ghost, Pacman *pacman, int *score); // Theo

// Select target grid based on ghost type.
void ChasePacman(Ghost *ghost, Pacman *pacman); // Theo

// Changes state of the ghost
void changeGhostState(Ghost *ghost, int state); // Theo