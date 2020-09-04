#ifndef __EEPROM_DATA
#define __EEPROM_DATA

#include <Arduino.h>

void EEPROM_write(unsigned char ucAddress, unsigned char ucData);
unsigned char EEPROM_read(unsigned char ucAddress);

#endif

