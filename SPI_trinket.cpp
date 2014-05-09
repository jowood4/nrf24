#include "SPI_trinket.h"

void SPI_trinket::setup(void){

}

void SPI_trinket::set_pinMode(uint8_t pin, uint8_t direction)
{
	pinMode(pin, direction);
}

uint8_t SPI_trinket::spi_shift(uint8_t data_write)
{
	uint8_t data_read = 0;
	for(uint8_t i = 0; i<8; i++)
	{
		if(bitRead(data_write,7-i)==0)
		{
			digitalWrite(DWRITE, LOW);
		}
		else
		{
			digitalWrite(DWRITE, HIGH);
		}
		bitWrite(data_read,7-i,digitalRead(DREAD));
		digitalWrite(CLOCK, HIGH);
		digitalWrite(CLOCK, LOW);
	}
	return data_read;
}

void SPI_trinket::write_pin(uint8_t pin, uint8_t val){
	digitalWrite(pin, val);
}

uint8_t SPI_trinket::read_pin(uint8_t pin){
	return digitalRead(pin);
}
