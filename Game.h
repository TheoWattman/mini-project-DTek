#include "data.h"
#include ".globals.h"
#include "display.h"
#include "Pacman.h"
#include "Ghost.h"
#include "IO.h"
#include "Pickups.h"

void updateDisplay();

uint8_t programmeState = inGame;

int game() {

    Pacman pacman;
    initPacman(&pacman);

    Ghost ghost;
    initGhost(&ghost);

    initEntityMap();

    int score = 0;

    while(1) {
        // Sleep(FRAMELENGTH);
        sleep(150000);
        // handleMSGs(); 
        clearDisplay();

        // Check if Pacman is colliding with ghosts and handles it accordingly
        if(handlePacmanGhostCollision(&ghost, &pacman)) break;

        // Update position and behavior of player and enemy.
        updateGhosts(&ghost, &pacman);
        updatePacman(&pacman);

        // Update visuals of player, map and enemies.
        drawEntityMap(&pacman);                                     // Draw pickups
        displayBitarray(-pacman.cameraX, -pacman.cameraY, map);     // Draw Map with offset of camera position
        displayGhost(&ghost, &pacman);                                 // 
        displayPacman(&pacman);

        displayScore(score);

        if(pacman.x == pacman.targetX * GRIDSIZE && pacman.y == pacman.targetY * GRIDSIZE) { // If player is at target grid.
            
            checkPickup(pacman.targetX, pacman.targetY, &ghost, &score);
            handleInput(&pacman);

            if(!checkCollision(pacman.targetX + pacman.dirX, pacman.targetY + pacman.dirY)) {
                pacman.targetX += pacman.dirX;
                pacman.targetY += pacman.dirY;
            } else {
                if(pacman.targetX == 24 && pacman.targetY == 9){    // At right teleporter
                    teleport(&pacman, 0, 9);
                    updateGhosts(&ghost, &pacman);
                }
                else if(pacman.targetX == 0 && pacman.targetY == 9){   // At left teleporter
                    teleport(&pacman, 24, 9);
                    updateGhosts(&ghost, &pacman);
                } else {
                    pacman.dirX = 0;
                    pacman.dirY = 0;
                }
            }
        }

        updateDisplay();
    }

    enterName(score);

    return 0;
}
