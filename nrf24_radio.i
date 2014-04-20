//SWIG interface file for using nrf24_radio class in Python

%module nrf24_radio
%include "cpointer.i"
%include "typemaps.i"

%{
  #include "nrf24_radio.h"
  #include "nrf24_register.h"
  #include "SPI_rasp_pi.h"
%}
 
 // Parse the original header file
 %include "nrf24_radio.h"
 %include "nrf24_register.h"
 %include "SPI_rasp_pi.h"

