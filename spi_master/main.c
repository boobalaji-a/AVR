#define FOSC 16000000UL
#define BAUD 9600
#define UBRR_VAL FOSC/16/BAUD-1

#include <avr/io.h>
#define CS PB2

void usart_init(unsigned int ubrr);
void usart_transmit(unsigned char data);

void spi_init();
unsigned char spi_write(unsigned char);

int main(void)
{
	usart_init(UBRR_VAL);
	spi_init();

	PORTB |= (1<<CS);
	for(volatile long i=0;i<10000;i++);

    PORTB &= ~(1<<CS);

    spi_write(0x03);
    spi_write(0x00);
    spi_write(0x00);
    unsigned char data;
	while(1){

	 data = spi_write(0xFF);
	usart_transmit(data);
	}
	return 0;
}
void usart_init(unsigned int ubrr)
{
	UBRR0H = (unsigned char) (ubrr >> 8);
	UBRR0L = (unsigned char)ubrr;
	UCSR0B = (1<<RXEN0) | (1<<TXEN0);
	UCSR0C |= (0x3 << 1);
}

void usart_transmit(unsigned char data)
{
	while(!(UCSR0A & (1<<UDRE0)));
	UDR0 = data;
	
}

void spi_init()
{
	DDRB |= (1<<PB3) | (1<<PB5) | (1<<CS);
	DDRB &= ~(1<<PB4);
	SPCR = (1<<SPE) | (1<<MSTR) | (1<<SPR0);
	PORTB |= (1<<CS);
}
unsigned char spi_write(unsigned char data)
{
	SPDR = data;
	 while(!(SPSR & (1<<SPIF)));
	 return SPDR;
}
