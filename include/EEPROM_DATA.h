/********************************************************************************
@file EEPROM_DATA.h
@brief arq de cabeçalho e lib firmware de leitura  e escrita na EEPROM
@author Cláudio Silva 
@date 31/08/2020
@version 1.0
*********************************************************************************/

#ifndef __EEPROM_DATA
#define __EEPROM_DATA

#include <Arduino.h>

void EEPROM_write(unsigned char ucAddress, unsigned char ucData);
unsigned char EEPROM_read(unsigned char ucAddress);




/************************************************************
*                 Função de Escrita na EEPROM               *
*************************************************************/                                                                      
void EEPROM_write(unsigned char ucAddress, unsigned char ucData)
{
    // Aguarada a ultima escrita ser completa
    while (EECR & (1<<EEPE));

    // seta o modo de programação
    EECR = (0<<EEPM1) | (0<<EEPM0);
    // Seta o endereço e o registrador de dados
    EEAR = ucAddress;
    EEDR = ucData;

    EECR |= (1<<EEMPE);
    EECR |= (1<<EEPE);
}
/**************************************************************
*                Função de Leitura da EEPROM                  *
***************************************************************/
unsigned char EEPROM_read(unsigned char ucAddress)
{
    // Aguarada a ultima escrita ser completa
    while (EECR & (1<<EEPE));
    // Seta o endereço e o registrador de dados
    EEAR = ucAddress;
    // Inicia processo de leitura de dado
    EECR |= (1<<EERE);
    // retorna o dado do registrador de dados
    return EEDR;
}

#endif