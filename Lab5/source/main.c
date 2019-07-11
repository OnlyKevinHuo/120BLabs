/*	Author: khuo002i
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab 7  Exercise 1
 *	Exercise Description: [optional - include for your own benefit]
 *
*	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
//#include "io.h"

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

void set_PWM(double frequency){
	static double current_frequency;
	if(frequency != current_frequency){
	if(!frequency){TCCR3B &= 0x08;}
	else{TCCR3B |= 0x03;}
	
	if(frequency < 0.954){ OCR3A = 0xFFFF;}
	else if(frequency > 31250){OCR3A = 0x0000;}
	else{OCR3A = (short)(8000000/(128*frequency))-1;}
	TCNT3 = 0;
	current_frequency = frequency;
	}
}

void PWM_on(){
	TCCR3A = (1 << COM3A0);
	TCCR3B = (1 << WGM32) | (1 << CS31) | (1<<CS30);
	set_PWM(0);
}

void PWM_off(){
	TCCR3A = 0x00;
	TCCR3B = 0x00;
}

#define A0 (~PINA & 0x01)
#define A1 (~PINA & 0x02)
#define A2 (~PINA & 0x04)

enum Speak_States{Init, off, on, CFOUR, DFOUR, EFOUR, FFOUR, GFOUR, AFOUR, BFOUR, C2FOUR} Speak_State;

void tick(){
  switch(Speak_State){
    case Init:
        Speak_State = off;
        break;

    case off:
        if(A0) Speak_State = on;
        else Speak_State = off;
        break;

    case on:
        Speak_State = CFOUR;
        break;
    case CFOUR:
        if(A0) Speak_State = off;
	if(A1) Speak_State = DFOUR;
        else Speak_State = CFOUR;
        break;

    case DFOUR:
        if(A0) Speak_State = off;
	if(A1) Speak_State = EFOUR;
	if(A2) Speak_State = CFOUR;
        else Speak_State = DFOUR;
        break;

    case EFOUR:
        if(A0) Speak_State = off;
	if(A1) Speak_State = FFOUR;
	if(A2) Speak_State = DFOUR;
        else Speak_State = EFOUR;
	break;

    case FFOUR:
        if(A0) Speak_State = off;
	if(A1) Speak_State = GFOUR;
	if(A2) Speak_State = EFOUR;
        else Speak_State = FFOUR;
	break;
    
    case GFOUR:
        if(A0) Speak_State = off;
	if(A1) Speak_State = AFOUR;
	if(A2) Speak_State = FFOUR;
        else Speak_State = GFOUR;
	break;

    case AFOUR:
        if(A0) Speak_State = off;
	if(A1) Speak_State = BFOUR;
	if(A2) Speak_State = GFOUR;
        else Speak_State = AFOUR;
	break;

    case BFOUR:
        if(A0) Speak_State = off;
	if(A1) Speak_State = C2FOUR;
	if(A2) Speak_State = AFOUR;
        else Speak_State = BFOUR;
	break;

    case C2FOUR:
        if(A0) Speak_State = off;
	if(A2) Speak_State = BFOUR;
        else Speak_State = C2FOUR;
	break;

    default:
        Speak_State = off;
        break;
  }

  switch(Speak_State){
    case Init:
        break;

    case off:
        set_PWM(0);
        break;

    case on:
	set_PWM(0);
	break; 
    case CFOUR:
        set_PWM(2616.3);
        break;

    case DFOUR:
        set_PWM(2936.6);
        break;

    case EFOUR:
        set_PWM(3296.3);
        break;

    case FFOUR:
        set_PWM(3492.3);
        break;

    case GFOUR:
        set_PWM(3290);
        break;

    case AFOUR:
        set_PWM(4400);
        break;

    case BFOUR:
        set_PWM(4938.8);
        break;

    case C2FOUR:
        set_PWM(5232.5);
        break;
    default:
        break;
  }
}
int main(){
        
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
        
        TimerSet(500);
        TimerOn();
	PWM_on();
	while(1){
	   	tick();
		while(!TimerFlag);
		TimerFlag = 0;
	}
	return 1;
}
