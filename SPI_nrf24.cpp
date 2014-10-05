#include "SPI_nrf24.h"

#if defined(BIT_BANG)
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

#elif defined(NRF_TRINKET)

void SPI_nrf24::setup(void){
    	USICR &= ~(_BV(USISIE) | _BV(USIOIE) | _BV(USIWM1));
    	USICR |= _BV(USIWM0) | _BV(USICS1) | _BV(USICLK);
    	SPI_DDR_PORT |= _BV(USCK_DD_PIN);   //set the USCK pin as output
    	SPI_DDR_PORT |= _BV(DO_DD_PIN);     //set the DO pin as output
    	SPI_DDR_PORT &= ~_BV(DI_DD_PIN);    //set the DI pin as input
}

uint8_t SPI_nrf24::spi_shift(uint8_t data_write)
{
	USIDR = data_write;
    	USISR = _BV(USIOIF);                //clear counter and counter overflow interrupt flag
    	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) { //ensure a consistent clock period
	while ( !(USISR & _BV(USIOIF)) ) USICR |= _BV(USITC);
    	}
    	return USIDR;
}

#elif defined(NRF_ARDUINO)

void SPI_nrf24::setup(void){
  SPCR |= _BV(MSTR);
  SPCR |= _BV(SPE);

  pinMode(11, OUTPUT);
  pinMode(13, OUTPUT);
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


