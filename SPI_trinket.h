#ifndef SPI_trinket_h
#define SPI_trinket_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

class SPI_trinket
{
public:
      	void setup(void);
	void set_pinMode(uint8_t pin, uint8_t direction);
      	uint8_t spi_shift(uint8_t data_write);
	void write_pin(uint8_t pin, uint8_t val);
	uint8_t read_pin(uint8_t pin);
};

#endif
