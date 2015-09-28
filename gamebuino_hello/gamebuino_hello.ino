#include <SPI.h>
#include <Gamebuino.h>

extern const byte font3x3[];
extern const byte font3x5[];
extern const byte font5x7[];
Gamebuino gb;

void setup() {
	gb.begin();
}

byte pos = 0;

void loop() {
	if (gb.update()) {
		gb.display.drawRect(0, 0, LCDWIDTH, LCDHEIGHT);
		
		gb.display.cursorX = 4;
		gb.display.cursorY = 4;
		gb.display.fontSize = 1;
		gb.display.setFont(font3x5);
		gb.display.println("Hello Dear!");
		
		gb.display.cursorX = 4;
		gb.display.setFont(font5x7);
		gb.display.println("Frames:");
		
		int count = gb.frameCount;
		gb.display.cursorX = 4;
		gb.display.fontSize = 2;
		gb.display.println(count);
		
		gb.display.drawChar(pos, 32, '*', 1);
		gb.display.drawPixel(pos, 40);
		
		if( (count / 8) % 2) {
			gb.display.cursorX = 4;
			gb.display.fontSize = 1;
			gb.display.setFont(font3x3);
			gb.display.println("BLINKY star hello");
		}
		
		if (pos < LCDWIDTH) {
			pos++;
		} else {
			pos = 0;
		}
	}
}
