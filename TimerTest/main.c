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

    TIMSK1 |= (1 << TOIE1); // enable Timer1 overflow interrupt:

    // Set CS12 bit so timer runs at clock speed: (pre-scaling of 256)
    TCCR1B |= (1 << CS12); // Sets bit CS12 in TCCR1B
    
    // This is the start value at which I want to start when the LED is off
    TCNT1 = 0xEDB0;  //0xD8AB is the hex value at which I want to start when the LED is on
        

    // enable global interrupts:
    sei();
}

ISR(TIMER1_OVF_vect)
{
    if((PORTB & LED) == 0) {
		PORTB |= LED;
		//0xD8AB is the hex value at which I want to start when the LED is on
		TCNT1 = 0xEDAF; // reload the timer pre-load
	} else {
		PORTB &= ~LED;
		// This is the start value at which I want to start when the LED is off
		TCNT1 = 0xC0EC; // reload the timer pre-load
	}
	// or use: PORTB ^= _BV(PB5);// PB5 =pin 19 is digitalpin 13
}
