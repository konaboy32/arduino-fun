#include "settings.h"

struct Drop {
	short x;
	short y;
};

extern boolean pressed[BTNS];
short playerXpos = 40;
long lastFrame = 0;
long now = 0;
short elapsed = 0;
char elapsedStr[4];
short frameCounter = 0;
short dropRenderInterval = DROP_INTERVAL;
struct Drop drop;

void setup(void) {
	lcdInitialise();
	lcdClear();
	soundInitialize();
	buttonsInitialize();
	lcdCharXY(playerXpos, PLAYER_ROW, '#');
	gameInitialize();
}

void loop(void) {
	fps();
	buttonsUpdate();
	drawDrops();
	drawPlayer();
}

void gameInitialize() {
  srand(millis());
	drop.x = 40;
	drop.y = 1;
	lastFrame = millis();
}

void fps() {
	now = millis();
	elapsed = now - lastFrame;
	lastFrame = now;
	itoa(elapsed, elapsedStr, 10);
	lcdStringXY(1, 1, elapsedStr);
}

void drawDrops() {
	if (frameCounter++ > dropRenderInterval) {
		lcdCharXY(drop.x, drop.y, ' ');
		if (drop.y < LCD_ROWS - 1) {
			drop.y++;
		} else {
			handleDropReachedBottom();
		}
		lcdCharXY(drop.x, drop.y, '*');
		frameCounter = 0;
	}
}

void handleDropReachedBottom() {
	drop.y = 1;
	drop.x = (rand() % 10) * PLAYER_WIDTH;
	dropRenderInterval--;
}

void drawPlayer() {
	if (pressed[BTN_A]) {
		handleRightInput();
		return;
	}
	if (pressed[BTN_LEFT] || pressed[BTN_UP] || pressed[BTN_DOWN] || pressed[BTN_RIGHT]) {
		handleLeftInput();
	}
}

void handleRightInput() {
	if (playerXpos < LCD_WIDTH - PLAYER_WIDTH - 4) {
		lcdCharXY(playerXpos, PLAYER_ROW, ' ');
		playerXpos += PLAYER_WIDTH;
		lcdCharXY(playerXpos, PLAYER_ROW, '#');
	}
}

void handleLeftInput() {
	if (playerXpos > 0) {
		lcdCharXY(playerXpos, PLAYER_ROW, ' ');
		playerXpos -= PLAYER_WIDTH;
		lcdCharXY(playerXpos, PLAYER_ROW, '#');
	}
}


