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
		DDRB = 0xFF; PORTB = 0x00;
        DDRC = 0xFF; PORTC = 0x00;
        unsigned char fourToSev = 0x10;
        unsigned char zeroToThree = 0x01;
		unsigned char bAdder = 0x01;
		unsigned char cAdder = 0x10;
		unsigned char bResult = 0x00;
		unsigned char cResult = 0x00;
		unsigned char chequer = 0x00;
		unsigned int i;
    /* Insert your solution below */
    while (1) {
                fourToSev = 0x10;
		zeroToThree = 0x01;
		chequer = 0x00;
		bResult = 0x00;
		cResult = 0x00;
		bAdder = 0x01;
		cAdder = 0x10;
				
				for(i = 0; i < 4; i++){
					chequer = PINA & fourToSev;
					if(chequer == fourToSev){bResult = bResult +bAdder;}
					chequer = 0x00;
					bAdder = bAdder + bAdder;
					fourToSev = fourToSev + fourToSev;
					
				}
				
				for(i = 0; i < 4; i++){
					chequer = PINA & zeroToThree;
					if(chequer == zeroToThree){cResult = cResult +cAdder;}
					chequer = 0x00;
					cAdder = cAdder + cAdder;
					zeroToThree = zeroToThree + zeroToThree;
						
				}

				PORTC = cResult;
				PORTB = bResult;
    }
        return 1;
}
