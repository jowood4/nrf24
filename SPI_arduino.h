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
      	void setup(void);
	void set_pinMode(uint8_t pin, uint8_t direction);
      	uint8_t spi_shift(uint8_t data_write);
	void write_pin(uint8_t pin, uint8_t val);
	uint8_t read_pin(uint8_t pin);
};

#endif
