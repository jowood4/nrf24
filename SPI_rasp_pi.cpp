#include "SPI_rasp_pi.h"

void SPI_rasp_pi::setup(void){
	wiringPiSetup();
	wiringPiSPISetup(0, 500000);
}

void SPI_rasp_pi::set_pinMode(uint8_t pin, uint8_t direction){
    pinMode(pin, direction);
}

uint8_t SPI_rasp_pi::spi_shift(uint8_t data_write){
	unsigned char* data_buffer = &data_write;
	wiringPiSPIDataRW(0,data_buffer,1);
        return *data_buffer;
}

void SPI_rasp_pi::write_pin(uint8_t pin, uint8_t val){
	digitalWrite(pin, val);
}

uint8_t SPI_rasp_pi::read_pin(uint8_t pin){
	return digitalRead(pin);
}
