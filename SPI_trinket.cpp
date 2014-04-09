#include "SPI_trinket.h"

SPI_trinket SPI;

void SPI_trinket::setup(int clk, int dwr, int dre){
  CLOCK = clk;
  DWRITE = dwr;
  DREAD = dre;
  
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
