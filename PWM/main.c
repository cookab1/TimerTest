/*
 * TimerTest.c
 *
 * Created: 2/28/2018 8:13:03 PM
 * Author : andyr
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

#define LED 0x80

void setup();

int main(void)
{
	DDRB = LED;
	PORTB= 0x00;
	setup();
	
    /* Replace with your application code */
    while (1) 
    {
    }
}
void setup()
{
	PORTB |= LED;
    // initialize Timer1
    cli();         // disable global interrupts
    TCCR1A = 0;    // set TCCR1A register to 0
    TCCR1B = 0;    // set TCCR1B register to 0 

	// turn on CTC mode:
	TCCR1B |= (1 << WGM12);
	
    // Set CS12 bit so timer runs at clock speed: (pre-scale of 256)
    TCCR1B |= (1 << CS12); // Sets bit CS12 in TCCR1B
	
    // set compare match register to desired timer count:
    OCR1A = 0x124F;
        
	// enable timer compare interrupt:
	TIMSK1 |= (1 << OCIE1A);
	
    // enable global interrupts:
    sei();
}

ISR(TIMER1_COMPA_vect)
{
    if((PORTB & LED) == 0) {
		//PORTB |= LED;
		// This is the compare/match value when the LED is on
		OCR1A = 0x124F; // reload the timer pre-load
	} else {
		PORTB &= ~LED;
		// This is the compare/match value when the LED is off
		OCR1A = 0x3F12; // reload the timer pre-load
	}
	// or use: PORTB ^= _BV(PB5);// PB5 =pin 19 is digitalpin 13
}
