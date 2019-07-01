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

enum Calc_States {Calc_Init, Calc_S1, Calc_S2, Calc_Wait, Calc_Reset} Calc_State;
enum Prev_States{Innie, SPlus, SMinus, SReset} Prev_State;

void Calc_Trans() {
   switch(Calc_State) { // Transitions
      
	case Calc_Init:
        if(PINA == 0x01) Calc_State = Calc_S1;
		if(PINA == 0x02) Calc_State = Calc_S2;
		if(PINA == 0x03) Calc_State = Calc_Reset;
		if(PINA == 0x00) Calc_State = Calc_Init;
        break;
		 
    case Calc_S1: 
        if(PINA == 0x03) Calc_State  = Calc_Reset;
		Calc_State = Calc_Wait;
        break;
		 
    case Calc_S2: 
        if(PINA == 0x03) Calc_State  = Calc_Reset;
		Calc_State = Calc_Wait;
        break;
	
	case Calc_Wait:
		if(PINA == 0x03) Calc_State = Calc_Reset;
		if(PINA == 0x00) Calc_State = Calc_Init;
		Calc_State = Calc_Wait;

	case Calc_Reset:
		Calc_State = Calc_Wait;
		
	  default:
         Calc_State  = Calc_Init;
   } // Transitions

   switch(Calc_State ) { // State actions
   
    case Calc_Init:
        break;
		 
    case Calc_S1:
        if(PORTC == 0x09) break;
		PORTC++;
        break;
		
    case Calc_S2:
        if(PORTC == 0x00) break;
		PORTC = PORTC - 0x01;
        break;
		
	case Calc_Wait:
        break;
	
	case Calc_Reset:
		 PORTC = 0x00;
         break;
		 
    default: 
		break;
   } // State actions

}

int main(void) {
	
    DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	PORTC = 0x07;
	Calc_State = Calc_Init;
	
    /* Insert your solution below */
    while (1) {
		Calc_Trans();
    }
        return 1;
}
