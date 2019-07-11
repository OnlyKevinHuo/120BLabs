/*	Author: khuo002i
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab 7  Exercise 1
 *	Exercise Description: [optional - include for your own benefit]
 *
*	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
//Lab 8 Exercise 2
#include <avr/io.h>
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#include "io.h"

#endif

volatile unsigned char TimerFlag = 0;

unsigned long _avr_timer_M = 0;
unsigned long _avr_timer_cntcurr = 0;

signed int i = 0;
const int SIZE = 8;

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

enum Speak_States{Init, off, on, PLAY, Wait, offWait} Speak_State;

void tick(double freq[]){
  switch(Speak_State){
    case Init:
        Speak_State = off;
        break;

    case off:
        if(A0) Speak_State = on;
        else Speak_State = off;
        break;

    case on:
        if(!A0) Speak_State = PLAY;
		else Speak_State = on;
        break;
		
    case PLAY:
        if(A0) Speak_State = offWait;
		if(A1 || A2) Speak_State = Wait;
        else Speak_State = PLAY;
        break;

    case Wait:
        if(PORTC == 0x00) Speak_State = PLAY;
		if(A0) Speak_State = offWait;
		else Speak_State = Wait;
        break;
		
	case offWait:
        if(A0) Speak_State = offWait;
		else Speak_State = off;
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
	
    case PLAY:
        set_PWM(freq[i]);
		PORTC = 0x01;
        break;

    case Wait:
		if(A1 && PORTC == 0x01){
			if(i == 7) break;
			else i++;
		}
		else if(A2 && PORTC == 0x01){
			if(i == 0) break;
			else i--;
		}
		
		PORTC = 0x00;
        break;
	
	case offWait:
        break;
		
    default:
        break;
  }
}
int main(){
        
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
 	DDRC = 0xFF; PORTC = 0x00;
	
	//double freg[SIZE] = {2616.3, 2936.6, 3296.3, 3492.3, 3920, 4400, 4938.8, 5232.5};
	double freq[8] = {261.63, 293.66, 329.63, 349.23, 392, 440, 493.88, 523.35};
    TimerSet(50);
    TimerOn();
	PWM_on();
	while(1){
	   	tick(freq);
		while(!TimerFlag);
		TimerFlag = 0;
	}
	return 1;
}	
