#ifndef USART_H
#define USART_H

#define F_CPU 8000000UL // Assume uC operates at 8MHz
#define BAUD_RATE 9600
#define BAUD_PRESCALE (((F_CPU / (BAUD_RATE * 16UL))) - 1)

void initUSART(){
	UCSRB |= (1 << RXEN)  | (1 << TXEN);
	UCSRC |= (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1);
	UBRRL = BAUD_PRESCALE;
	UBRRH = (BAUD_PRESCALE >> 8);
}

unsigned char USART_IsSendReady()
{
	return (UCSRA & (1 << UDRE));
}

unsigned char USART_HasTransmitted()
{
	return (UCSRA & (1 << TXC));
}

unsigned char USART_HasReceived()
{
	return (UCSRA & (1 << RXC));
}

void USART_Flush()
{
	static unsigned char dummy;
	while ( UCSRA & (1 << RXC) ) { dummy = UDR; }
}

void USART_Send(unsigned char sendMe)
{
	while( !(UCSRA & (1 << UDRE)) );
	UDR = sendMe;
}

unsigned char USART_Receive()
{
	while ( !(UCSRA & (1 << RXC)) ); // Wait for data to be received
	return UDR; // Get and return received data from buffer
}

#endif //USART_H
