#define FOSC 16000000UL
#define BAUD 9600
#define UBRR_VAL FOSC/16/BAUD-1

#include <avr/io.h>

void usart_init(unsigned int ubrr);
void usart_transmit(unsigned char data);
unsigned char usart_receive();
int main(void)
{
	usart_init(UBRR_VAL);
	while(1){
	unsigned char data = usart_receive();
	usart_transmit(data);


	}
	return 0;
}
void usart_init(unsigned int ubrr)
{
	UBRR0H = (unsigned char) (ubrr >> 8);
	UBRR0L = (unsigned char)ubrr;
	UCSR0B = (1<<RXEN0) | (1<<TXEN0);
	UCSR0C |= (1<<5) | (0x3 << 1);
}

void usart_transmit(unsigned char data)
{
	while(!(UCSR0A & (1<<UDRE0)));
	UDR0 = data;
	
}

unsigned char usart_receive()
{
	while(!(UCSR0A & (1<<RXC0)));
	return UDR0;
}
