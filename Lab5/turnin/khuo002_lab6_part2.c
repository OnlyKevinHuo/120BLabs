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

void tick(){
        unsigned char mask = PINA & 0x01;
        switch(LED_State){
                case Init:
                        LED_State = juan;
                        break;
                case juan:
                        if(mask == 0x00) LED_State = too;
                        if(mask == 0x01) LED_State = jt;
                        break;
                case too:
                        if(mask == 0x00) LED_State = tree;
                        if(mask == 0x01) LED_State = tt;
                        break;
                case tree:
                        if(mask == 0x00) LED_State = juan;
                        if(mask == 0x01) LED_State = to;

                        break;
                case jt:
						if(mask == 0x01  && PORTB == 0x01) LED_State = jt;
						if(mask == 0x00) LED_State = jt;
						if(mask == 0x01 && PORTB == 0x00) LED_State = too;
                        break;
                case tt:
                        if(mask == 0x01  && PORTB == 0x01) LED_State = tt;
						if(mask == 0x00) LED_State = tt;
						if(mask == 0x01 && PORTB == 0x00) LED_State = tree;
                        break;
                case to:
                        if(mask == 0x01  && PORTB == 0x01) LED_State = to;
						if(mask == 0x00) LED_State = to;
						if(mask == 0x01 && PORTB == 0x00) LED_State = juan;
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
                        if(PORTB == 0x00) PORTB = 0x01;
                        break;
                case too:
                        PORTC = 0x02;
                        if(PORTB == 0x00) PORTB = 0x01;
                        break;
                case tree:
                        PORTC = 0x04;
                        if(PORTB == 0x00) PORTB = 0x01;
                        break;
                case jt:
						PORTC = 0x01;
                        if(mask == 0x00 && PORTB == 0x01) PORTB = 0x00;
                        break;
                case tt:
                        PORTC = 0x02;
						if(mask == 0x00 && PORTB == 0x01) PORTB = 0x00;
                        break;
                case to:
                        PORTC = 0x04;
						if(mask == 0x00 && PORTB == 0x01) PORTB = 0x00;
                        break;

                default:
                        break;
        }
}

int main(){
        
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
        TimerSet(200);
        TimerOn();
        
        while(1){
                tick();
                while(!TimerFlag);
                TimerFlag = 0;
        }
	return 1;
}

