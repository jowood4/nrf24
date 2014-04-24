#include "nrf24_radio.h"

nrf24_radio::nrf24_radio(void){

}

void nrf24_radio::setup(uint8_t csn, uint8_t ce){

  radio.setup(csn, ce);
  radio.write_CE(0);
  radio.write_CSN(1);

for(uint8_t i = 0; i<32;i++)
{
  sendbyte[i] = 0xAA;
}

  status_address = &status_data;
  transmit_address[0] = 0x01;
  transmit_address[1] = 0x01;
  transmit_address[2] = 0x01;
  transmit_address[3] = 0x01;
  transmit_address[4] = 0x01;
  trans_add = transmit_address;

  radio.write_register(0x01, 0x01, status_address);
  radio.write_register(0x02, 0x01, status_address);
  radio.write_register(0x04, 0x1A, status_address);
  radio.write_register(0x05, 0x70, status_address);
  radio.write_register(0x06, 0x26, status_address);
  radio.write_register(0x11, 0x20, status_address);
  radio.set_rw_address(0x10, transmit_address, 5, status_address);
  radio.set_rw_address(0x0A, transmit_address, 5, status_address);
  
  radio.write_register(0x00, 0x00, status_address);
  radio.write_register(0x00, 0x0F, status_address);
  delay(2);

  //address_array = radio.read_rw_address(0x0A, address_array, status_address);

  radio.send_command(0xFF, status_address);
  status_data |= 0x70;
  radio.write_register(0x07, status_data, status_address);


  radio.write_payload(sendbyte, 32, status_address);

  flush_RX_buffer();
  flush_TX_buffer();

}

uint8_t nrf24_radio::read_register(uint8_t reg){
	return radio.read_register(reg, status_address);
}

void nrf24_radio::receiver_start(void){

    //clear buffers
    radio.write_CE(0);
    radio.send_command(0xE2, status_address);
    status_data |= 0x70;
    radio.write_register(0x07, status_data, status_address);

    //get in RX mode
    radio.write_register(0x00, 0x3F, status_address);
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

      //get FIFO number
      current_FIFO = 0x11;
      
      //get number of bytes received
      received_bytes = radio.read_register(current_FIFO, status_address);
      received_bytes = uint8_t(received_bytes);
      
      rec_data = radio.read_payload(32, rec_data, status_address);
      
	  radio.send_command(0xE2, status_address);
	  status_data |= 0x70;
	  radio.write_register(0x07, status_data, status_address);

      return received_bytes;
    }
    else{
	  radio.write_CE(1);
	  return uint8_t(0);
    }
}

uint8_t nrf24_radio::get_status(void){
	radio.send_command(0xFF, status_address);
	return status_data;
}

uint8_t nrf24_radio::flush_RX_buffer(void){
	radio.send_command(0xE2, status_address);
	return status_data;
}

uint8_t nrf24_radio::flush_TX_buffer(void){
	radio.send_command(0xE1, status_address);
	return status_data;
}

uint8_t nrf24_radio::auto_acknowledge(uint8_t data){
//bits 0 - 5 correspond to AA on data pipe 0 - 5
	radio.write_register(0x01, data, status_address);
	return status_data;
}

uint8_t nrf24_radio::enable_RX_addr(uint8_t data){
//bits 0 - 5 correspond to AA on data pipe 0 - 5
	radio.write_register(0x02, data, status_address);
	return status_data;
}

uint8_t nrf24_radio::address_width(uint8_t data){
//decimal 1 = 3 ints
//decimal 2 = 4 ints
//decimal 3 = 5 ints
	radio.write_register(0x03, data, status_address);
	return status_data;
}

uint8_t nrf24_radio::setup_retransmit(uint8_t data){
	radio.write_register(0x04, data, status_address);
	return status_data;
}

uint8_t nrf24_radio::setup_frequency(uint8_t data){
	radio.write_register(0x05, data, status_address);
	return status_data;
}


void nrf24_radio::transmitter_mode(uint8_t *send_data, uint8_t num_ints){
	
	//send data to buffer and put in transmit mode
	radio.write_CE(0);
      radio.write_payload(send_data, num_ints, status_address);
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

	radio.send_command(0xFF, status_address);
	status_data |= 0x70;
      radio.write_register(0x07, status_data, status_address);
      
      //flush tx buffer
      radio.send_command(0xE1, status_address);
      radio.write_register(0x07, status_data, status_address);

	radio.send_command(0xE1, status_address);
}
