#ifndef NRF24_REGISTER_H
#define NRF24_REGISTER_H

#define NRF_TRINKET 1

#if defined(NRF_TRINKET)
#include "SPI_trinket.h"
#elif defined(NRF_ARDUINO)
#include "SPI_arduino.h"
#endif

#include "Arduino.h"

class nrf24_register{

   public:
	nrf24_register();
	void setup(byte csn, byte ce);
	byte read_register(byte address, unsigned char *status);
	byte* read_payload(byte num_bytes, byte *payload_address, byte *status);
	void write_register(byte address, byte data, byte *status);
	void write_payload(byte *data_write, byte num_bytes, byte *status);
	void powerOFF(byte *status);
	void write_CE(byte num);
	void send_command(byte command, byte *status);
	byte spi_shift(byte data_in);
	void write_CSN(byte num);
	void set_rw_address(byte rw_address, byte *address, byte num_bytes, byte *status);
	void write_buffer(byte address, byte *buffer, byte num_bytes, byte *status);
	byte* read_rw_address(byte rw_address, byte *address_address, byte *status);
	byte read_IRQ(void);

   private:
		
	#if defined(NRF_TRINKET)
		SPI_trinket SPI_nrf;
	#elif defined(NRF_ARDUINO)
		SPI_arduino SPI_nrf;
	#endif
   
    	byte _CE;
    	byte _CSN;
    	byte _CLK;    
    	byte _MOSI;
    	byte _MISO;
	byte _IRQ;
};

#endif

////////////////////////////////////////////////////////
//
//State Table
//
// Receive:
//
// 1. Power ON VDD to get to Power Down state
// 2. Set PWR_UP bit in CONFIG register to get to Standby state
// 3. Set CE = 1 and PRIM_RX = 1 in CONFIG register to enter RX state
//    Stays in RX mode until CE = 0; Returns to Standby
//
//
// Transmit:
//
// 1. Power ON VDD to get to Power Down state
// 2. Set PWR_UP bit in CONFIG register to get to Standby state
// 3. Set CE = 1 and PRIM_RX = 0 to enter Standby TX state
// 4. Write to TX_FIFO
//    Stays in TX mode until TX_FIFO empty.
//    Stays in Standby TX state until CE = 0; Returns to Standby
	
		
