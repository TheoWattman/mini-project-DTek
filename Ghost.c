#include "Ghost.h"

extern uint8_t ghost_sprite[];
extern uint8_t ghost_flee[];
extern uint8_t ghost_dead[];

void initGhost(Ghost *ghost) {
    ghost->x = 60;
    ghost->y = 45;

    ghost->targetX = 12;
    ghost->targetY = 8;

    ghost->dirX = 0;
    ghost->dirY = -1;

    ghost->state = CHASE;
};

void findGhostPath(Ghost *ghost, int targetX, int targetY, uint8_t type) {

    int closestDist = MAX_INT;
    int furthestDist = 0;

    int deltaX = ghost->x - targetX;
    int deltaY = ghost->y - targetY;

    int bestDir = -1;

    int forbiddenDirX = -ghost->dirX;
    int forbiddenDirY = -ghost->dirY;

    static int dirs[4][2] = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};

    int i = 0;

    for (i; i < 4; i++)
    {
        int newX = ghost->x / GRIDSIZE + dirs[i][0];
        int newY = ghost->y / GRIDSIZE + dirs[i][1];

        if (!checkCollision(newX, newY) && (dirs[i][0] != forbiddenDirX || dirs[i][1] != forbiddenDirY)) {
                int dist = (deltaX + dirs[i][0]) * (deltaX + dirs[i][0]) + (deltaY + dirs[i][1]) * (deltaY + dirs[i][1]);
                if (dist < closestDist && type == CHASE) {
                    closestDist = dist;
                    bestDir = i;
                }

                if (dist > furthestDist && type == FLEE) {
                    furthestDist = dist;
                    bestDir = i;
                }

            }

    }

    if (bestDir != -1) {
        ghost->targetX = ghost->x / GRIDSIZE + dirs[bestDir][0];
        ghost->targetY = ghost->y / GRIDSIZE + dirs[bestDir][1];
        ghost->dirX = dirs[bestDir][0];
        ghost->dirY = dirs[bestDir][1];
    }
    
}

void displayGhost(Ghost *ghost, Pacman *pacman) {
    switch (ghost->state)
    {
    case CHASE:
        displayBitarray(ghost->x - pacman->cameraX, ghost->y - pacman->cameraY, ghost_sprite);
        break;
    case SCATTER:
        displayBitarray(ghost->x - pacman->cameraX, ghost->y - pacman->cameraY, ghost_sprite);
        break;
    case FLEE:
        displayBitarray(ghost->x - pacman->cameraX, ghost->y - pacman->cameraY, ghost_flee);
        break;
    case DEAD:
        displayBitarray(ghost->x - pacman->cameraX, ghost->y - pacman->cameraY, ghost_dead);
        break;
    }
}

void teleportGhost(Ghost *ghost, int targetX, int targetY) {
    ghost->targetX = targetX + ghost->dirX;
    ghost->targetY = targetY + ghost->dirY;

    ghost->x = targetX * GRIDSIZE;
    ghost->y = targetY * GRIDSIZE;
}

int handlePacmanGhostCollision(Ghost *ghost, Pacman *pacman) {
    if((ghost->x - pacman->x) * (ghost->x - pacman->x) + (ghost->y - pacman->y) * (ghost->y - pacman->y) < 20) {   
        if(ghost->state == SCATTER || ghost->state == CHASE) {
            // game over logic here

            return 1;
        } else if(ghost->state == FLEE) {
            ghost->state = DEAD;
        }
    }
    return 0;
}

void updateGhosts(Ghost *ghost, Pacman *pacman) {

    if(ghost->x == ghost->targetX * GRIDSIZE && ghost->y == ghost->targetY * GRIDSIZE) {
        switch (ghost->state)
        {
        case SCATTER:
            findGhostPath(ghost, ghost->scatterX, ghost->scatterY, CHASE); // Run to scatter grid
            break;
        
        case CHASE:
            findGhostPath(ghost, pacman->x, pacman->y, CHASE);   // Chase Pacman
            break;
        
        case FLEE:
            findGhostPath(ghost, pacman->x, pacman->y, FLEE);    // Flee from Pacman.
            break;

        case DEAD:
            findGhostPath(ghost, 12 * GRIDSIZE, 7 * GRIDSIZE, CHASE);    // Run back to ghost box.
            if(ghost->x == 12 * GRIDSIZE && ghost->y == 7 * GRIDSIZE)
                ghost->state = SCATTER;
            break;
        }
    }

    if(ghost->x == 120 && ghost->y == 45)   // if
        teleportGhost(ghost, 0,9);
    else if(ghost->x == 0 && ghost->y == 45)
        teleportGhost(ghost, 24,9);
    
    ghost->x += ghost->dirX;
    ghost->y += ghost->dirY;
}