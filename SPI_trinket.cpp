#include "SPI_trinket.h"

void SPI_trinket::setup(byte csn, byte ce){
 
  	_CSN = csn;
  	_CE = ce;
  
  	pinMode(_CSN, OUTPUT);
	pinMode(_CE, OUTPUT);
  
	pinMode(CLOCK, OUTPUT);
	pinMode(DWRITE, OUTPUT);
	pinMode(DREAD, INPUT);

	digitalWrite(CLOCK, LOW);
	digitalWrite(DWRITE, LOW);
}

int SPI_trinket::spi_shift(int data_write)
{
	int data_read = 0;
	for(int i = 0; i<8; i++)
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

void SPI_trinket::write_pin(int pin, int val){
	digitalWrite(pin, val);
}

int SPI_trinket::read_pin(int pin){
	return digitalRead(pin);
}
