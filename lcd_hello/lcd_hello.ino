extern boolean pressed[7];

const int BTN_LEFT = 0;
const int BTN_UP = 1;
const int BTN_RIGHT = 2;
const int BTN_DOWN = 3;
const int BTN_A = 4;
const int BTN_B = 5;
const int BTN_C = 6;

void setup(void) {
	lcdInitialise();
	lcdClear();
	buttonsInitialize();
}

void loop(void) {
	buttonsUpdate();
	checkButtonPressed();

}

void checkButtonPressed() {
	for (int i = 0; i < 7; i++) {
		if (pressed[i]) {
			lcdCharacter(i + 48);
		}
	}
}

