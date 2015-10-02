#include "settings.h"

extern boolean pressed[BTNS];
int playerXpos = 40;
long lastFrame = 0;
long now = 0;
int frameRate = 0;
char frameRateStr[4];

void setup(void) {
	lcdInitialise();
	lcdClear();
	buttonsInitialize();
	lcdCharXY(playerXpos, PLAYER_ROW, '#');
}

void loop(void) {
	fps();
	buttonsUpdate();
	checkButtons();
}

void fps() {
  now = millis();
	frameRate = 1000 / (now - lastFrame);
	lastFrame = now;
	itoa(frameRate, frameRateStr, 10);
	lcdStringXY(1, 1, frameRateStr);
}


void checkButtons() {
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


