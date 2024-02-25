#include "Pickups.h"


extern uint8_t entityMap[];
extern uint8_t gridMap[];

void initEntityMap() {

    int i = 2;
    for (i; i < 62; i++)
    {
        entityMap[i] = ~gridMap[i];
    }
    
}

void drawEntityMap(Pacman *pacman) {

    int i, j;
    int w = entityMap[0];
    int h = entityMap[1];

    int n = 0;

    for (i = 0; i < h; i++) {
        for (j = 0; j < w; j++) {
            if((entityMap[2 + n / 8] & (0x1 << (7 - n % 8))) != 0) {
                putPixel(j * GRIDSIZE + 2 - pacman->cameraX, i * GRIDSIZE + 2 - pacman->cameraY); 
                if((j == 1 && i == 3) || (j == 23 && i == 3) || (j == 1 && i == 13) || (j == 23 && i == 13)) {
                    putPixel(j * GRIDSIZE + 2 - pacman->cameraX - 1, i * GRIDSIZE + 2 - pacman->cameraY);
                    putPixel(j * GRIDSIZE + 2 - pacman->cameraX + 1, i * GRIDSIZE + 2 - pacman->cameraY);
                    putPixel(j * GRIDSIZE + 2 - pacman->cameraX, i * GRIDSIZE + 2 - pacman->cameraY - 1);
                    putPixel(j * GRIDSIZE + 2 - pacman->cameraX, i * GRIDSIZE + 2 - pacman->cameraY + 1);
                }
            }
            
            n += 1;
        }
    }
}

void checkPickup(int x, int y, Ghost *ghost, int* score) {

    // Checks grid at given location, returns 0 if it is empty and 1 if it is a wall

    int byte = (y * entityMap[0] + x) / 8;
    int bit =  7 - (y * entityMap[0] + x) % 8;

    if(entityMap[byte + 2] & (0x1 << bit)) {
        entityMap[byte + 2] &= ~(0x1 << bit); // clear pac food
        *score += 10;
        if((x == 1 && y == 3) || (x == 23 && y == 3) || (x == 1 && y == 13) || (x == 23 && y == 13)) {
            int i = 0;
            for (i; i < GHOST_AMOUNT; i++){
                changeGhostState(&ghost[i], FLEE);
            }
            *score += 40;
        }
    }
}

int entityMapIsClear() {
    int i = 2;
    for (i; i < 62; i++){
        if(entityMap[i]) return 0;
    }
    return 1;
}