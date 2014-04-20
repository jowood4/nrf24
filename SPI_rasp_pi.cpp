#include "SPI_rasp_pi.h"

#define OUTPUT 1
#define INPUT 0

void SPI_rasp_pi::setup(int csn, int ce){
	wiringPiSetup();
	wiringPiSPISetup(0, 500000);
	
	pinMode(csn, OUTPUT);
	pinMode(ce, OUTPUT);
}

unsigned char SPI_rasp_pi::spi_shift(unsigned char data_write){
	unsigned char* data_buffer = &data_write;
	wiringPiSPIDataRW(0,data_buffer,1);
        return *data_buffer;
}

void SPI_rasp_pi::write_pin(int pin, int val){
	digitalWrite(pin, val);
}

int SPI_rasp_pi::read_pin(int pin){
	return digitalRead(pin);
}
