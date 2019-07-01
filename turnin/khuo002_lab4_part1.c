nclude <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
enum LED_States { LED_Init, LED_S1, LED_S2} LED_State;

void LED_Trans() {
   switch(LED_State) { // Transitions

      case LED_Init:
         LED_State = LED_S1;
         break;

      case LED_S1:
         if(PINA == 0x01 && PORTC == 0x01) LED_State = LED_S2;
         if(PINA == 0x01 && PORTC == 0x00) LED_State = LED_S1;
         if(PINA == 0x00) LED_State = LED_S1;
         break;

      case LED_S2:
         if(PINA == 0x01 && PORTC == 0x01) LED_State = LED_S1;
         if(PINA == 0x01 && PORTC == 0x00) LED_State = LED_S2;
         if(PINA == 0X00) LED_State = LED_S2;
         break;
      default:
         LED_State = LED_Init;
   } // Transitions

   switch(LED_State) { // State actions

      case LED_Init:
         PORTC = 0x01;
         printf("LED_State: LED_Init\n");
         PORTB = 0x00;
         break;

      case LED_S1:
         if(PINA == 0x01) PORTC = 0x00;
         if(PINA == 0x00) PORTC = 0x01;
         printf("LED_State: LED_S1\n");
         PORTB = 0x01;
         break;

      case LED_S2:
         if(PINA == 0x01) PORTC = 0x00;
         if(PINA == 0x00) PORTC = 0x01;
         printf("LED_State: LED_S2\n");
         PORTB = 0x02;
         break;

      default:
         break;
   } // State actions

}

int main(void) {
        DDRA = 0x00; PORTA = 0xFF;
        DDRC = 0xFF; PORTC = 0x00;
        DDRB = 0xFF; PORTB = 0x00;
        LED_State = LED_Init;
    /* Insert your solution below */
        while (1) {
                LED_Trans();
        }
        return 1;
}
