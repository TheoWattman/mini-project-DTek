#include <stdint.h>
#include "display.h"
#include "Pacman.h"
#include "Ghost.h"

// Initializes all pickups in a bit array.
void initEntityMap(); // Isac

// Draws pickups.
void drawEntityMap(Pacman *pacman); // Isac

// Checks if player is currently standing on a pickup.
void checkPickup(int x, int y, Ghost *ghost, int* score); // Isac

// Checks if player has cleared all pickups.
int entityMapIsClear(); // Theo