#define F_CPU 16000000UL

#include <avr/io.h>

void i2c_init()
{
    
    TWSR = 0x00;
    TWBR = 72;
}

void i2c_start()
{
    TWCR = (1<<7) | (1<<5) | (1<<2);

    while(!(TWCR & (1<<7)));
}

void i2c_write(unsigned char data)
{
    TWDR = data;

    TWCR = (1<<7) | (1<<2);

    while(!(TWCR & (1<<7)));
}

void i2c_stop()
{
    TWCR = (1<<7) | (1<<4) | (1<<2);
}

int main()
{
    i2c_init();

    while(1)
    {
        i2c_start();

        i2c_write(0x40);

        i2c_write(0xAA);

        i2c_stop();

        while(1);
    }
}
