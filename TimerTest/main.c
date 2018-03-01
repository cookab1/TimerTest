/*
 * TimerTest.c
 *
 * Created: 2/28/2018 8:13:03 PM
 * Author : andyr
 */ 

#include <avr/io.h>

#

int main(void)
{
    /* Replace with your application code */
    while (1) 
    {
        
    }
}
void setup()
{
    pinMode(LEDPIN, OUTPUT);
    // initialize Timer1
    cli();         // disable global interrupts
    TCCR1A = 0;    // set TCCR1A register to 0
    TCCR1B = 0;    // set TCCR1B register to 0 

    // enable Timer1 overflow interrupt:
    TIMSK1 | = (1 << TOIE1);

    // Set CS10 bit so timer runs at clock speed: (prescale of 256)
    TCCR1B |= (1 << CS12); // Sets bit CS12 in TCCR1B
    
    // This is the start value so that it counts for the exact off time
    TCNT1 = D5F2; 
        
        //D8AB is the hex value at which I want to start when the LED is on

    // enable global interrupts:
    sei();
}

ISR(TIMER1_OVF_vect)
{
    digitalWrite(LEDPIN, !digitalRead(LEDPIN));
    // or use: PORTB ^= _BV(PB5);// PB5 =pin 19 is digitalpin 13
}
