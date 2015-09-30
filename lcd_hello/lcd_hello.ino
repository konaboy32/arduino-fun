#include "settings.h"

extern boolean pressed[BTNS];
int playerXpos = 40;

void setup(void) {
	lcdInitialise();
	lcdClear();
	buttonsInitialize();
	lcdCharXY(playerXpos, PLAYER_ROW, '#');
}

void loop(void) {
	buttonsUpdate();
	checkButtons();
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


