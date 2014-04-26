#include "nrf24_register.h"

nrf24_register::nrf24_register(){

}

void nrf24_register::setup(uint8_t csn, uint8_t ce){
  	SPI_nrf.setup();
        _CSN = csn;
        _CE = ce;
        SPI_nrf.set_pinMode(_CSN, OUTPUT);
        SPI_nrf.set_pinMode(_CE, OUTPUT);
}

void nrf24_register::setup(uint8_t csn, uint8_t ce, uint8_t irq){
  	SPI_nrf.setup();
        _CSN = csn;
        _CE = ce;
	_IRQ = irq;
        SPI_nrf.set_pinMode(_CSN, OUTPUT);
        SPI_nrf.set_pinMode(_CE, OUTPUT);
	SPI_nrf.set_pinMode(_IRQ, INPUT);
}

void nrf24_register::write_CSN(uint8_t num){
 	SPI_nrf.write_pin(_CSN, num);
 //digitalWrite(_CSN, num);
}

void nrf24_register::write_CE(uint8_t num){

 //digitalWrite(_CE, num);
 	SPI_nrf.write_pin(_CE, num);
}


uint8_t nrf24_register::read_register(uint8_t address, uint8_t *status){

 	uint8_t data_read = 0;

 	address &= 0x1F;

	 SPI_nrf.write_pin(_CSN, 0);

 	*status = SPI_nrf.spi_shift(address);
 	data_read = SPI_nrf.spi_shift(0x00);

 	SPI_nrf.write_pin(_CSN, 1);

 	return data_read;
}

uint8_t* nrf24_register::read_payload(uint8_t num_bytes, uint8_t *payload_address, uint8_t *status){

 	uint8_t command = 0x61;

 	SPI_nrf.write_pin(_CSN, 0);

 	*status = spi_shift(command);
 	for(uint8_t j=0;j<num_bytes;j++){
	 	payload_address[j] = spi_shift(0);
	}

 	SPI_nrf.write_pin(_CSN, 1);

 	return payload_address;
}


void nrf24_register::write_register(uint8_t address, uint8_t data, uint8_t *status){

 	address &= 0x1F;
 	address += 0x20;

 	SPI_nrf.write_pin(_CSN, 0);

 	*status = spi_shift(address);
  	SPI_nrf.spi_shift(data);

 	SPI_nrf.write_pin(_CSN, 1);
 
}

void nrf24_register::set_rw_address(uint8_t address, uint8_t *data, uint8_t num_bytes, uint8_t *status){

	address &= 0x1F;
 	address += 0x20;

 	SPI_nrf.write_pin(_CSN, 0);

 	*status = spi_shift(address);

 	for(uint8_t i = 0; i<num_bytes; i++){
 		SPI_nrf.spi_shift(*data++);
	}

 	SPI_nrf.write_pin(_CSN, 1);

}

uint8_t* nrf24_register::read_rw_address(uint8_t address, uint8_t *address_address, uint8_t *status){

 	address &= 0x1F;

 	SPI_nrf.write_pin(_CSN, 0);

 	*status = spi_shift(address);

 	for(uint8_t i = 0; i<5; i++){
   		address_address[i] = spi_shift(0x00);
	}

 	SPI_nrf.write_pin(_CSN, 1);

 	return address_address;
}


void nrf24_register::write_payload(uint8_t *data_write, uint8_t num_bytes, uint8_t *status){

 	uint8_t command = 0xA0;

 	SPI_nrf.write_pin(_CSN, 0);

 	*status = spi_shift(command);

 	for(uint8_t j=0;j<num_bytes;j++){
 		spi_shift(*data_write++);
	}

 	SPI_nrf.write_pin(_CSN, 1);

}

void nrf24_register::send_command(uint8_t command, uint8_t *status){

 	SPI_nrf.write_pin(_CSN, 0);

 	*status = SPI_nrf.spi_shift(command);

 	SPI_nrf.write_pin(_CSN, 1);

}

uint8_t nrf24_register::spi_shift(uint8_t data_in){

 	uint8_t data_out;

 //data_out = SPI_nrf.transfer(data_in);
 	data_out = SPI_nrf.spi_shift(data_in);

 	return data_out;
}

void nrf24_register::write_buffer(uint8_t address, uint8_t *buffer, uint8_t num_bytes, uint8_t *status){

	uint8_t i = 0;

	address &= 0x1F;
	address += 0x20;

	SPI_nrf.write_pin(_CSN, 0);

	*status = spi_shift(address);

	for(i = 0; i<num_bytes; i++){
		SPI_nrf.spi_shift(buffer[i]);
	}

	SPI_nrf.write_pin(_CSN, 1);
}

uint8_t nrf24_register::read_IRQ(void){
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
