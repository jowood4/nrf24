#include "SPI_nrf24.h"

#if defined(NRF_TRINKET)

void SPI_nrf24::setup(void){

}

void SPI_nrf24::setup(uint8_t clk, uint8_t mosi, uint8_t miso){
	CLOCK = clk;
	DWRITE = mosi;
	DREAD = miso;
}

uint8_t SPI_nrf24::spi_shift(uint8_t data_write)
{
	uint8_t data_read = 0;
	for(uint8_t i = 0; i<8; i++)
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

#elif defined(NRF_ARDUINO)

void SPI_nrf24::setup(void){
  SPCR |= _BV(MSTR);
  SPCR |= _BV(SPE);
}

uint8_t SPI_nrf24::spi_shift(uint8_t data_write)
{
  //return SPI.transfer(data_write);
  SPDR = data_write;
  while (!(SPSR & _BV(SPIF)))
    ;
  return SPDR;
}

#elif defined(NRF_RASP_PI)

void SPI_nrf24::setup(void){
	wiringPiSetup();
	wiringPiSPISetup(0, 500000);
}

uint8_t SPI_nrf24::spi_shift(uint8_t data_write){
	unsigned char* data_buffer = &data_write;
	wiringPiSPIDataRW(0,data_buffer,1);
        return *data_buffer;
}

#endif

void SPI_nrf24::set_pinMode(uint8_t pin, uint8_t direction){
    pinMode(pin, direction);
}

void SPI_nrf24::write_pin(uint8_t pin, uint8_t val){
	digitalWrite(pin, val);
}

uint8_t SPI_nrf24::read_pin(uint8_t pin){
	return digitalRead(pin);
}


