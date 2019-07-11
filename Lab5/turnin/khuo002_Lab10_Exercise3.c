/*	Author: khuo002
 *	 *  Partner(s) Name: 
 *	  *	Lab Section:
 *	   *	Assignment: Lab 10  Exercise 1
 *	    *	Exercise Description: [optional - include for your own benefit]
 *	     *
 *	     *	I acknowledge all content contained herein, excluding template or example
 *	      *	code, is my own original work.
 *	       */
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
/*
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
*/

#define A2 (~PINA & 0x04)
unsigned char TL = 0x00;
unsigned char Blinks = 0x00;
unsigned char speaker = 0x00;
enum TL_States{TL_Init, Set1, Set2, Set3} TL_State;
enum Blink_States{Blink_Init, fox, dagger} Blink_State;
enum Speak_States{Speak_Init, annoyo, tron} Speak_State;

void TL_Tick(){
  switch(TL_State){
    case TL_Init:
        TL_State = Set1;
        break;

    case Set1:
        TL_State = Set2;
        break;

    case Set2:
        TL_State = Set3;
        break;

    case Set3:
        TL_State = Set1;
        break;

    default:
        TL_State = TL_Init;
        break;
  }

  switch(TL_State){
    case TL_Init:
        break;

    case Set1:
        TL = 0x01;
        break;

    case Set2:
        TL = 0x02;
        break;

    case Set3:
        TL = 0x04;
        break;

    default:

        break;
  }
}

void Blink_Tick(){
  switch(Blink_State){
    case Blink_Init:
        Blink_State = fox;
        break;

    case fox:
        Blink_State = dagger;
        break;

    case dagger:
        Blink_State = fox;
        break;

    default:
        Blink_State = Blink_Init;
        break;
  }

  switch(Blink_State){
    case Blink_Init:
        break;

    case fox:
        Blinks = 0x08;
        break;

    case dagger:
        Blinks = 0x00;
        break;

    default:
        Blink_State = Blink_Init;
        break;
  }
}

void Speaks(){
  switch(Speak_State){
    case Speak_Init:
        Speak_State = annoyo;
        break;

    case annoyo:
        Speak_State = tron;
        break;

    case tron:
        Speak_State = annoyo;
        break;

    default:
        Speak_State = Speak_Init;
        break;
  }

  switch(Speak_State){
    case Speak_Init:
        break;

    case annoyo:
        speaker = 0x10;
        break;

    case tron:
        speaker = 0x00;
        break;

    default:
        break;
  }
}

void Fusion_Ha(){
	PORTB = ((Blinks | TL) | speaker);
}

unsigned long TL_ET = 0;
unsigned long Blinks_ET = 0;
unsigned long Speaks_ET = 0;
int main(){
        
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
    	TimerSet(100);
    	TimerOn();
	TL_State = TL_Init;
	Blink_State = Blink_Init;
	while(1){
		if(TL_ET >= 300){
	   		TL_Tick();
			TL_ET = 0;
		}

		if(Blinks_ET >= 1000){
			Blink_Tick();
			Blinks_ET = 0;
		}

		if(A2){
			if(Speaks_ET >= 300){
	   		Speaks();
			Speaks_ET = 0;
		
			}
			Speaks_ET += 200;
		}

		while(!TimerFlag);
		TimerFlag = 0;
		TL_ET += 100;
		Blinks_ET += 100;
		Fusion_Ha();
	}
	return 1;
}	

