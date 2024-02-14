#include <pic32mx.h>
#include <stdint.h>

#include "data.h"

// Buttons, is 1 if theyre being pressed, 0 if not.
#define button1 ((PORTF >> 1) & 0x1)	// 0001
#define button2 ((PORTD >> 5) & 0x1)	// 0010
#define button3 ((PORTD >> 6) & 0x1)	// 0100
#define button4 ((PORTD >> 7) & 0x1)	// 1000

int main() {

	SPIInit();
	displayInit();

	TRISE &= ~0xFF;
	TRISF |= 0x2;

	while(1) {
		sleep(100000);

		clearDisplay();
	
		displayBitarray(0,0, example);

		updateDisplay();
	}
	return 0;
}

//isacs coola kommentar från sin branch
