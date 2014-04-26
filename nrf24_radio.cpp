#include "nrf24_radio.h"

nrf24_radio::nrf24_radio(void){
	auto_ack = 0x01;
	en_RX_addr = 0x01;
	addr_width = 5;
	retransmit = 0x1A;
	frequency = 0x70;
	RF_power = 0;
	data_rate = 0;
	carrier = 0;
	use_IRQ = 0;

	status_address = &status_data;

	for(int i = 0; i < addr_width; i++){
		transmit_address[i] = 0x01;
		receive_address0[i] = 0x01;
		receive_address1[i] = 0x01;
		receive_address2[i] = 0x01;
		receive_address3[i] = 0x01;
		receive_address4[i] = 0x01;
		receive_address5[i] = 0x01;
	}
}

uint8_t nrf24_radio::refresh(void){

  //radio.write_register(0x01, 0x01, status_address); //auto_ack
  //radio.write_register(0x02, 0x01, status_address); //en_RX_addr
  //radio.write_register(0x04, 0x1A, status_address); //retransmit
  //radio.write_register(0x05, 0x70, status_address); //frequency
  //radio.write_register(0x06, 0x26, status_address); //rf_param
  //radio.write_register(0x11, 0x20, status_address); //??

	setup_auto_acknowledge();
	setup_frequency();
	setup_retransmit();
	setup_addr_width();
	setup_en_RX_addr();
	setup_RF_param();
	setup_transmit_address();
	setup_receive_address();
}


uint8_t nrf24_radio::powerOFF(void){
	data = read_register(0x00);
    	radio.write_register(0x00, data&0xFE, status_address);
	return status_data;
}

uint8_t nrf24_radio::powerON(void){
	data = read_register(0x00);
    	radio.write_register(0x00, data|0x01, status_address);
	return status_data;
}

uint8_t nrf24_radio::write_payload(uint8_t* data, uint8_t num_bytes){
	radio.write_payload(data, num_bytes, status_address);
	return status_data;
}

uint8_t nrf24_radio::write_register(uint8_t reg, uint8_t data){
	radio.write_register(reg, data, status_address);
	return status_data;
}

uint8_t nrf24_radio::read_payload(uint8_t* read_buffer, uint8_t num_bytes){
	read_buffer = radio.read_payload(num_bytes, read_buffer, status_address);
	return status_data;
}

void nrf24_radio::setup(uint8_t csn, uint8_t ce){

	radio.setup(csn, ce);
	radio.write_CE(0);
  	radio.write_CSN(1);

	for(uint8_t i = 0; i<32;i++)
	{
  		sendbyte[i] = 0xAA;
	}

	powerOFF();
	refresh();

  	flush_RX_buffer();
  	flush_TX_buffer();

  	powerON();
  	delay(2);

	//address_array = radio.read_rw_address(0x0A, address_array, status_address);

	radio.write_payload(sendbyte, 32, status_address);
}

void nrf24_radio::setup(uint8_t csn, uint8_t ce, uint8_t irq){

	radio.setup(csn, ce, irq);
	radio.write_CE(0);
  	radio.write_CSN(1);

	for(uint8_t i = 0; i<32;i++)
	{
  		sendbyte[i] = 0xAA;
	}

	powerOFF();
	refresh();

  	flush_RX_buffer();
  	flush_TX_buffer();

  	powerON();
  	delay(2);

	radio.write_payload(sendbyte, 32, status_address);
}

uint8_t nrf24_radio::read_register(uint8_t reg){
	return radio.read_register(reg, status_address);
}

void nrf24_radio::receiver_start(void){

    	//clear buffers
    	radio.write_CE(0);
	flush_RX_buffer();

    	//get in RX mode
    	powerON();
    	radio.write_CE(1);
    	delay(200);
}

void nrf24_radio::receiver_stop(void){
	radio.write_CE(0);
}

uint8_t nrf24_radio::bytes_received(void){
	if(use_IRQ){
		return radio.read_IRQ();
	}
	else{
		get_status();
		if((status_data & 0x20) > 0){
			return 1;
		}
		else{
			return 0;
		}
	}
}

uint8_t nrf24_radio::receiver_mode(uint8_t *rec_data){

	if(bytes_received()){

		uint8_t pipe;
		uint8_t bytes;
		get_pipe_numbytes(&pipe, &bytes);
      
      		read_payload(rec_data, bytes);
      
		flush_RX_buffer();

	      	return status_data;
	}
	else{
		radio.write_CE(1);
	  	return uint8_t(0);
    	}
}

uint8_t nrf24_radio::get_pipe_numbytes(uint8_t* pipe, uint8_t* bytes){
	get_status();
	*pipe = (status_data & 0x0E)/2;

	*bytes = radio.read_register(*pipe, status_address);
	return status_data;
}

void nrf24_radio::transmitter_mode(uint8_t *send_data, uint8_t num_bytes){
	
	//send data to buffer and put in transmit mode
	radio.write_CE(0);
	write_payload(send_data, num_bytes);
	radio.write_register(0x00, 0x4E, status_address);
	radio.write_CE(1);
	delay(50);

	//radio.send_command(0xFF, status_address);
	//while(bitRead(status_data,5) == 0)
	//{
	//	radio.send_command(0xFF, status_address);
	//	delay(5);
	//}

	radio.write_CE(0);	
	flush_TX_buffer();
}

uint8_t nrf24_radio::get_status(void){
	radio.send_command(0xFF, status_address);
	return status_data;
}

uint8_t nrf24_radio::flush_RX_buffer(void){
	radio.send_command(0xE2, status_address);
	status_data |= 0x40;
	radio.write_register(0x07, status_data, status_address);
	return status_data;
}

uint8_t nrf24_radio::flush_TX_buffer(void){
	radio.send_command(0xE1, status_address);
	status_data |= 0x30;
	radio.write_register(0x07, status_data, status_address);
	return status_data;
}


uint8_t nrf24_radio::setup_auto_acknowledge(void){
//bits 0 - 5 correspond to AA on data pipe 0 - 5
	radio.write_register(0x01, auto_ack, status_address);
	return status_data;
}

uint8_t nrf24_radio::setup_en_RX_addr(void){
//bits 0 - 5 correspond to AA on data pipe 0 - 5
	radio.write_register(0x02, en_RX_addr, status_address);
	return status_data;
}

uint8_t nrf24_radio::setup_addr_width(void){
//decimal 1 = 3 bytes
//decimal 2 = 4 bytes
//decimal 3 = 5 bytes
	radio.write_register(0x03, addr_width-2, status_address);
	return status_data;
}

uint8_t nrf24_radio::setup_retransmit(void){
	radio.write_register(0x04, retransmit, status_address);
	return status_data;
}

uint8_t nrf24_radio::setup_frequency(void){
	radio.write_register(0x05, frequency, status_address);
	return status_data;
}

uint8_t nrf24_radio::setup_RF_param(void){

	uint8_t data = 0;

	if((carrier != 0)&&(carrier != 1))
	{
		carrier = 0;
	}
	data = data + carrier*0x80;

	if((RF_power < 0)||(RF_power > 3))
	{
		RF_power = 0;
	}
	data = data + RF_power*0x02;

	switch(data_rate){
		case 0: //250kbps
			data = data + 0x20;
		case 1: //1Mbps
		case 2: //2Mbps
			data = data + 0x08;
		default:
			data_rate = 0;
			data = data + 0x20;
	}

	radio.write_register(0x06, data, status_address);
	return status_data;
}

uint8_t nrf24_radio::setup_transmit_address(void){
	radio.set_rw_address(0x10, transmit_address, addr_width, status_address);
	return status_data;
}

uint8_t nrf24_radio::setup_receive_address(void){
	radio.set_rw_address(0x0A, receive_address0, addr_width, status_address);
	radio.set_rw_address(0x0B, receive_address1, addr_width, status_address);
	radio.set_rw_address(0x0C, receive_address2, addr_width, status_address);
	radio.set_rw_address(0x0D, receive_address3, addr_width, status_address);
	radio.set_rw_address(0x0E, receive_address4, addr_width, status_address);
	radio.set_rw_address(0x0F, receive_address5, addr_width, status_address);
	return status_data;
}

void nrf24_radio::write_array(uint8_t* array, uint8_t index, uint8_t data){
	array[index] = data;
}
	
uint8_t nrf24_radio::read_array(uint8_t* array, uint8_t index){
	return array[index];
}


