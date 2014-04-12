#include "nrf24_register.h"

nrf24_register::nrf24_register(){

}

void nrf24_register::setup(byte csn, byte ce){
  	SPI_nrf.setup(csn, ce);
}

void nrf24_register::write_CSN(byte num){
 	SPI_nrf.write_pin(_CSN, num);
 //digitalWrite(_CSN, num);
}

void nrf24_register::write_CE(byte num){

 //digitalWrite(_CE, num);
 	SPI_nrf.write_pin(_CE, num);
}


byte nrf24_register::read_register(byte address, unsigned char *status){

 	byte data_read = 0;

 	address &= 0x1F;

	 SPI_nrf.write_pin(_CSN, 0);

 	*status = SPI_nrf.spi_shift(address);
 	data_read = SPI_nrf.spi_shift(0x00);

 	SPI_nrf.write_pin(_CSN, 1);

 	return data_read;
}

byte* nrf24_register::read_payload(byte num_bytes, byte *payload_address, byte *status){

 	byte command = 0x61;

 	SPI_nrf.write_pin(_CSN, 0);

 	*status = spi_shift(command);
 	for(int j=0;j<num_bytes;j++){
	 	payload_address[j] = spi_shift(0);
	}

 	SPI_nrf.write_pin(_CSN, 1);

 	return payload_address;
}


void nrf24_register::write_register(byte address, byte data, byte *status){

 	address &= 0x1F;
 	address += 0x20;

 	SPI_nrf.write_pin(_CSN, 0);

 	*status = spi_shift(address);
  	SPI_nrf.spi_shift(data);

 	SPI_nrf.write_pin(_CSN, 1);
 
}

void nrf24_register::set_rw_address(byte address, byte *data, byte num_bytes, byte *status){

	address &= 0x1F;
 	address += 0x20;

 	SPI_nrf.write_pin(_CSN, 0);

 	*status = spi_shift(address);

 	for(int i = 0; i<num_bytes; i++){
 		SPI_nrf.spi_shift(*data++);
	}

 	SPI_nrf.write_pin(_CSN, 1);

}

byte* nrf24_register::read_rw_address(byte address, byte *address_address, byte *status){

 	address &= 0x1F;

 	SPI_nrf.write_pin(_CSN, 0);

 	*status = spi_shift(address);

 	for(int i = 0; i<5; i++){
   		address_address[i] = spi_shift(0x00);
	}

 	SPI_nrf.write_pin(_CSN, 1);

 	return address_address;
}


void nrf24_register::write_payload(byte *data_write, byte num_bytes, byte *status){

 	byte command = 0xA0;

 	SPI_nrf.write_pin(_CSN, 0);

 	*status = spi_shift(command);

 	for(int j=0;j<num_bytes;j++){
 		spi_shift(*data_write++);
	}

 	SPI_nrf.write_pin(_CSN, 1);

}

void nrf24_register::send_command(byte command, byte *status){

 	SPI_nrf.write_pin(_CSN, 0);

 	*status = SPI_nrf.spi_shift(command);

 	SPI_nrf.write_pin(_CSN, 1);

}

byte nrf24_register::spi_shift(byte data_in){

 	byte data_out;

 //data_out = SPI_nrf.transfer(data_in);
 	data_out = SPI_nrf.spi_shift(data_in);

 	return data_out;
}

void nrf24_register::write_buffer(byte address, byte *buffer, byte num_bytes, byte *status){

	byte i = 0;

	address &= 0x1F;
	address += 0x20;

	SPI_nrf.write_pin(_CSN, 0);

	*status = spi_shift(address);

	for(i = 0; i<num_bytes; i++){
		SPI_nrf.spi_shift(buffer[i]);
	}

	SPI_nrf.write_pin(_CSN, 1);
}

byte nrf24_register::read_IRQ(void){
	return SPI_nrf.read_pin(_IRQ);
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
