#ifndef NRF24_REGISTER_H
#define NRF24_REGISTER_H

#define BIT_BANG 1

#include "stdint.h"
#include "SPI_nrf24.h"

class nrf24_register{

   public:
	nrf24_register();

	#if defined BIT_BANG
	void setup(uint8_t csn, uint8_t ce, uint8_t clk, uint8_t mosi, uint8_t miso);
	void setup(uint8_t csn, uint8_t ce, uint8_t clk, uint8_t mosi, uint8_t miso, uint8_t irq);
	#else
	void setup(uint8_t csn, uint8_t ce);
	void setup(uint8_t csn, uint8_t ce, uint8_t irq);
	#endif

	void write_register(uint8_t address, uint8_t data, uint8_t *status);
	void write_payload(uint8_t *data_write, uint8_t num_bytes, uint8_t *status);
	uint8_t read_register(uint8_t address, uint8_t *status);
	uint8_t* read_payload(uint8_t num_bytes, uint8_t *payload_address, uint8_t *status);
	void set_rw_address(uint8_t rw_address, uint8_t *address, uint8_t num_ints, uint8_t *status);
	uint8_t* read_rw_address(uint8_t rw_address, uint8_t* rw_address_ptr, uint8_t *status);

	void send_command(uint8_t command, uint8_t *status);
	uint8_t spi_shift(uint8_t data_in);	
	
	void write_buffer(uint8_t address, uint8_t *buffer, uint8_t num_bytes, uint8_t *status);
	
	void write_CE(uint8_t num);
	void write_CSN(uint8_t num);
	uint8_t read_IRQ(void);

	SPI_nrf24 SPI_nrf;

   //private:
	
   
    	uint8_t _CE;
    	uint8_t _CSN;
    	uint8_t _CLK;    
    	uint8_t _MOSI;
    	uint8_t _MISO;
	uint8_t _IRQ;
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
	
		
