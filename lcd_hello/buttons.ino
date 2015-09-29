#define BTN_UP      0
#define BTN_RIGHT   1
#define BTN_DOWN    2
#define BTN_LEFT    3
#define BTN_A       4
#define BTN_B       5
#define BTN_C       6

#define BTN_UP_PIN      9
#define BTN_RIGHT_PIN   7
#define BTN_DOWN_PIN    6
#define BTN_LEFT_PIN    8
#define BTN_A_PIN       4
#define BTN_B_PIN       2
#define BTN_C_PIN       A3

const int DEBOUNCE_COUNT = 5; // number of millis/samples to consider before declaring a debounced input

int pin[7];             // store the pin number
int counter[7];         // how many times we have seen new value
int state[7];           // the debounced input value
boolean pressed[7];     // momentarily set to true when key is pressed

void buttonsInitialize() {

	pin[0] = BTN_UP_PIN;
	pin[1] = BTN_RIGHT_PIN;
	pin[2] = BTN_DOWN_PIN;
	pin[3] = BTN_LEFT_PIN;
	pin[4] = BTN_A_PIN;
	pin[5] = BTN_B_PIN;
	pin[6] = BTN_C_PIN;
	
	for (int i = 0; i < 7; i++) {
		counter[i] = 0;
		state[i] = HIGH;
	}
}

void buttonsUpdate() {
	for (int i = 0; i < 7; i++) {
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