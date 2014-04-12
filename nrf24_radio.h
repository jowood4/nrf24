#ifndef NRF24_RADIO_H
#define NRF24_RADIO_H

#include "nrf24_register.h"

class nrf24_radio{

   public:
	nrf24_radio();
	void setup(byte csn, byte ce);
	byte receiver_mode(byte *rec_data);
	void receiver_stop(void);
	void receiver_start(void);
	void transmitter_mode(byte *send_data, byte num_bytes);
	byte get_status(void);
	byte setup_retransmit(byte data);
	byte address_width(byte data);
	byte enable_RX_addr(byte data);
	byte auto_acknowledge(byte data);
	byte flush_TX_buffer(void);
	byte flush_RX_buffer(void);
	byte bytes_received(void);
	byte setup_frequency(byte data);

	byte *address_array;
	byte byteread;
	nrf24_register radio;
	byte *status_address;
	byte status_data;

   private:
	byte data;
	byte frequency;
	byte retransmit;
	byte use_IRQ;
	byte received_bytes;
	byte current_FIFO;
	byte sendByte[32];
	byte transmit_address[5];
	byte *trans_add;
	byte read_byte;

};

#endif		
