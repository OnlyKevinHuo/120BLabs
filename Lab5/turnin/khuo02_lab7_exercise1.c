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
#include "io.h"
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

enum LED_States{Init, lelou, juan, too, tree, FOUR, pibuh, sicks, sepen, ate, nein} LED_State;

void tick(){
	unsigned char mask = ~PINA & 0x03;
	switch(LED_State) { // Transitions
	
	case Init:
		
        LED_State = lelou;
        break;
	
	case lelou:
		if(mask == 0x00 || mask == 0x02) LED_State = lelou;
		if(mask == 0x01) LED_State = juan;
		if(mask == 0x03) LED_State = lelou;
        break;
		
    case juan: 
		if(mask == 0x00) LED_State  = juan;
		if(mask == 0x01) LED_State  = too;
		if(mask == 0x02 || mask == 0x03) LED_State = lelou;
		
        break;	
		
    case too: 
        if(mask == 0x00) LED_State  = too;
		if(mask == 0x01) LED_State  = tree;
		if(mask == 0x02) LED_State = juan;
		if(mask == 0x03) LED_State = lelou;
        break;
	
	case tree:
		if(mask == 0x00) LED_State  = tree;
		if(mask == 0x01) LED_State  = FOUR;
		if(mask == 0x02) LED_State = too;
		if(mask == 0x03) LED_State = lelou;
        break;
		
	case FOUR:
		if(mask == 0x00) LED_State  = juan;
		if(mask == 0x01) LED_State  = pibuh;
		if(mask == 0x02) LED_State = tree;
		if(mask == 0x03) LED_State = lelou;
        break;
		
		
	case pibuh:
		if(mask == 0x00) LED_State  = pibuh;
		if(mask == 0x01) LED_State  = sicks;
		if(mask == 0x02) LED_State = FOUR;
		if(mask == 0x03) LED_State = lelou;
        break;
		
	case sicks:
		if(mask == 0x00) LED_State  = sicks;
		if(mask == 0x01) LED_State  = sepen;
		if(mask == 0x02) LED_State = pibuh;
		if(mask == 0x03) LED_State = lelou;
        break;
		
	case sepen:
		if(mask == 0x00) LED_State  = sepen;
		if(mask == 0x01) LED_State  = ate;
		if(mask == 0x02) LED_State = sicks;
		if(mask == 0x03) LED_State = lelou;
        break;
		
	case ate:
		if(mask == 0x00) LED_State  = ate;
		if(mask == 0x01) LED_State  = nein;
		if(mask == 0x02) LED_State = sepen;
		if(mask == 0x03) LED_State = lelou;
        break;
	
	case nein:
		if(mask == 0x00) LED_State  = nein;
		if(mask == 0x01) LED_State  = nein;
		if(mask == 0x02) LED_State = ate;
		if(mask == 0x03) LED_State = lelou;
        break;
		
	  default:
         LED_State  = Init;
	break;
   }
   
   switch(LED_State ) { // State actions
   
    case Init:
        break;
		 
    case lelou:
		LCD_WriteData( 0 + ‘0’ );
        break;
		
	case juan:
        LCD_WriteData( 1 + ‘0’ );
        break;
	
    case too:
        LCD_WriteData( 2 + ‘0’ );
        break;
		
	case tree:
        LCD_WriteData( 3 + ‘0’ );
        break;

	case FOUR:
        LCD_WriteData( 3 + ‘0’ );
        break;
		 
	case pibuh:
        LCD_WriteData( 5 + ‘0’ );
        break;
	
	case sicks:
        LCD_WriteData( 6 + ‘0’ );
        break;
		
	case sepen:
		LCD_WriteData( 7 + ‘0’ );
        break;
		
	case ate:
		LCD_WriteData( 8 + ‘0’ );
        break;
		
	case nein:
		LCD_WriteData( 9 + ‘0’ );
        break;
		
    default: 
		break;
   } // State actions
}

int main(){
        
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xFF; PORTC = 0x00;
        TimerSet(100);
        TimerOn();
        
        w hile(1){
                tick();
                while(!TimerFlag);
                TimerFlag = 0;
        }
	return 1;
}
