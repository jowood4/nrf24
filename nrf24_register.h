#ifndef NRF24_REGISTER_H
#define NRF24_REGISTER_H

#include "stdint.h"

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
	void setup(uint8_t csn, uint8_t ce);
	void setup(uint8_t csn, uint8_t ce, uint8_t irq);
	uint8_t read_register(uint8_t address, uint8_t *status);
	uint8_t* read_payload(uint8_t num_bytes, uint8_t *payload_address, uint8_t *status);
	void write_register(uint8_t address, uint8_t data, uint8_t *status);
	void write_payload(uint8_t *data_write, uint8_t num_bytes, uint8_t *status);
	void powerOFF(uint8_t *status);
	void write_CE(uint8_t num);
	void send_command(uint8_t command, uint8_t *status);
	uint8_t spi_shift(uint8_t data_in);
	void write_CSN(uint8_t num);
	void set_rw_address(uint8_t rw_address, uint8_t *address, uint8_t num_ints, uint8_t *status);
	void write_buffer(uint8_t address, uint8_t *buffer, uint8_t num_bytes, uint8_t *status);
	uint8_t* read_rw_address(uint8_t rw_address, uint8_t *address_address, uint8_t *status);
	uint8_t read_IRQ(void);

   private:
		
	#if defined(NRF_TRINKET)
		SPI_trinket SPI_nrf;
	#elif defined(NRF_ARDUINO)
		SPI_arduino SPI_nrf;
        #elif defined(NRF_RASP_PI)
               SPI_rasp_pi SPI_nrf;
	#endif
   
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
	
		
