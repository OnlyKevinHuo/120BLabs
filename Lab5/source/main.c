#include <avr/io.h>
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#include "io.h"
#endif

int main(void){
	DDRC = 0xFF; PORTC = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
	unsigned char yeet = 'i';
	LCD_init();
	LCD_Cursor(1);
	LCD_WriteData(yeet);
	while(1){continue;}
}
