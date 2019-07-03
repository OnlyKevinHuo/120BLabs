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

enum LED_States {Init, abyss, juan, too, tree, FOUR, pibuh, sicks, ravine} LED_State;


void Flashing_Lights() {
   unsigned char mask = PINA & 0x01;

    switch(LED_State) { // Transitions
	
	case Init:
		
        LED_State = abyss;
        break;
	
	case abyss:
		if(mask == 0x01) LED_State = juan;
		if(mask == 0x00) LED_State = abyss;
        break;
		
    case juan: 
		if(mask == 0x01 && PORTC == 0x00) LED_State  = too;
		if(mask == 0x01 && PORTC == 0x001) LED_State  = abyss;
		if(mask == 0x00) LED_State = juan;
        break;
		 
    case too: 
        if(mask == 0x01 && PORTC == 0x00) LED_State  = tree;
		if(mask == 0x01 && PORTC == 0x001) LED_State  = juan;
		if(mask == 0x00) LED_State = too;
        break;
	
	case tree:
		if(mask == 0x01 && PORTC == 0x00) LED_State  = FOUR;
		if(mask == 0x01 && PORTC == 0x001) LED_State  = too;
		if(mask == 0x00) LED_State = tree;
        break;

	case FOUR:
		if(mask == 0x01 && PORTC == 0x00) LED_State  = pibuh;
		if(mask == 0x01 && PORTC == 0x001) LED_State  = tree;
		if(mask == 0x00) LED_State = FOUR;
        break;
		
	case pibuh:
		if(mask == 0x01 && PORTC == 0x00) LED_State  = sicks;
		if(mask == 0x01 && PORTC == 0x001) LED_State  = FOUR;
		if(mask == 0x00) LED_State = pibuh;
        break;
		
	case sicks:
		if(mask == 0x01 && PORTC == 0x00) LED_State = ravine;
		if(mask == 0x01 && PORTC == 0x01) LED_State  = pibuh;
		if(mask == 0x00) LED_State = sicks;
        break;
		
	case ravine:
		if(mask == 0x01) LED_State = sicks;
		if(mask == 0x00) LED_State = ravine;
        break;
		
        LED_State = sicks;
        break;
	  default:
         LED_State  = Init;
   } // Transitions

   switch(LED_State ) { // State actions
   
    case Init:
		PORTC = 0x00;
        break;
		 
    case abyss:
		PORTB = 0x00;
		if(PORTC == 0x01){
			PORTC = 0x00;
			break;
		}
        break;
		
	case juan:
        if(PORTC == 0x00){
			PORTB = 0x01;
			break;
		}
		if(PORTC == 0x01){
			PORTB = 0x3F;
			break;
		}
        break;
		
    case too:
        if(PORTC == 0x00){
			PORTB = 0x03;
			break;
		}
		if(PORTC == 0x01){
			PORTB = 0x3E;
			break;
		}
        break;
		
	case tree:
        if(PORTC == 0x00){
			PORTB = 0x07;
			break;
		}
		if(PORTC == 0x01){
			PORTB = 0x3C;
			break;
		}
        break;
	
	case FOUR:
        if(PORTC == 0x00){
			PORTB = 0x0F;
			break;
		}
		if(PORTC == 0x01){
			PORTB = 0x38;
			break;
		}
        break;
		 
	case pibuh:
        if(PORTC == 0x00){
			PORTB = 0x1F;
			break;
		}
		if(PORTC == 0x01){
			PORTB = 0x30;
			break;
		}
        break;
		 
	case sicks:
        if(PORTC == 0x01){
			PORTB = 0x20;
			break;
		}
		if(PORTC == 0x01){
			PORTB = 0x3E;
			break;
		}
        break;
		
	case ravine:
		PORTB = 0x00;
		if(PORTC == 0x00){
			PORTC = 0x01;
			break;
		}
        break;
    default: 
		break;
   } // State actions

}

int main(void) {
	
    DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	DDRB = 0xFF; PORTB = 0x00;
	LED_State = Init;
	
    /* Insert your solution below */
    while (1) {
		Flashing_Lights();
    }
        return 1;
}
