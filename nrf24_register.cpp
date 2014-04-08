
#include "nrf24L01_trinket.h"
#include <SPI_trinket.h>

nrf24L01_trinket::nrf24L01_trinket(){

}

void nrf24L01_trinket::setup(byte csn, byte ce){

 _CSN = csn;
 _CE = ce;

 pinMode(_CSN, OUTPUT);
 pinMode(_CE, OUTPUT);

 SPI.begin();

 digitalWrite(_CSN, 1);
 digitalWrite(_CE, 0);
}

void nrf24L01_trinket::write_CSN(byte num){

 digitalWrite(_CSN, num);
}

void nrf24L01_trinket::write_CE(byte num){

 digitalWrite(_CE, num);
}


byte nrf24L01_trinket::read_register(byte address, unsigned char *status){

 byte data_read = 0;

 address &= 0x1F;

 digitalWrite(_CSN, LOW);

 *status = spi_shift(address);
 data_read = spi_shift(0x00);

 digitalWrite(_CSN, HIGH);

 return data_read;
}

byte* nrf24L01_trinket::read_payload(byte num_bytes, byte *payload_address, byte *status){

 byte command = 0x61;

 digitalWrite(_CSN, LOW);

 *status = spi_shift(command);
 for(int j=0;j<num_bytes;j++){
	 payload_address[j] = spi_shift(0);
}

 digitalWrite(_CSN, HIGH);

 return payload_address;
}


void nrf24L01_trinket::write_register(byte address, byte data, byte *status){

 address &= 0x1F;
 address += 0x20;

 digitalWrite(_CSN, LOW);

 *status = spi_shift(address);
  spi_shift(data);

 digitalWrite(_CSN, HIGH);
 

}

void nrf24L01_trinket::set_rw_address(byte address, byte *data, byte num_bytes, byte *status){

 address &= 0x1F;
 address += 0x20;

 digitalWrite(_CSN, LOW);

 *status = spi_shift(address);

 for(int i = 0; i<num_bytes; i++){
 spi_shift(*data++);
}

 digitalWrite(_CSN, HIGH);

}

byte* nrf24L01_trinket::read_rw_address(byte address, byte *address_address, byte *status){

 byte data_read = 0;

 address &= 0x1F;

 digitalWrite(_CSN, LOW);

 *status = spi_shift(address);

 for(int i = 0; i<5; i++){
   address_address[i] = spi_shift(0x00);
}

 digitalWrite(_CSN, HIGH);

 return address_address;
}


void nrf24L01_trinket::write_payload(byte *data_write, byte num_bytes, byte *status){

 byte command = 0xA0;

 digitalWrite(_CSN, LOW);

 *status = spi_shift(command);

 for(int j=0;j<num_bytes;j++){
 spi_shift(*data_write++);
}

 digitalWrite(_CSN, HIGH);

}

void nrf24L01_trinket::send_command(byte command, byte *status){

 digitalWrite(_CSN, LOW);

 *status = spi_shift(command);

 digitalWrite(_CSN, HIGH);

}

byte nrf24L01_trinket::spi_shift(byte data_in){

 byte data_out;

 //data_out = SPI.transfer(data_in);
 data_out = SPI.spi_shift(data_in);

 return data_out;
}

void nrf24L01_trinket::write_buffer(byte address, byte *buffer, byte num_bytes, byte *status){

	byte i = 0;

	address &= 0x1F;
	address += 0x20;

	digitalWrite(_CSN, LOW);

	*status = spi_shift(address);

	for(i = 0; i<num_bytes; i++){
		spi_shift(buffer[i]);
	}

	digitalWrite(_CSN, HIGH);
}

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
