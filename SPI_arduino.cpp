#include "SPI_arduino.h"

void SPI_arduino::setup(byte csn, byte ce){
 _CSN = csn;
 _CE = ce;

 pinMode(_CSN, OUTPUT);
 pinMode(_CE, OUTPUT);

  //SPI.begin();
  pinMode(SCK, OUTPUT);
  pinMode(MOSI, OUTPUT);
  pinMode(SS, OUTPUT);
  
  digitalWrite(SCK, LOW);
  digitalWrite(MOSI, LOW);
  digitalWrite(SS, HIGH);

  SPCR |= _BV(MSTR);
  SPCR |= _BV(SPE);
  //

 digitalWrite(_CSN, 1);
 digitalWrite(_CE, 0);
}

byte SPI_arduino::spi_shift(byte data_write)
{
  //return SPI.transfer(data_write);
  SPDR = data_write;
  while (!(SPSR & _BV(SPIF)))
    ;
  return SPDR;
}

void SPI_arduino::write_pin(byte pin, byte val){
	digitalWrite(pin, val);
}

byte SPI_arduino::read_pin(byte pin){
	return digitalRead(pin);
}
