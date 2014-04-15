#ifndef SPI_arduino_h
#define SPI_arduino_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <stdio.h>
#include <avr/pgmspace.h>
#include "pins_arduino.h"

class SPI_arduino
{
public:
      void setup(byte csn, byte ce);
      byte spi_shift(byte data_write);
	    void write_pin(byte pin, byte val);
	    byte read_pin(byte pin);
	    
private:
      byte _CE;
      byte _CSN;
      byte _CLK;    
      byte _MOSI;
      byte _MISO;
	    byte _IRQ;
};

#endif
