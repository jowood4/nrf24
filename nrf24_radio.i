//SWIG interface file for using nrf24_radio class in Python

%module nrf24_radio
%include "cpointer.i"
//%include "typemaps.i"
//%include "stdint.i"

%apply unsigned char { uint8_t };

%{
  #include "nrf24_radio.h"
  #include "nrf24_register.h"
  #include "SPI_nrf24.h"
%}
 
 // Parse the original header file
 %include "nrf24_radio.h"
 %include "nrf24_register.h"
 %include "SPI_nrf24.h"

