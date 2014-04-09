#ifndef SPI_trinket_h
#define SPI_trinket_h

class SPI_trinket
{
public:
      void setup(int clk, int dwr, int dre);
      int spi_shift(int data_write);
	    void pin_write(int pin, int val);
	    
private:
      byte CLOCK;
      byte DWRITE;
      byte DREAD;
};

extern SPI_trinket SPI;

#endif
