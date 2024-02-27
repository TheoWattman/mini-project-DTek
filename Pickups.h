#include <stdint.h>
#include "display.h"
#include "Pacman.h"
#include "Ghost.h"

// Initializes all pickups in a bit array.
void initEntityMap();

// Draws pickups.
void drawEntityMap(Pacman *pacman);

// Checks if player is currently standing on a pickup.
void checkPickup(int x, int y, Ghost *ghost, int* score);

// Checks if player has cleared all pickups.
int entityMapIsClear();