#ifndef SPI_trinket_h
#define SPI_trinket_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#define CLOCK 2
#define DWRITE 0
#define DREAD 1

class SPI_trinket
{
public:
      	void setup(byte csn, byte ce);
      	int spi_shift(int data_write);
	void write_pin(int pin, int val);
	int read_pin(int pin);
	    
private:
      	byte _CE;
      	byte _CSN;
      	byte _CLK;    
      	byte _MOSI;
      	byte _MISO;
	byte _IRQ;
};

#endif
