#ifndef SPI_nrf24_h
#define SPI_nrf24_h

#include <stdint.h>

#define NRF_TRINKET 1

#if defined(NRF_RASP_PI)

#include <wiringPi.h>
#include <wiringPiSPI.h>

#elif defined(NRF_ARDUINO)

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <stdio.h>
#include <avr/pgmspace.h>
#include "pins_arduino.h"

#elif defined(NRF_TRINKET)

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#endif


class SPI_nrf24
{
public:
      	void setup(void);
	void setup(uint8_t clk, uint8_t mosi, uint8_t miso);
	void set_pinMode(uint8_t pin, uint8_t direction);
      	uint8_t spi_shift(uint8_t data_write);
	void write_pin(uint8_t pin, uint8_t val);
	uint8_t read_pin(uint8_t pin);
private:
	uint8_t CLOCK;
	uint8_t DWRITE;
	uint8_t DREAD;
};

#endif
