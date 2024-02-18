#include "IO.h"

int getBtns() {
    return (button4 << 3) | (button3 << 2) | (button2 << 1) | button1;
}

void handleInput(Pacman *pacman) {
        if(button1) {
            if(!checkCollision(pacman->targetX + 1, pacman->targetY)) {
                pacman->dirX = 1;
                pacman->dirY = 0;
            }
        } else if(button2) {
            if(!checkCollision(pacman->targetX, pacman->targetY + 1)) {
                pacman->dirX = 0;
                pacman->dirY = 1;
            }
        } else if(button3) {
            if(!checkCollision(pacman->targetX, pacman->targetY - 1)) {
                pacman->dirX = 0;
                pacman->dirY = -1;
            }
        } else if(button4) {
            if(!checkCollision(pacman->targetX - 1, pacman->targetY)) {
                pacman->dirX = -1;
                pacman->dirY = 0;
            }
        }
}