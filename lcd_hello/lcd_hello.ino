	unsigned long lastTime = 0;
char buffer[4]; 

void setup(void) {
	lcdInitialise();
	lcdClear();
	lcdString("Hello Mum!");
}

void loop(void) {
	delay(500);
	unsigned long now = millis();
	unsigned long elapsed = now - lastTime;
	lastTime = now;
	lcdCharacter(' ');
	lcdString(ltoa(elapsed, buffer, 10));
}

