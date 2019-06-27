/*	Author: khuo002
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0x00; PORTB = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	unsigned char mask = 0x01;
	unsigned char result = 0x00;
	unsigned char cnt = 0x00;
	unsigned int i;
    /* Insert your solution below */
    while (1) {
	cnt = 0x00;
	mask = 0x01;
	for(i = 0; i < 8; i++){
		result = PINA & mask;
		if(result != 0){
			cnt++;	
		}
		mask = mask+mask;
	}

	mask = 0x01;

	for(i = 0; i < 8; i++){

                result = PINB & mask;
                if(result != 0){
                        cnt++;
                }
                mask = mask+mask;
        }
	PORTC = cnt;
    }
}
