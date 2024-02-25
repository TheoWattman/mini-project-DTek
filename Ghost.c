#include "Ghost.h"

extern uint8_t ghost_sprite[];
extern uint8_t ghost_flee[];
extern uint8_t ghost_dead[];

int blinky_x = 0;
int blinky_y = 0;

void initGhost(Ghost *ghost, int type) {
    ghost->x = 12 * GRIDSIZE;
    ghost->y = 7 * GRIDSIZE;

    ghost->targetX = 12;
    ghost->targetY = 7;

    ghost->dirX = 0;
    ghost->dirY = -1;

    ghost->counter = 0;

    switch (type)
    {
    case BLINKY:
        ghost->scatterX = 23 * GRIDSIZE;
        ghost->scatterY = 1 * GRIDSIZE;
        break;
    case INKY:
        ghost->scatterX = 23 * GRIDSIZE;
        ghost->scatterY = 17 * GRIDSIZE;
        break;
    case PINKY:
        ghost->scatterX = 1 * GRIDSIZE;
        ghost->scatterY = 1 * GRIDSIZE;
        break;
    case CLYDE:
        ghost->scatterX = 1 * GRIDSIZE;
        ghost->scatterY = 17 * GRIDSIZE;
        break;
    }

    changeGhostState(ghost, SCATTER);

    ghost->ghost_type = type;
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

void displayGhosts(Ghost *ghost, Pacman *pacman) {
    int i = 0;
    for (i; i < GHOST_AMOUNT; i++)
    {
        switch (ghost[i].state)
        {
        case CHASE:
            displayBitarray(ghost[i].x - pacman->cameraX, ghost[i].y - pacman->cameraY, ghost_sprite);
            break;
        case SCATTER:
            displayBitarray(ghost[i].x - pacman->cameraX, ghost[i].y - pacman->cameraY, ghost_sprite);
            break;
        case FLEE:
            displayBitarray(ghost[i].x - pacman->cameraX, ghost[i].y - pacman->cameraY, ghost_flee);
            break;
        case DEAD:
            displayBitarray(ghost[i].x - pacman->cameraX, ghost[i].y - pacman->cameraY, ghost_dead);
            break;
        }
    }
}

void teleportGhost(Ghost *ghost, int targetX, int targetY) {
    ghost->targetX = targetX + ghost->dirX;
    ghost->targetY = targetY + ghost->dirY;

    ghost->x = targetX * GRIDSIZE;
    ghost->y = targetY * GRIDSIZE;
}

int handlePacmanGhostCollision(Ghost *ghost, Pacman *pacman, int *score) {
    int i = 0;
    for (i; i < GHOST_AMOUNT; i++)
    {
        if((ghost[i].x - pacman->x) * (ghost[i].x - pacman->x) + (ghost[i].y - pacman->y) * (ghost[i].y - pacman->y) < 20) {
            if(ghost[i].state == SCATTER || ghost[i].state == CHASE) {
                return 1;
            } else if(ghost[i].state == FLEE) {
                changeGhostState(&ghost[i], DEAD);
                *score += 200;
            }
        }
    }
    return 0;
}


void updateGhosts(Ghost *ghost, Pacman *pacman) {
    int i = 0;
    for (i; i < GHOST_AMOUNT; i++)
    {
        if(ghost[i].x == ghost[i].targetX * GRIDSIZE && ghost[i].y == ghost[i].targetY * GRIDSIZE) {
            switch (ghost[i].state)
            {
            case SCATTER:
                findGhostPath(&ghost[i], ghost[i].scatterX, ghost[i].scatterY, CHASE); // Run to scatter grid
                break;
            
            case CHASE:
                ChasePacman(&ghost[i], pacman);
                break;
            
            case FLEE:
                findGhostPath(&ghost[i], pacman->x, pacman->y, FLEE);    // Flee from Pacman.
                break;

            case DEAD:
                findGhostPath(&ghost[i], 12 * GRIDSIZE, 7 * GRIDSIZE, CHASE);    // Run back to ghost box.
                if(ghost[i].x == 12 * GRIDSIZE && ghost[i].y == 7 * GRIDSIZE)
                    changeGhostState(&ghost[i], SCATTER);
                break;
            }
        }

        if(ghost[i].x == 120 && ghost[i].y == 45)   // if
            teleportGhost(&ghost[i], 0,9);
        else if(ghost[i].x == 0 && ghost[i].y == 45)
            teleportGhost(&ghost[i], 24,9);
        
        ghost[i].x += ghost[i].dirX;
        ghost[i].y += ghost[i].dirY;

        switch (ghost[i].state)
        {
        case CHASE:
            if(ghost[i].counter > CHASE_COUNTER)
                changeGhostState(&ghost[i], SCATTER);
            break;
        case SCATTER:
            if(ghost[i].counter > SCATTER_COUNTER)
                changeGhostState(&ghost[i], CHASE);
            break;
        case FLEE:
            if(ghost[i].counter > FLEE_COUNTER)
                changeGhostState(&ghost[i], SCATTER);
            break;
        }
        ghost[i].counter++;
    }
}

void ChasePacman(Ghost *ghost, Pacman *pacman) {

    int vx;
    int vy;

    switch (ghost->ghost_type)
    {
    case BLINKY:
        blinky_x = ghost->x;
        blinky_y = ghost->y;
        findGhostPath(ghost, pacman->x, pacman->y, CHASE);   // Chase Pacman directly
        break;
    case INKY:
        vx = 2 * (pacman->x + pacman->dirX * 5) - blinky_x;
        vy = 2 * (pacman->y + pacman->dirY * 5) - blinky_y;

        vx = vx > 23 * GRIDSIZE ? 23 * GRIDSIZE : vx;
        vy = vy > 23 * GRIDSIZE ? 23 * GRIDSIZE : vy;

        vx = vx < 0 ? 0 : vx;
        vy = vy < 0 ? 0 : vy;

        findGhostPath(ghost, vx, vy, CHASE);
        break;
    case PINKY:
        findGhostPath(ghost, pacman->x + pacman->dirX * 15, pacman->y + pacman->dirY * 15, CHASE);  // Chase 2 tiles in front of pacman
        break;
    case CLYDE:
        if((ghost->x - pacman->x) * (ghost->x - pacman->x) + (ghost->y - pacman->y) * (ghost->y - pacman->y) < 1600) {
            findGhostPath(ghost, ghost->scatterX, ghost->scatterY, CHASE);
        } else {
            findGhostPath(ghost, pacman->x, pacman->y, CHASE);
        }
        break;
    }
}

void changeGhostState(Ghost *ghost, int state) {
    ghost->state = state;
    ghost->counter = 0;
}