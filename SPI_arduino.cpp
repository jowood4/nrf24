#include "SPI_arduino.h"

void SPI_arduino::setup(void){
  SPCR |= _BV(MSTR);
  SPCR |= _BV(SPE);
}

void SPI_arduino::set_pinMode(uint8_t pin, uint8_t direction)
{
	pinMode(pin, direction);
}

uint8_t SPI_arduino::spi_shift(uint8_t data_write)
{
  //return SPI.transfer(data_write);
  SPDR = data_write;
  while (!(SPSR & _BV(SPIF)))
    ;
  return SPDR;
}

void SPI_arduino::write_pin(uint8_t pin, uint8_t val){
	digitalWrite(pin, val);
}

uint8_t SPI_arduino::read_pin(uint8_t pin){
	return digitalRead(pin);
}
