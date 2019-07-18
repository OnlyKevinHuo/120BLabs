#include <avr/io.h>
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#include "io.h"
#endif

volatile signed char TimerFlag = 0;

unsigned long _avr_timer_M = 0;
unsigned long _avr_timer_cntcurr = 0;
volatile unsigned int array_place = 0;
static char sent[67] = {' ', ' ', ' ',' ', ' ', ' ', ' ',' ', ' ', ' ', ' ',' ', ' ', ' ', ' ', 'C', 'S', '1', '2', '0', 'B', ' ', 'i', 's', ' ', 'L', 'e', 'g', 'e', 'n', 'd', '.', '.', '.', ' ', 'w', 'a', 'i', 't', ' ', 'f', 'o', 'r', ' ', 'i', 't', ' ', 'D', 'A', 'R', 'Y', '!', ' ', ' ', ' ',' ', ' ', ' ', ' ',' ', ' ', ' ', ' ',' ', ' ', ' ', ' '};

enum displayee_States{displayee};

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
volatile unsigned int k = 0;
int LCD_Disp(int state){
	unsigned int  j;
	unsigned char yeet;
	switch(state){
		case displayee: state = displayee; break;
		default: state = displayee; break;
	}
	
	switch(state){
		case displayee:
			if(k >= 52) k = 0;
			LCD_ClearScreen();
			for(j = 0; j < 16; j++){
				LCD_Cursor(j);
				yeet = sent[j+k];
				LCD_WriteData(yeet);
			}
			break;
			
	}
	k++;
	return state;
}

int main(){
 	        DDRC = 0xFF; PORTC = 0x00;
		DDRD = 0xFF; PORTD = 0x00;
		static task task1;
		task *tasks[] = {&task1};
		const unsigned short numTasks = 1;//sizeof(tasks)/sizeof(task*);
		task1.state = displayee;
		task1.period = 400;
		task1.elapsedTime = task1.period;
		task1.TickFct = &LCD_Disp;
	
		TimerSet(400);
		TimerOn();
		LCD_init();
		unsigned short i;
		
        	while(1){
			for(i = 0; i < numTasks; i++){
				if(tasks[i]->elapsedTime >= tasks[i]->period){
					tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);
					tasks[i]->elapsedTime = 0;
				}
				tasks[i]->elapsedTime += 400;
			}
			
			while(!TimerFlag);
			TimerFlag = 0;
        }
		
		return 0;
}
