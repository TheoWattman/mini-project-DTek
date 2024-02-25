#pragma once
#include <stdint.h>
#include ".globals.h"
#include "Pacman.h"
#include <stdio.h>
#include <stdbool.h>

// Ghost states
#define SCATTER  0
#define CHASE    1
#define FLEE     2
#define DEAD     3

// Ghost types
#define BLINKY 0
#define INKY 1
#define PINKY 2
#define CLYDE 3

// Ghost counter
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
    // The current state of the ghost:
    // SCATTER - Marches around a given grid
    // CHASE - Chases Pacman
    // FLEE - Flees from Pacman, usually after Pacman eats a power pallet
    uint8_t state;
    // Counter, will count towards a new state
    int counter;
    // Type of ghost,
    // AGGRESSIVE - Will chase player directly 
    // STRATEGIC - Will try to cut off the player by working directly together with an AGGRESSIVE ghost.
    uint8_t ghost_type;
} Ghost;

// Initializes the Ghost
void initGhost(Ghost *ghost, int type);

// Pathfinding for the Ghost, finds the next target grid depending on state.
// - Chase: Next grid is the adjacent grid closest to the final target
// - Flee: Next grid is the adjacent grid furthest to the final target
void findGhostPath(Ghost *ghost, int targetX, int targetY, uint8_t type);

// Displays the ghost
void displayGhost(Ghost *ghost, Pacman *pacman);

// Teleports the ghost to a given grid
void teleportGhost(Ghost *ghost, int targetX, int targetY);

// Updates the ghost's path, position, direction etc. 
void updateGhosts(Ghost *ghost, Pacman *pacman);

// Checks if ghost is colliding with pacman, if so it handles it accordingly.
// Ghost dies if currently fleeing otherwise pacman dies.
int handlePacmanGhostCollision(Ghost *ghost, Pacman *pacman, int *score);

// Select target grid based on ghost type.
void ChasePacman(Ghost *ghost, Pacman *pacman);

// Changes state of the ghost
void changeGhostState(Ghost *ghost, int state);