/*	Author: khuo002
 *	Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab 4  Exercise 2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
  */

#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum Lock_States {Zero, One, Two, Three, Four, Five} Lock_State;

void Lock_Trans() {
   switch(Lock_State) { // Transitions
		
	case Zero:
		
        if(PINA == 0x01) Lock_State = One;
		if(PINA == 0x02) Lock_State = Two;
		if(PINA == 0x04) Lock_State = Three;
		Lock_State = 0;
        break;
		 
    case One: 
		if(PINA == 0x00) Lock_State = Four;
		if(PINA == 0x01) Lock_State = One;
		Lock_State = 0;
        break;
		 
    case Two: 
        if(PINA == 0x00) Lock_State  = Zero;
		Lock_State = Two;
        break;
	
	case Three:
		if(PINA == 0x00) Lock_State  = Zero;
		Lock_State = Three;
        break;

	case Four:
		if(PINA == 0x02) Lock_State = Five;
		if(PINA == 0x00) Lock_State = Four;
		Lock_State = Zero;
		break;
		
	case Five:
		if(PINA == 0x80) Lock_State = Zero;
		Lock_State = Five;
		break;
		
	  default:
         Lock_State  = Zero;
   } // Transitions

   switch(Lock_State ) { // State actions
   
    case Zero:
		PORTB = 0x00;
        break;
		 
    case One: 
        break;
		 
    case Two: 
        break;
	
	case Three:
        break;

	case Four:
		break;
		
	case Five:
		PORTB = 0x01;
		break;
		
	  default:
         break;
   } // State actions

}

int main(void) {
	
    DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	
	Lock_State = 0;
	
    /* Insert your solution below */
    while (1) {
		Lock_Trans();
    }
        return 1;
}
