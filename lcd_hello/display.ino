extern const byte ASCII[][5];

void lcdClear(void) {
	for (int index = 0; index < LCD_WIDTH * LCD_HEIGHT / 8; index++) {
		lcdWriteData(0x00);
	}
}

void lcdInitialise(void) {
	pinMode(PIN_SCE, OUTPUT);
	pinMode(PIN_RESET, OUTPUT);
	pinMode(PIN_DC, OUTPUT);
	pinMode(PIN_SDIN, OUTPUT);
	pinMode(PIN_SCLK, OUTPUT);
	digitalWrite(PIN_RESET, LOW);
	digitalWrite(PIN_RESET, HIGH);
	lcdWriteCommand(0x21);  // LCD Extended Commands.
	lcdWriteCommand(0xB1);  // Set LCD Vop (Contrast). 
	lcdWriteCommand(0x04);  // Set Temp coefficent. //0x04
	lcdWriteCommand(0x14);  // LCD bias mode 1:48. //0x13
	lcdWriteCommand(0x20);  // LCD Basic Commands
	lcdWriteCommand(0x0C);  // LCD in normal mode.
}

void lcdCharacter(char character) {
	lcdWriteData(0x00);
	for (int index = 0; index < 5; index++) {
		lcdWriteData(ASCII[character - 0x20][index]);
	}
	lcdWriteData(0x00);
}

void lcdString(const char *characters) {
	while (*characters) {
		lcdCharacter(*characters++);
	}
}

void lcdStringXY(int x, int y, const char *characters) {
	lcdGotoXY(x, y);
	lcdString(characters);
}

void lcdGotoXY(int x, int y) {
	lcdWriteCommand(0x80 | x);
	lcdWriteCommand(0x40 | y);
}

void lcdCharXY(int x, int y, char character) {
	lcdGotoXY(x, y);
	lcdCharacter(character);
}

void lcdWriteCommand(byte data) {
	lcdWrite(LCD_COMMAND, data);
}

void lcdWriteData(byte data) {
	lcdWrite(LCD_DATA, data);
}

void lcdWrite(byte dc, byte data) {
	digitalWrite(PIN_DC, dc);
	digitalWrite(PIN_SCE, LOW);
	shiftOut(PIN_SDIN, PIN_SCLK, MSBFIRST, data);
	digitalWrite(PIN_SCE, HIGH);
}
