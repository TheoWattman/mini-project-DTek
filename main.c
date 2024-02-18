#include <pic32mx.h>
#include ".globals.h"
#include <stdint.h>
#include <stdbool.h>
#include "data.h"
#include "Game.h"
#include "menus.h"

// Buttons, is 1 if theyre being pressed, 0 if not.

int main() {

	SPIInit();
	displayInit();

	TRISE &= ~0xFF;
	TRISF |= 0x2;

	mainMenu();
	
	return 0;
}
