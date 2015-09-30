int pin[BTNS];             // store the pin number
int counter[BTNS];         // how many times we have seen new value
int state[BTNS];           // the debounced input value
boolean pressed[BTNS];     // momentarily set to true when key is pressed

void buttonsInitialize() {

	pin[0] = BTN_UP_PIN;
	pin[1] = BTN_RIGHT_PIN;
	pin[2] = BTN_DOWN_PIN;
	pin[3] = BTN_LEFT_PIN;
	pin[4] = BTN_A_PIN;
	
	for (int i = 0; i < BTNS; i++) {
		counter[i] = 0;
		state[i] = HIGH;
	}
}

void buttonsUpdate() {
	for (int i = 0; i < BTNS; i++) {
		buttonUpdate(i);
	}
}

void buttonUpdate(int i) {
	pressed[i] = false;
	int reading = digitalRead(pin[i]);

	if (reading == state[i] && counter[i] > 0) counter[i]--;
	if (reading != state[i]) counter[i]++; 

	// If the Input has shown the same value for long enough let's switch it
	if(counter[i] > DEBOUNCE_COUNT) {
		counter[i] = 0;
		if (state[i] == HIGH && reading == LOW) {
			pressed[i] = true;
		}
		state[i] = reading;
	}
}