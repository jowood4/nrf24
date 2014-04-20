#ifndef NRF24_REGISTER_H
#define NRF24_REGISTER_H

#define NRF_RASP_PI 1

#if defined(NRF_TRINKET)
#include "SPI_trinket.h"
#elif defined(NRF_ARDUINO)
#include "SPI_arduino.h"
#elif defined(NRF_RASP_PI)
#include "SPI_rasp_pi.h"
#endif

class nrf24_register{

   public:
	nrf24_register();
	void setup(int csn, int ce);
	int read_register(int address, int *status);
	int* read_payload(int num_ints, int *payload_address, int *status);
	void write_register(int address, int data, int *status);
	void write_payload(int *data_write, int num_ints, int *status);
	void powerOFF(int *status);
	void write_CE(int num);
	void send_command(int command, int *status);
	int spi_shift(int data_in);
	void write_CSN(int num);
	void set_rw_address(int rw_address, int *address, int num_ints, int *status);
	void write_buffer(int address, int *buffer, int num_bytes, int *status);
	int* read_rw_address(int rw_address, int *address_address, int *status);
	int read_IRQ(void);

   private:
		
	#if defined(NRF_TRINKET)
		SPI_trinket SPI_nrf;
	#elif defined(NRF_ARDUINO)
		SPI_arduino SPI_nrf;
        #elif defined(NRF_RASP_PI)
               SPI_rasp_pi SPI_nrf;
	#endif
   
    	int _CE;
    	int _CSN;
    	int _CLK;    
    	int _MOSI;
    	int _MISO;
	int _IRQ;
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
	
		
