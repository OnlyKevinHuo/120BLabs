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
        DDRC = 0xFF; PORTC = 0x00;
        unsigned char mask = 0x00;
        unsigned char result = 0x00;
    /* Insert your solution below */
    while (1) {
                result = 0x00;
                mask = PINA & 0x0F;

                if(mask == 0x11) result = 0xFF;
                if((mask == 0x0D) || (mask == 0x0E) || (mask == 0x0F)){result = 0x3F;}
                if((mask == 0x0A) || (mask == 0x0B) || (mask == 0x0C)){result = 0x3E;}
                if((mask == 0x07) || (mask == 0x08) || (mask == 0x09)){result =  0x3C;}
                if((mask == 0x05) || (mask == 0x06)){result = 0x38;}
                if((mask == 0x03) || (mask == 0x04)){result = 0x30;}
                if((mask == 0x01) || (mask == 0x02)){result = 0x20;}

		mask = PINA & 0x70;
                if((result & 0xCF) == 0x00){result = result + 0x40;}
		if(mask == 0x70) result = result + 0x80;
		PORTC = result;
    }
        return 1;
}
