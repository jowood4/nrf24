#ifndef SPI_rasp_pi_h
#define SPI_rasp_pi_h

#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <stdint.h>

class SPI_rasp_pi
{
public:
	void setup(void);
	void set_pinMode(uint8_t pin, uint8_t direction);
	uint8_t spi_shift(uint8_t data_write);
	void write_pin(uint8_t pin, uint8_t val);
	uint8_t read_pin(uint8_t pin);
};

#endif
