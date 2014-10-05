#ifndef NRF24_RADIO_H
#define NRF24_RADIO_H

#define BIT_BANG 1

#include "nrf24_register.h"
#include "stdint.h"

class nrf24_radio{

   public:
	nrf24_radio();

	//Setup functions
	#if defined BIT_BANG
	void setup(uint8_t csn, uint8_t ce, uint8_t clk, uint8_t mosi, uint8_t miso);
	void setup(uint8_t csn, uint8_t ce, uint8_t clk, uint8_t mosi, uint8_t miso, uint8_t irq);
	#else
	void setup(uint8_t csn, uint8_t ce);
	void setup(uint8_t csn, uint8_t ce, uint8_t irq);
	#endif
	void init(void);

	//High level functions
	uint8_t receiver_mode(void);
	void receiver_stop(void);
	uint8_t receiver_start(void);
	uint8_t transmitter_mode(void);

	//Radio commands
	uint8_t read_register(uint8_t reg);
	uint8_t write_register(uint8_t reg, uint8_t data);
	uint8_t read_payload(uint8_t* read_buffer, uint8_t num_bytes);
	uint8_t write_payload(uint8_t* data, uint8_t num_bytes);
	uint8_t get_status(void);
	uint8_t get_pipe_numbytes(uint8_t* pipe, uint8_t* bytes);
	uint8_t flush_TX_buffer(void);
	uint8_t flush_RX_buffer(void);
	uint8_t bytes_received(void);
	uint8_t powerOFF(void);
	uint8_t powerON(void);

	//Radio settings commands
	uint8_t setup_auto_acknowledge(void);
	uint8_t setup_frequency(void);
	uint8_t setup_retransmit(void);
	uint8_t setup_addr_width(void);
	uint8_t setup_en_RX_addr(void);
	uint8_t setup_RF_param(void);
	uint8_t setup_transmit_address(void);
	uint8_t setup_receive_address(void);
	uint8_t setup_data_width(void);
	uint8_t refresh(void);

	//Simplifiy SWIG.  Hopefully get rid of these
	void write_array(uint8_t* array, uint8_t index, uint8_t data);
	uint8_t read_array(uint8_t* array, uint8_t index);

	nrf24_register radio;

	//Radio settings
	uint8_t auto_ack;
	uint8_t en_RX_addr;
	uint8_t addr_width;
	uint8_t frequency;
	uint8_t retransmit;
	uint8_t use_IRQ;
	uint8_t RF_power;
	uint8_t data_rate;
	uint8_t carrier;
	uint8_t crc_bytes;
	uint8_t crc_en;

	uint8_t tx_buffer[32];
	uint8_t rx_buffer[32];

	//FIFO addresses
	uint8_t transmit_address[5];
	uint8_t receive_address0[5];
	uint8_t receive_address1[5];
	uint8_t receive_address2[5];
	uint8_t receive_address3[5];
	uint8_t receive_address4[5];
	uint8_t receive_address5[5];
	uint8_t data_width[6];

  //private:

	//uint8_t *address_array;
	uint8_t byteread;
	uint8_t *status_address;
	uint8_t status_data;

	uint8_t read_byte;
	uint8_t data;
};

#endif
