#ifndef NRF24_RADIO_H
#define NRF24_RADIO_H

#include "nrf24_register.h"

class nrf24_radio{

   public:
	nrf24_radio();
	void setup(int csn, int ce);
	int receiver_mode(int *rec_data);
	void receiver_stop(void);
	void receiver_start(void);
	void transmitter_mode(int *send_data, int num_ints);
	int get_status(void);
	int setup_retransmit(int data);
	int address_width(int data);
	int enable_RX_addr(int data);
	int auto_acknowledge(int data);
	int flush_TX_buffer(void);
	int flush_RX_buffer(void);
	int ints_received(void);
	int setup_frequency(int data);

	int *address_array;
	int intread;
	nrf24_register radio;
	int *status_address;
	int status_data;

   private:
	int data;
	int frequency;
	int retransmit;
	int use_IRQ;
	int received_ints;
	int current_FIFO;
	int sendint[32];
	int transmit_address[5];
	int *trans_add;
	int read_int;

};

#endif		
