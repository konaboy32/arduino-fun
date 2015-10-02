#include "settings.h"

extern boolean pressed[BTNS];
short playerXpos = 40;
long lastFrame = 0;
long now = 0;
short elapsed = 0;
char elapsedStr[4];
short frameCount;
short dropRenderInterval = DROP_INTERVAL;

struct Drop {
	short x;
	short y;
};

struct Drop drop;

void setup(void) {
	gameInitialize();
	lcdInitialise();
	lcdClear();
	buttonsInitialize();
	lcdCharXY(playerXpos, PLAYER_ROW, '#');
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
}

void fps() {
	now = millis();
	elapsed = now - lastFrame;
	lastFrame = now;
	itoa(elapsed, elapsedStr, 10);
	lcdStringXY(1, 1, elapsedStr);
}

void drawDrops() {
	if (frameCount++ > dropRenderInterval) {
		lcdCharXY(drop.x, drop.y, ' ');
		if (drop.y < LCD_ROWS - 1) {
			drop.y++;
		} else {
			drop.y = 1;
			drop.x = (rand() % 10) * PLAYER_WIDTH;
			dropRenderInterval--;
		}
		lcdCharXY(drop.x, drop.y, '*');
		frameCount = 0;
	}
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
		playerXpos = playerXpos + PLAYER_WIDTH;
		lcdCharXY(playerXpos, PLAYER_ROW, '#');
	}
}

void handleLeftInput() {
	if (playerXpos > 0) {
		lcdCharXY(playerXpos, PLAYER_ROW, ' ');
		playerXpos = playerXpos - PLAYER_WIDTH;
		lcdCharXY(playerXpos, PLAYER_ROW, '#');
	}
}


