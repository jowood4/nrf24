#ifndef SPI_nrf24_h
#define SPI_nrf24_h

#define BIT_BANG 1

#include <stdint.h>

#if defined(NRF_RASP_PI)

#include <wiringPi.h>
#include <wiringPiSPI.h>

#else

#if defined(BIT_BANG)
#include "Arduino.h"
#endif

#if defined(NRF_ARDUINO)

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

#include <stdint.h>
#include <avr/io.h>
#include <util/atomic.h>

#define SPI_DDR_PORT DDRB
#define USCK_DD_PIN DDB2
#define DO_DD_PIN DDB1
#define DI_DD_PIN DDB0

#define SPI_MODE0 0x00
#define SPI_MODE1 0x04

#endif
#endif

class SPI_nrf24
{
public:
	#if defined(BIT_BANG)
	void setup(uint8_t clk, uint8_t mosi, uint8_t miso);
	#else
	void setup(void);
	#endif
	void set_pinMode(uint8_t pin, uint8_t direction);
      	uint8_t spi_shift(uint8_t data_write);
	void write_pin(uint8_t pin, uint8_t val);
	uint8_t read_pin(uint8_t pin);
//private:
	#if defined(BIT_BANG)
	uint8_t CLOCK;
	uint8_t DWRITE;
	uint8_t DREAD;
	#endif
};

#endif
