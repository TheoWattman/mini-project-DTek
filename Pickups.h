#include <stdint.h>
#include "display.h"
#include "Pacman.h"
#include "Ghost.h"

// Initializes all pickups in a bit array.
void initEntityMap();

void drawEntityMap(Pacman *pacman);

void checkPickup(int x, int y, Ghost *ghost, int* score);

int entityMapIsClear();