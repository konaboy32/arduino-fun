#define NOTE_C4 115
#define NOTE_D4 102
#define NOTE_E4 91
#define NOTE_F4 86
#define NOTE_G4 77
#define NOTE_A4 68
#define NOTE_B4 61
#define NOTE_C5 57

boolean playTone = false;
boolean cycleHigh = false;

long timerCounter = 0;
long halfCycleCounter = 0;

long totalHalfCycles = 0;
int tonePitch = 0;

void setup(void) {

	pinMode(3, OUTPUT);
	TCCR2B = (TCCR2B & B11111000) | 1; // set timer 2 prescaler to 1 -> 30kHz PWM on pin 3

	// initialize timer1 
	noInterrupts(); // disable all interrupts
	TCCR1A = 0; // set entire TCCR1A register to 0
	TCCR1B = 0; // set entire TCCR1B register to 0 (as we do not know the initial values)
	TCNT1 = 0;

	OCR1A = 280; // compare match register
	TCCR1B |= (1 << WGM12); // CTC mode
	TCCR1B |= (1 << CS10); // 1 prescaler
	TIMSK1 |= (1 << OCIE1A); // enable timer compare interrupt
	interrupts(); // enable all interrupts
}

void loop(void) {
	playBeepTone(NOTE_C4, 100);
	delay(1000);
	playBeepTone(NOTE_D4, 90);
	delay(1000);
	playBeepTone(NOTE_E4, 80);
	delay(1000);
	playBeepTone(NOTE_F4, 70);
	delay(1000);
	playBeepTone(NOTE_G4, 60);
	delay(1000);
	playBeepTone(NOTE_A4, 50);
	delay(1000);
	playBeepTone(NOTE_B4, 40);
	delay(1000);
	playBeepTone(NOTE_C5, 30);
	delay(1000);
	playBeepTone(NOTE_B4, 20);
	delay(1000);
	playBeepTone(NOTE_A4, 10);
	delay(1000);
	playBeepTone(NOTE_G4, 5);
	delay(1000);
	playBeepTone(NOTE_F4, 4);
	delay(1000);
	playBeepTone(NOTE_E4, 3);
	delay(1000);
	playBeepTone(NOTE_D4, 2);
	delay(1000);
	playBeepTone(NOTE_C4, 1);
	delay(1000);
}

void playBeepTone(int pitch, int halfCycles) {
	timerCounter = 0;
	playTone = true;
	tonePitch = pitch;
	totalHalfCycles = halfCycles;
}

ISR(TIMER1_COMPA_vect) {
	if (playTone) {
	
		//toggle output after n timer interrupts to create square wave
		if (timerCounter++ > tonePitch) {
			if (cycleHigh) {
				OCR2B = 0;
			} else {
				OCR2B = 255;
			}
			cycleHigh = !cycleHigh;
			timerCounter = 0;
			halfCycleCounter++;
		}
		
		//switch output off if duration exceeded
		if (halfCycleCounter > totalHalfCycles) {
			playTone = false;
			halfCycleCounter = 0;
			OCR2B = 0;
		}
	}
}



