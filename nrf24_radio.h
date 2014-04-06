
///////////////////////////////////////////////////


/*
Arduino based NRF24L01 Header File
*/

#ifndef WIRELESS_H
#define WIRELESS_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "NRF24L01_trinket.h"

class Wireless{

   public:
	Wireless();
	void setup(byte csn, byte ce);
	byte receiver_mode(byte *rec_data);
	void receiver_stop(void);
	void receiver_start(void);
	void transmitter_mode(byte *send_data, byte num_bytes);
	byte get_status(void);
	byte *address_array;
	byte byteread;
	nrf24L01_trinket radio;
	byte *status_address;
	byte status_data;

   private:
    	
	byte data;
	byte frequency;
	byte retransmit;
	byte use_IRQ;
	byte bytes_received;
	byte current_FIFO;
	byte sendByte[32];
	byte transmit_address[5];
	byte *trans_add;
	byte read_byte;

};


#endif		
