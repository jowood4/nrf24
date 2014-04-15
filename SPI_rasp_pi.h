#ifndef SPI_rasp_pi_h
#define SPI_rasp_pi_h

#include <wiringPi.h>
#include <wiringPiSPI.h>

class SPI_rasp_pi
{
public:
      void setup(int csn, int ce);
      int spi_shift(int data_write);
	    void write_pin(int pin, int val);
	    int read_pin(int pin);

private:
      int _CE;
      int _CSN;
      int _CLK;    
      int _MOSI;
      int _MISO;
	    int _IRQ;
};

#endif
