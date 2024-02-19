#include "data.h"
#include ".globals.h"
#include "display.h"
#include "Pacman.h"
#include "Ghost.h"
#include "IO.h"
#include "Pickups.h"

void updateDisplay();

int game() {

    Pacman pacman;
    initPacman(&pacman);

    Ghost ghosts[GHOST_AMOUNT];
    initGhost(&ghosts[0], BLINKY);
    initGhost(&ghosts[1], INKY);
    initGhost(&ghosts[2], CLYDE);
    initGhost(&ghosts[3], PINKY);

    initEntityMap();

    int score = 0;

    while(1) {
        // Sleep(FRAMELENGTH);
        sleep(150000);
        // handleMSGs(); 
        clearDisplay();

        // Check if Pacman is colliding with ghosts and handles it accordingly
        handlePacmanGhostCollision(ghosts, &pacman);

        // Update position and behavior of player and enemy.
        updateGhosts(ghosts, &pacman);
        updatePacman(&pacman);

        // Update visuals of player, map and enemies.
        drawEntityMap(&pacman);                                     // Draw pickups
        displayBitarray(-pacman.cameraX, -pacman.cameraY, map);     // Draw Map with offset of camera position
        displayGhosts(ghosts, &pacman);                           
        displayPacman(&pacman);

        displayScore(score);

        if(pacman.x == pacman.targetX * GRIDSIZE && pacman.y == pacman.targetY * GRIDSIZE) { // If player is at target grid.
            
            checkPickup(pacman.targetX, pacman.targetY, ghosts, &score);
            handleInput(&pacman);

            if(!checkCollision(pacman.targetX + pacman.dirX, pacman.targetY + pacman.dirY)) {
                pacman.targetX += pacman.dirX;
                pacman.targetY += pacman.dirY;
            } else {
                if(pacman.targetX == 24 && pacman.targetY == 9){    // At right teleporter
                    teleport(&pacman, 0, 9);
                    updateGhosts(ghosts, &pacman);
                    continue;
                }
                else if(pacman.targetX == 0 && pacman.targetY == 9){   // At left teleporter
                    teleport(&pacman, 24, 9);
                    updateGhosts(ghosts, &pacman);
                    continue;
                } else {
                    pacman.dirX = 0;
                    pacman.dirY = 0;
                }
            }
        }

        updateDisplay();
    }

    return 0;
}
