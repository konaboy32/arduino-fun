boolean cycleHigh = false;
int halfCycle = 0;
boolean beep = false;

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
	beep = !beep;
	delay(1000);
}

ISR(TIMER1_COMPA_vect) {
	if (beep) {
		if (halfCycle++ > 100) {
			if (cycleHigh) {
				OCR2B = 0;
			} else {
				OCR2B = 255;
			}
			cycleHigh = !cycleHigh;
			halfCycle = 0;
		}
	}
}



