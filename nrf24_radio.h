#ifndef NRF24_RADIO_H
#define NRF24_RADIO_H

#include "nrf24_register.h"
#include "stdint.h"

class nrf24_radio{

   public:
	nrf24_radio();
	void setup(uint8_t csn, uint8_t ce);
	uint8_t receiver_mode(uint8_t *rec_data);
	void receiver_stop(void);
	void receiver_start(void);
	void transmitter_mode(uint8_t *send_data, uint8_t num_bytes);
	uint8_t get_status(void);
	uint8_t setup_retransmit(uint8_t data);
	uint8_t address_width(uint8_t data);
	uint8_t enable_RX_addr(uint8_t data);
	uint8_t auto_acknowledge(uint8_t data);
	uint8_t flush_TX_buffer(void);
	uint8_t flush_RX_buffer(void);
	uint8_t bytes_received(void);
	uint8_t setup_frequency(uint8_t data);
	uint8_t read_register(uint8_t register);

	uint8_t *address_array;
	uint8_t byteread;
	nrf24_register radio;
	uint8_t *status_address;
	uint8_t status_data;

   private:
	uint8_t data;
	uint8_t frequency;
	uint8_t retransmit;
	uint8_t use_IRQ;
	uint8_t received_bytes;
	uint8_t current_FIFO;
	uint8_t sendbyte[32];
	uint8_t transmit_address[5];
	uint8_t *trans_add;
	uint8_t read_byte;

};

#endif		
