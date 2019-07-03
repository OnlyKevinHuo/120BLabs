/*	Author: khuo002
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab 6  Exercise 1
 *	Exercise Description: [optional - include for your own benefit]
 *
*	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
volatile unsigned char TimerFlag = 0;

unsigned long _avr_timer_M = 0;
unsigned long _avr_timer_cntcurr = 0;

void TimerOn(){
	TCCR1B = 0x0B;
	OCR1A = 125;
	TIMSK1 = 0x02;
	TCNT1 = 0;
	_avr_timer_cntcurr = _avr_timer_M;
	SREG |= 0x80;
}

void TimerOff(){
	TCCR1B = 0x00;
}

void TimerISR(){
	TimerFlag = 1;
}

ISR(TIMER1_COMPA_vect){
	_avr_timer_cntcurr--;
	if(_avr_timer_cntcurr == 0){
		TimerISR();
		_avr_timer_cntcurr = _avr_timer_M;
	}
}

void TimerSet(unsigned long M){
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}


enum LED_States {Init, juan, jt, too, tt, tree, to} LED_State;
/*
void tick(){
	switch(LED_State){
		case Init:
                  		LED_State = juan;
        			break;
		case juan:
                  		LED_State = too;
        			break;
		case too:
                  		LED_State = tree;
        			break;
		case tree:
                  		LED_State = juan;
        			break;
		default:	
			LED_State = Init;
			break;
	}		

	switch(LED_State){
		case Init:
        			break;
		case juan:
                  		PORTC = 0x01;
        			break;
		case too:
                  		PORTC = 0x02;
        			break;
		case tree:
                  		PORTC = 0x04;
        			break;
		default:	
			break;
	}
} 
*/
void tick(){
	unsigned char mask = ~PINA & 0x01;
        switch(LED_State){
                case Init:
                	LED_State = juan;
                        break;
                case juan:
                        if(mask == 0x00 && PORTB == 0x00) LED_State = too;
			if(mask == 0x01 && PORTB == 0x00) LED_State = juan;
			if(mask == 0x00 && PORTB == 0x01) LED_State = juan;
			if(mask == 0x01 && PORTB == 0x01) LED_State = jt;
                        break;
                case too:
			if(mask == 0x00 && PORTB == 0x00) LED_State = tree;
                        if(mask == 0x01 && PORTB == 0x00) LED_State = too;
			if(mask == 0x00 && PORTB == 0x01) LED_State = too;
			if(mask == 0x01 && PORTB == 0x01) LED_State = tt;
                        break;
                case tree:
			if(mask == 0x00 && PORTB == 0x00) LED_State = juan;
                        if(mask == 0x01 && PORTB == 0x00) LED_State = tree;
			if(mask == 0x00 && PORTB == 0x00) LED_State = tree
                        if(mask == 0x01 && PORTB == 0x01) LED_State = to;
			break;
		case jt:
			LED_State = too;
			break;
		case tt: 
			LED_State = tree;
			break;
		case to:
			LED_State = juan;
			break;      
          default:        
                        LED_State = Init;
                        break;
        }               

        switch(LED_State){
                case Init:
                                break;
                case juan:
                        PORTC = 0x01;
			if(mask == 0x01 && PORTB == 0x00) PORTB = 0x01;
			break;
                case too:
                        PORTC = 0x02;
                        if(mask == 0x01 && PORTB == 0x00) PORTB = 0x01;
                        break;
                case tree:
                        PORTC = 0x04;
			if(mask == 0x01 && PORTB == 0x00) PORTB = 0x01;
                        break;
		case jt:
			PORTB = 0x00;
			break;
		case tt:
                        PORTB = 0x00;
                        break;
		case to:
                        PORTB = 0x00;
                        break;

                default:        
                        break;
        }
} 

void main(){
        
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF;
        PORTC = 0x00;
        TimerSet(100);
        TimerOn();
        
        while(1){
                tick();
                while(!TimerFlag);
                TimerFlag = 0;
        }
}
/*
enum LED_States {Init, abyss, juan, too, tree, FOUR, pibuh, sicks, ravine} LED_State;

void Flashing_Lights() {
   unsigned char mask = ~PINA & 0x01;

    switch(LED_State) { // Transitions
	
	case Init:
		
        LED_State = abyss;
        break;
	
	case abyss:
		if(mask == 0x01) LED_State = juan;
		if(mask == 0x00) LED_State = abyss;
        break;
		
    case juan: 
		if(mask == 0x01 && PORTB == 0x00) LED_State  = too;
		if(mask == 0x01 && PORTB == 0x001) LED_State  = abyss;
		if(mask == 0x00) LED_State = juan;
        break;
		 
    case too: 
        if(mask == 0x01 && PORTB == 0x00) LED_State  = tree;
		if(mask == 0x01 && PORTB == 0x001) LED_State  = juan;
		if(mask == 0x00) LED_State = too;
        break;
	
	case tree:
		if(mask == 0x01 && PORTB == 0x00) LED_State  = FOUR;
		if(mask == 0x01 && PORTB == 0x001) LED_State  = too;
		if(mask == 0x00) LED_State = tree;
        break;

	case FOUR:
		if(mask == 0x01 && PORTB == 0x00) LED_State  = pibuh;
		if(mask == 0x01 && PORTB == 0x001) LED_State  = tree;
		if(mask == 0x00) LED_State = FOUR;
        break;
		
	case pibuh:
		if(mask == 0x01 && PORTB == 0x00) LED_State  = sicks;
		if(mask == 0x01 && PORTB == 0x001) LED_State  = FOUR;
		if(mask == 0x00) LED_State = pibuh;
        break;
		
	case sicks:
		if(mask == 0x01 && PORTB == 0x00) LED_State = ravine;
		if(mask == 0x01 && PORTB == 0x01) LED_State  = pibuh;
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
	break;
   } // Transitions

   switch(LED_State ) { // State actions
   
    case Init:
		PORTB = 0x00;
        break;
		 
    case abyss:
		PORTC = 0x00;
		if(PORTB == 0x01){
			PORTB = 0x00;
			break;
		}
        break;
		
	case juan:
        if(PORTB == 0x00){
			PORTC = 0x01;
			break;
		}
		if(PORTB == 0x01){
			PORTC = 0x3F;
			break;
		}
        break;
		
    case too:
        if(PORTB == 0x00){
			PORTC = 0x03;
			break;
		}
		if(PORTB == 0x01){
			PORTC = 0x3E;
			break;
		}
        break;
		
	case tree:
        if(PORTB == 0x00){
			PORTC = 0x07;
			break;
		}
		if(PORTB == 0x01){
			PORTC = 0x3C;
			break;
		}
        break;
	
	case FOUR:
        if(PORTB == 0x00){
			PORTC = 0x0F;
			break;
		}
		if(PORTB == 0x01){
			PORTC = 0x38;
			break;
		}
        break;
		 
	case pibuh:
        if(PORTB == 0x00){
			PORTC = 0x1F;
			break;
		}
		if(PORTB == 0x01){
			PORTC = 0x30;
			break;
		}
        break;
		 
	case sicks:
        if(PORTB == 0x01){
			PORTC = 0x20;
			break;
		}
		if(PORTB == 0x01){
			PORTC = 0x3E;
			break;
		}
        break;
		
	case ravine:
		PORTC = 0x00;
		if(PORTB == 0x00){
			PORTB = 0x01;
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
	

    while (1) {
		Flashing_Lights();
    }
        return 1;
}
*/


