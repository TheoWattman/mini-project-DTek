#include "menus.h"

extern int highscores[];
extern char initialList[];
extern uint8_t font[];
extern uint8_t controlBackground[];

int menuOption = 0;
int prevButtonStates = 0;

void storeHighScore(char* initials, int score) {

    int i = 0;
    for(i; i < 4; i++) {
        if(score > highscores[i]) {
            int j = 3;
            for(j; j > i; j--) {
                highscores[j] = highscores[j-1];
            }
            highscores[i] = score;
            initialList[i*2] = initials[0];
            initialList[i*2 + 1] = initials[1];
            break;
        }
    }
}

void menuScreenDisplay(int frame) {

    clearDisplay();
    displayString(10,5, "Play", font);
    displayString(10,13, "Scores", font);
    displayString(10,21, "Controls", font);

    displayLine(10, menuOption * 8 + 11, 40);

    menuAnimation(frame);

    updateDisplay();

}

void scoreDisplay() {

	clearDisplay();

    displayString(10,5, "Scores", font);
    displayLine(41,6,1);
    displayLine(41,9,1);
    displayString(10,21, "Return", font);
    displayLine(10, 2 * 8 + 11, 30);

    displayChar(48, 2, '1', font);
    displayChar(48, 9, '2', font);
    displayChar(48, 16, '3', font);
    displayChar(48, 23, '4', font);

    displayLine(54,3,1);
    displayLine(54,6,1);
    displayLine(54,10,1);
    displayLine(54,13,1);
    displayLine(54,17,1);
    displayLine(54,20,1);
    displayLine(54,24,1);
    displayLine(54,27,1);

    displayLine(54,8,40);
    displayLine(54,15,40);
    displayLine(54,22,40);
    displayLine(54,29,40);

    int i = 0;
    for(i; i < 4; i++) {
        if(highscores[i] == 47) {
            displayString(64, 2 + i*7, "Empty", font);
        }
        else {
            displayChar(64, 2 + i*7, initialList[i*2], font);
            displayChar(69, 2 + i*7, initialList[i*2 + 1], font);
            char str[10];
            numToString(highscores[i], str);
            displayString(78, 2 + i*7, str, font);
        }
    }

    updateDisplay();
}

void controlDisplay() {

	clearDisplay();

    displayString(15,13, "O", font);
    displayString(45,13, "O", font);
    displayString(75,13, "O", font);
    displayString(105,13, "O", font);
    displayString(10,5, "left", font);
    displayString(40,5, "up", font);
    displayString(70,5, "down", font);
    displayString(100,5, "right", font);
    displayString(10,21, "Return", font);
    displayLine(10, 2 * 8 + 11, 40);

    updateDisplay();
}

void enterNameDisplay(char *initials, int pos) {

    clearDisplay();

    displayString(10,10, "Enter", font);
    displayString(39,10, "Name", font);
    displayLine(70,16, 7);
    displayLine(77,16, 7);
    displayString(2,22, "ABCDEFGHIJKLMNOPQRSTUVWXY", font);
    displayLine(2 + 5*pos,28,5);

    if(initials[0] != 0){
        displayChar(71,10, initials[0], font);
    }
    if(initials[1] != 0){
        displayChar(78,10, initials[1], font);
    }

    updateDisplay();

}

void scores() {
    // the high-score screen
	scoreDisplay();
    // sleep(20000);

    while(getBtns()){sleep(1000);}

	while(1) {
        while(!getBtns()){sleep(1000);}
		if (button3) {
			mainMenu();
		}
        while(getBtns()){sleep(1000);}
	}
}

void controls() {
    // the controls screen
	// controlDisplay();
    clearDisplay();
    displayBitarray(0,0, controlBackground);
    updateDisplay();

    while(getBtns()){sleep(1000);}

	while(1) {
        while(!getBtns()){sleep(1000);}
		if (button3) {
			mainMenu();
		}
        while(getBtns()){sleep(1000);}
	}
}

void mainMenu() 
{
    menuOption = 0;

    int menuAnimationFrame = 0;

    sleep(1000000);

	menuScreenDisplay(menuAnimationFrame);

    while(getBtns()){}

    // if button 1 pushed: pos++, if button 2 pressed: break
    while(1){
        while(!getBtns()){
                menuScreenDisplay(menuAnimationFrame++);
        }
        if (button4) {
                menuOption = (menuOption + 1) % 3;
                menuScreenDisplay(menuAnimationFrame++);
        }
        else if (button3) {
			break;
		}
        while(getBtns()){
                menuScreenDisplay(menuAnimationFrame++);
        }
    }

    if((menuOption % 3) == 0) {
        // enter game
        int score = 0;
        game(&score);
        enterName(score);
    }
    if((menuOption % 3) == 1) {
        // enter scores
        scores();
    }
    if((menuOption % 3) == 2) {
        // enter controls
        controls();
    }
}

void enterName(int score) {
    
    int i = 0;
    int pos = 0;
    char initials[2] = {'\0', '\0'};
    enterNameDisplay(initials, pos);

    while(getBtns()){sleep(1000);} // wait until buttons are released

    while(initials[1] == 0) {

        while (!getBtns()) {sleep(1000);}

        if (button4 && pos > 0) pos--;
        else if(button3 && pos < 24) pos++;
        else if(button2){
            initials[i] = 'A' + pos;
            i++;
        }

        enterNameDisplay(initials, pos);

        while(getBtns()) {sleep(1000);}

    }

    storeHighScore(initials, score);

    sleep(1500000);

}

extern uint8_t menuAnim0[];
extern uint8_t menuAnim1[];
extern uint8_t menuAnim2[];
extern uint8_t menuAnim3[];

void menuAnimation(int frame) {

    displayRect(124 - (frame / 6) % 55, 14, 4, 4);

    displayRect(124 - (27 + frame / 6) % 55, 14, 4, 4);

    switch((frame / 25) % 6) {
        case 0:
            displayBitarray(70, 6, menuAnim0);
            break;
        case 1:
            displayBitarray(70, 6, menuAnim1);
            break;
        case 2:
            displayBitarray(70, 6, menuAnim2);
            break;
        case 3:
            displayBitarray(70, 6, menuAnim3);
            break;
        case 4:
            displayBitarray(70, 6, menuAnim2);
            break;
        case 5:
            displayBitarray(70, 6, menuAnim1);
            break;
    }
    updateDisplay();
};