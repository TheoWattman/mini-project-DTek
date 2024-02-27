#include "display.h"

#define DISPLAY_SIZE_X 128
#define DISPLAY_SIZE_Y 4
#define DISPLAY_SIZE 512

#define SET_COMMAND_MODE (PORTFCLR = 0x10)  // Set command mode, from the chipkit ref manual, it clears the bit at index 4 of PORTF
#define SET_DATA_MODE (PORTFSET = 0x10)

#define switch1 ((PORTD >> 8) & 0x1)

uint8_t displayBuffer[DISPLAY_SIZE];


extern uint8_t font[];

uint8_t spi_put_byte(uint8_t bVal) {

	while ((SPI2STAT & PIC32_SPISTAT_SPITBE) == 0);

    SPI2BUF = bVal;

	while ((SPI2STAT & PIC32_SPISTAT_SPITBE) == 0);

    return SPI2BUF;

}

void putPixel(uint8_t x, uint8_t y) {

    int row = y / 8;

    displayBuffer[x + DISPLAY_SIZE_X * row] |= (0x1 << (y % 8));
}

void putNotPixel(uint8_t x, uint8_t y) {

    int row = y / 8;

    displayBuffer[x + DISPLAY_SIZE_X * row] &= (~(0x1 << (y % 8)));
}

void displayChar(const uint8_t x, const uint8_t y, char character, const uint8_t *font) {

    if(character >= 48 && character <= 57) {
        character -= 22;
    } else if(character >= 97 && character <= 122 ) {
        character -= 97;
    } else if(character >= 65 && character <= 90 ) {
        character -= 65;
    }

    int i, j;
    int w = font[0];

    int n = character * w * w;

    for (i = 0; i < w; i++) {
        for (j = 0; j < w; j++) {
            if((font[2 + n / 8] & (0x1 << (7 - n % 8))) != 0)
                putPixel(x + j, y + i); 
            
            n += 1;
        }
    }   

}

void displayString(const uint8_t x, const uint8_t y, char *character, const uint8_t *font) {
    int i = 0;
    while(character[i] != 0) {

        displayChar(x + i * font[0], y, character[i], font);

        i++;
    }
}

void sleep(int cyc) {
    int i;
    for (i = cyc; i > 0; i--);
}

void displayBitarray(const uint8_t x, const uint8_t y, const uint8_t *byteArray) {

    int i, j;
    int w = byteArray[0];
    int h = byteArray[1];

    int n = 0;

    for (i = 0; i < h; i++) {
        for (j = 0; j < w; j++) {
            if((byteArray[2 + n / 8] & (0x1 << (7 - n % 8))) != 0)
                putPixel(x + j, y + i); 
            
            n += 1;
        }
    }

}

void clearDisplay(void) {
    int i;
    for (i = 0; i < DISPLAY_SIZE; i++)
    {
        displayBuffer[i] = 0;
    }
}

void displayRow(uint8_t byteAmount, uint8_t * buffer) {

    int j;
    for (j = 0; j < byteAmount; j++)
    {

        uint8_t bTmp;

        //  Wait for transmitter to be ready
        while ((SPI2STAT & PIC32_SPISTAT_SPITBE) == 0);

        // Write the next transmit byte.
        if(switch1) {
            SPI2BUF = ~*buffer++;
        } else {
            SPI2BUF = *buffer++;
        }
        

        // Wait for receive byte.
        while ((SPI2STAT & PIC32_SPISTAT_SPITBE) == 0);

        bTmp = SPI2BUF;
        
    }

}

void displayPacFood(const uint8_t x, const uint8_t y, const uint8_t *gridArray) {

    int i, j;
    int w = gridArray[0];
    int h = gridArray[1];

    int n = 0;

    for (i = 0; i < h; i++) {
        for (j = 0; j < w; j++) {
            if((gridArray[2 + n / 8] & (0x1 << (7 - n % 8))) == 0)
                putPixel(x + j*5, y + i*5); 
            n += 1;
        }
    }
}

void displayLine(int x, int y, int len) {
    // Displays Horizontal Line
	int i = x;
    for (i; i < x + len; i++)
    {
        putPixel(i, y);
    } 
}

void displayNotLine(int x, int y, int len) {
    // Displays Horizontal Line
	int i = x;
    for (i; i < x + len; i++)
    {
        putNotPixel(i, y);
    } 
}

void displayRect(int x, int y, int width, int height) {
  	int i = y;
    for (i; i < y + height; i++)
    {
        displayLine(x, i, width);
    }  
}

void clearRect(int x, int y, int width, int height) {
  	int i = y;
    for (i; i < y + height; i++)
    {
        displayNotLine(x, i, width);
    }  
}

void numToString(int score, char* str) {
    int tempNum = score;
    int i = 0;
    while (tempNum != 0){ // find length of score
        tempNum /= 10;
        i++;
    }
    str[i] = '\0';
    while (score) {
        str[--i] = '0' + (score % 10);
        score /= 10;
    }
}

void displayScore(int score) {
    
    //Display black box
    int i = 0;
    for(i; i<6; i++){
        displayNotLine(0, i, 22);
    }

    //convert score to string
    char str[10];
    numToString(score, str);

    //display the score
    displayString(1,0, str, font);
}

void updateDisplay() {
    int i;
    
    uint8_t * buffer;
    buffer = displayBuffer;

    for (i = 0; i < DISPLAY_SIZE_Y; i++)
    {
        SET_COMMAND_MODE;
        spi_put_byte(0x22);
        spi_put_byte(i);

        spi_put_byte(0x00);
        spi_put_byte(0x10);

        SET_DATA_MODE;

        // Display the current row
        displayRow(DISPLAY_SIZE_X, buffer);
        buffer += DISPLAY_SIZE_X;

    }
    
}

// from the chipkit ref manual
void displayInit(void) {

    SET_COMMAND_MODE;
    sleep(10);
    PORTFCLR = 0x40;            // Turn on VDD
    sleep(1000000);
    spi_put_byte(0xAE);
    PORTGCLR = 0x200;           // Bring reset low
    sleep(10);
    PORTGSET = 0x200;           // Bring reset high
    sleep(10);

    spi_put_byte(0x8D);
    spi_put_byte(0x14);

    spi_put_byte(0xD9);
    spi_put_byte(0xF1);

    PORTFCLR = 0x20;            // Turn on VCC
    sleep(10000000);


    // Invert the display so that the origin is in the upper left corner
    spi_put_byte(0xA1);
    spi_put_byte(0xC8);


    spi_put_byte(0xDA);
    spi_put_byte(0x20);

    // Send Display On command
    spi_put_byte(0xAF);
}

// From github at https://github.com/is1200-example-projects/hello-display/blob/master/main.c#L271
void SPIInit(void) {
    // Set up the bus clock
	OSCCON &= ~0x180000;
	OSCCON |= 0x080000;

    // Setup the output pins
	AD1PCFG = 0xFFFF;
	ODCE = 0x0;
	TRISECLR = 0xFF;
	PORTE = 0x0;

    // Output pins for the display signals
	PORTF = 0xFFFF;
	PORTG = (1 << 9);
	ODCF = 0x0;
	ODCG = 0x0;
	TRISFCLR = 0x70;
	TRISGCLR = 0x200;

    // Set up the input pins
	TRISDSET = (1 << 8);
	TRISFSET = (1 << 1);

    // Clear the spirov bit
    SPI2STATCLR &= ~0x40;

	/* Set CKP = 1, MSTEN = 1; */
    SPI2CON |= 0x60;
	
	/* Turn on SPI */
	SPI2CONSET = 0x8000;
}