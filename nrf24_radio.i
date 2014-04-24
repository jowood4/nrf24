//SWIG interface file for using nrf24_radio class in Python

%module nrf24_radio
%include "cpointer.i"
//%include "typemaps.i"
//%include "stdint.i"

%{
  #include "nrf24_radio.h"
  #include "nrf24_register.h"
  #include "SPI_rasp_pi.h"
%}

%apply unsigned char { uint8_t };
 
 // Parse the original header file
 %include "nrf24_radio.h"
 %include "nrf24_register.h"
 %include "SPI_rasp_pi.h"

