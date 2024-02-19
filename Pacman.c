#include "Pacman.h"

extern uint8_t left[];
extern uint8_t up[];
extern uint8_t right[];
extern uint8_t down[];
extern uint8_t defaultPac[];
extern uint8_t gridMap[];

// Game over animation
extern uint8_t GO_anim[7][6];

void initPacman(Pacman *pacman) {
    pacman->x = 25;
    pacman->y = 25;

    pacman->targetX = 5;
    pacman->targetY = 5;

    pacman->dirX = 0;
    pacman->dirY = 0;

    pacman->cameraX = -1;
    pacman->cameraY = 0;
}

uint8_t checkCollision(int x, int y) {

    if(x >= GRIDWIDTH || x < 0 || y >= GRIDHEIGHT || y < 0);

    // Checks grid at given location, returns 0 if it is empty and 1 if it is a wall

    int byte = (y * gridMap[0] + x) / 8;
    int bit =  7 - (y * gridMap[0] + x) % 8;

    return gridMap[byte + 2] & (0x1 << bit);
}

void displayPacman(Pacman *pacman) {

    // Displays the correct sprite based on the direction of the player.

    if(pacman->dirX == -1)
        displayBitarray(pacman->x - pacman->cameraX, pacman->y - pacman->cameraY,left);
    else if(pacman->dirX == 1)
        displayBitarray(pacman->x - pacman->cameraX, pacman->y - pacman->cameraY,right);
    else if(pacman->dirY == -1)
        displayBitarray(pacman->x - pacman->cameraX, pacman->y - pacman->cameraY,up);
    else if(pacman->dirY == 1)
        displayBitarray(pacman->x - pacman->cameraX, pacman->y - pacman->cameraY,down);
    else {
        displayBitarray(pacman->x - pacman->cameraX, pacman->y - pacman->cameraY,defaultPac);
    }
}

void updatePacman(Pacman* pacman) {
    pacman->x += pacman->dirX;
    pacman->y += pacman->dirY;

    if(pacman->y < 15) {      // If the player is in the top 3 grids, lock camera to top.
        pacman->cameraY = 0;
    } else if(pacman->y >= 80) { // If the player is in the bottom 3 grids, lock camera to bottom.
        pacman->cameraY = PIXEL_OFFSET_BOTTOM;
    } else {
        pacman->cameraY = pacman->y - PIXEL_OFFSET_MIDDLE;
    }
}

void teleport(Pacman *pacman, int targetX, int targetY) {
    pacman->targetX = targetX;
    pacman->targetY = targetY;

    pacman->x = targetX * GRIDSIZE;
    pacman->y = targetY * GRIDSIZE;
}

void gameOverAnimation(Pacman *pacman) {
    int i = 0;
    for (i; i <= 6; i++){
        sleep(1000000);
        clearRect(pacman->x - pacman->cameraX, pacman->y - pacman->cameraY, 5, 5);
        displayBitarray(pacman->x - pacman->cameraX, pacman->y - pacman->cameraY, GO_anim[i]);
        updateDisplay();
    }
    sleep(1000000);
}