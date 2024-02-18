// #include <pic32mx.h>
// #include <stdint.h>
// #include <string.h>
// #include <stdbool.h>

// // Buttons, is 1 if theyre being pressed, 0 if not.
// #define button1 ((PORTF >> 1) & 0x1)	// 0001
// #define button2 ((PORTD >> 5) & 0x1)	// 0010
// #define button3 ((PORTD >> 6) & 0x1)	// 0100
// #define button4 ((PORTD >> 7) & 0x1)	// 1000

// #define GRIDSIZE 5
// #define GRIDWIDTH 25
// #define GRIDHEIGHT 19
// #define PIXEL_OFFSET_BOTTOM 65
// #define PIXEL_OFFSET_MIDDLE 15
// #define FRAMELENGTH 40

// void enterName(int score);

// void copyGrid() {
//     size_t i = 0;
//     for (i; i < sizeof(gridMap); i++){
//         foodGrid[i] = gridMap[i];
//     }
// }

// void clearFood(int gridX, int gridY, int *score) {
//     int pos = gridX + (gridY)*25;

//     if((foodGrid[2 + pos / 8] & (0x1 << (7 - pos % 8))) == 0){
//         *score += 50;
//     }
//     foodGrid[2 + pos / 8] |= (0x1 << (7 - pos % 8));
// }

// void displayLine(int x, int y, int len) {
//     // Displays Horizontal Line
// 	int i = x;
//     for (i; i < x + len; i++)
//     {
//         putPixel(i, y);
//     } 
// }

// void displayNotLine(int x, int y, int len) {
//     // Displays Horizontal Line
// 	int i = x;
//     for (i; i < x + len; i++)
//     {
//         putNotPixel(i, y);
//     } 
// }

// int getBtns() {
//     return (button4 << 3) | (button3 << 2) | (button2 << 1) | button1;
// }

// uint8_t checkCollision(int x, int y) {

//     if(x >= GRIDWIDTH || x < 0 || y >= GRIDHEIGHT || y < 0);

//     // Checks grid at given location, returns 0 if it is empty and 1 if it is a wall

//     int byte = (y * gridMap[0] + x) / 8;
//     int bit =  7 - (y * gridMap[0] + x) % 8;

//     return gridMap[byte + 2] & (0x1 << bit);
// }

// void displayPlayer(int x, int y, int dirX, int dirY) {

//     // Displays the correct sprite based on the direction of the player.

//     if(dirX == -1)
//         displayBitarray(x, y,left);
//     else if(dirX == 1)
//         displayBitarray(x, y,right);
//     else if(dirY == -1)
//         displayBitarray(x, y,up);
//     else if(dirY == 1)
//         displayBitarray(x, y,down);
//     else {
//         displayBitarray(x, y,defaultPac);
//     }
// }

// void displayScore(int score) {
    
//     //Display black box
//     int i = 0;
//     for(i; i<6; i++){
//         displayNotLine(0, i, 22);
//     }

//     //convert score to string
//     char str[10];
//     int tempNum = score;
//     i = 0;
//     while (tempNum != 0){ // find length of score
//         tempNum /= 10;
//         i++;
//     }
//     str[i] = '\0';
//     while (score) {
//         str[--i] = '0' + (score % 10);
//         score /= 10;
//     }

//     //display the score
//     displayString(1,0, str, font);
// }

// void updateGameDisplay(int pixelX, int pixelY, int dirX, int dirY) {
//     if(pixelY < 15) {      // If the player is in the top 3 grids, lock camera to top.
//         displayBitarray(1, 0, map);
//         displayPacFood(3,2, foodGrid);
//         displayPlayer(pixelX + 1,pixelY,dirX, dirY);
//     } else if(pixelY >= 80) { // If the player is in the bottom 3 grids, lock camera to bottom.
//         displayBitarray(1, - PIXEL_OFFSET_BOTTOM, map);
//         displayPacFood(3, - PIXEL_OFFSET_BOTTOM+2, foodGrid);
//         displayPlayer(pixelX + 1,pixelY - PIXEL_OFFSET_BOTTOM ,dirX, dirY);
//     } else {
//         displayBitarray(1, -pixelY + PIXEL_OFFSET_MIDDLE, map);
//         displayPacFood(3, -pixelY + PIXEL_OFFSET_MIDDLE+2, foodGrid);
//         displayPlayer(pixelX + 1, PIXEL_OFFSET_MIDDLE, dirX, dirY);
//     }
// }

// void handleInput(int gridX, int gridY, int *dirX, int *dirY) {
//         if(button1) {
//             if(!checkCollision(gridX + 1, gridY)) {
//                 *dirX = 1;
//                 *dirY = 0;
//             }
//         } else if(button2) {
//             if(!checkCollision(gridX, gridY + 1)) {
//                 *dirX = 0;
//                 *dirY = 1;
//             }
//         } else if(button3) {
//             if(!checkCollision(gridX, gridY - 1)) {
//                 *dirX = 0;
//                 *dirY = -1;
//             }
//         } else if(button4) {
//             if(!checkCollision(gridX - 1, gridY)) {
//                 *dirX = -1;
//                 *dirY = 0;
//             }
//         }
// }

// void updatePosition(int *pixelX, int *pixelY, int dirX, int dirY) {
//     *pixelX += dirX;
//     *pixelY += dirY;
// }

// void teleport(int *pixelX, int *pixelY, int *gridX, int *gridY, int targetX, int targetY) {
//     *gridX = targetX;
//     *gridY = targetY;

//     *pixelX = targetX * 5;
//     *pixelY = targetY * 5;
// }

// int programMain() {

//     int timer = 0;
//     int score = 0;

//     // copyGrid(); 

//     uint8_t menuOption = 0;

//     int pixelX = 25;
//     int pixelY = 25;

//     int gridX = 5;
//     int gridY = 5;

//     int dirX = 0;
//     int dirY = 0;

//     while(1) {
//         sleep(200000);

//         clearDisplay();

//         if(1) {            
//             if(pixelX == gridX * GRIDSIZE && pixelY == gridY * GRIDSIZE) { // If player is at target grid.
                
//                 timer++;

//                 clearFood(gridX, gridY, &score);

//                 handleInput(gridX, gridY, &dirX, &dirY);

//                 if(!checkCollision(gridX + dirX, gridY + dirY)) {
//                     gridX += dirX;
//                     gridY += dirY;
//                 } else {
//                     if(gridX == 24 && gridY == 9){
//                         teleport(&pixelX, &pixelY, &gridX, &gridY, 0, 9);
//                         continue;
//                     }
//                     else if(gridX == 0 && gridY == 9){
//                         teleport(&pixelX, &pixelY, &gridX, &gridY, 24, 9);
//                         continue;
//                     } else {
//                         dirX = 0;
//                         dirY = 0;
//                     }

//                 }
//             }

//             updatePosition(&pixelX, &pixelY, dirX, dirY);

//             updateGameDisplay(pixelX, pixelY, dirX, dirY);
//             displayScore(score);
//         }

//         updateDisplay();

//         // if (score >= 200) break;
//         if (timer >= 50) break;
//     }

//     enterName(score);
//     mainMenu();

//     return 0;
// }
