/*      Author: khuo002
 *       *       *       *  Partner(s) Name:
 *        *        *        *     Lab Section:
 *         *         *         *    Assignment: Lab 11  Exercise 1
 *          *          *          *   Exercise Description: [optional - include for your own benefit]
 *           *           *           *
 *            *            *           *  I acknowledge all content contained herein, excluding template or example
 *             *             *            * code, is my own original work.
 *              *              *             */
#include <avr/io.h>
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#include "io.h"
#endif

volatile signed char TimerFlag = 0;

unsigned long _avr_timer_M = 0;
unsigned long _avr_timer_cntcurr = 0;
unsigned char y;
unsigned char k = ' ';
enum LCD_displayee_States{wait, displayee1};
enum LEDs_displayee_States{displayeeA};
unsigned char GetBit(unsigned char x, unsigned char k) {
        return ((x & (0x01 << k)) != 0);
}

typedef struct task{
        signed char state;
        unsigned long int period;
        unsigned long int elapsedTime;
        int (*TickFct)(int);
} task;

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
int r = 0;
unsigned char GetKeyPadKey(){
        PORTA = 0xEF;
        asm("nop");
        if(GetBit(PINA,0) == 0){ k = '1'; r = 1; return('1');}
        if(GetBit(PINA,1) == 0){ k = '4'; r = 1; return('4');}
        if(GetBit(PINA,2) == 0){ k = '7'; r = 1; return('7');}
        if(GetBit(PINA,3) == 0){ k = '*'; return('*');}

        PORTA = 0xDF;
        asm("nop");
        if(GetBit(PINA,0) == 0){ k = '2'; r = 1; return('2');}
        if(GetBit(PINA,1) == 0){ k = '5'; r = 1; return('5');}
        if(GetBit(PINA,2) == 0){ k = '8'; r = 1; return('8');}
        if(GetBit(PINA,3) == 0){ k = '0'; r = 1; return('0');}

        PORTA = 0xBF;
        asm("nop");
        if(GetBit(PINA,0) == 0){ k = '3'; r = 1; return('3');}
        if(GetBit(PINA,1) == 0){ k = '6'; r = 1; return('6');}
        if(GetBit(PINA,2) == 0){ k = '9'; r = 1; return('9');}
        if(GetBit(PINA,3) == 0){ k = '#'; r = 1; return('#');}

        PORTA = 0x7F;
        asm("nop");
        if(GetBit(PINA,0) == 0){ k = 'A'; r = 1; return('A');}
        if(GetBit(PINA,1) == 0){ k = 'B'; r = 1; return('B');}
        if(GetBit(PINA,2) == 0){ k = 'C'; r = 1; return('C');}
        if(GetBit(PINA,3) == 0){ k = 'D'; r = 1; return('D');}

        return('\0');
}

int LEDS_Tick(int state){
	
	switch(state){
		case displayeeA: state = displayeeA; break;
		default: state = displayeeA; break;
	}
	
	switch(state){
		case displayeeA:
			switch(y){
				case '\0': PORTB = 0x1F; break;
				case '1': PORTB = 0x01; break;
				case '2': PORTB = 0x02; break;
				case '3': PORTB = 0x03; break;
				case '4': PORTB = 0x04; break;
				case '5': PORTB = 0x05; break;
				case '6': PORTB = 0x06; break;
				case '7': PORTB = 0x07; break;
				case '8': PORTB = 0x08; break;
				case '9': PORTB = 0x09; break;
				case 'A': PORTB = 0x0A; break;
				case 'B': PORTB = 0x0B; break;
				case 'C': PORTB = 0x0C; break;
				case 'D': PORTB = 0x0D; break;
				case '*': PORTB = 0x0E; break;
				case '0': PORTB = 0x00; break;
				case '#': PORTB = 0x0F; break;
				default: PORTB = 0x1B; break;
			}
			
			break;
	}
	return state;
}

unsigned int Curse = 1;
int LCD_Tick(int state){
	
	switch(state){
		case wait: 
			if(r) state = displayee1;
			else state = wait;
			break;
			
		case displayee1: state = wait; break;
		default: state = displayee1; break;
	}
	
	switch(state){
		case displayee1:
			if(Curse >= 16) Curse = 0;
			r = 0;
			LCD_Cursor(Curse);
			LCD_WriteData(k);
			Curse++;
			break;
	}
	return state;
}

int main(){
		DDRA = 0xF0; PORTA = 0x0F;
        DDRB = 0xFF; PORTB = 0x00;
		DDRC = 0xFF; PORTC = 0x00;
		DDRD = 0xFF; PORTD = 0x00;

		
		static task task1, task2;
		task *tasks[] = {&task1, &task2};
		const unsigned short numTasks = 2; //sizeof(tasks)/sizeof(task*);
		
		task1.state = displayee1;
		task1.period = 300;
		task1.elapsedTime = task1.period;
		task1.TickFct = &LEDS_Tick;
		
		task2.state = displayeeA;
		task2.period = 300;
		task2.elapsedTime = task2.period;
		task2.TickFct = &LCD_Tick;
	
		TimerSet(100);
		TimerOn();
		LCD_init();
		LCD_DisplayString(1, "Congratulations!");	
		unsigned short i;
		
        while(1){
			y = GetKeyPadKey();
			for(i = 0; i < numTasks; i++){
				if(tasks[i]->elapsedTime >= tasks[1]->period){
					tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);
					tasks[i]->elapsedTime = 0;
				}
				tasks[i]->elapsedTime += 100;
			}
			while(!TimerFlag);
			TimerFlag = 0;
        }
		
		return 0;
}
