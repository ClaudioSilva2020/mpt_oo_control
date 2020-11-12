/********************************************************************************
@file TEMP_SENSOR.h
@brief arq de cabeçalho e lib firmware parte do sensor de temperatura
@author Cláudio Silva 
@date 31/08/2020
@version 1.0
*********************************************************************************/

#ifndef __TEMP_SENSOR
#define __TEMP_SENSOR

#include <Arduino.h>
#include <avr/io.h>
#include <util/delay.h>


//-------------------------Configurações Macros ------------------------------//
#define set_Bit(Reg, bit_x) (Reg|=(1<<bit_x)) //seta bit x do registrador Reg
#define clr_Bit(Reg, bit_x) (Reg&=~(1<<bit_x)) //reseta o bit
#define test_Bit(Reg, bit_x) (Reg&(1<<bit_x))  //testa o estado e retorna 1ou0
#define clp_Bit(Reg, bit_x) (Reg^=(1<<bit_x))  //troca o estado logico do bit

void TEMP_read_init();
unsigned int TEMP_read();

void TEMP_read_init()
{
    ADCSRA &= ~(_BV(ADATE) |_BV(ADIE)); // Clear auto trigger and interrupt enable
    ADCSRA |= _BV(ADEN);                // Enable AD and start conversion
    ADMUX = 0xF | _BV( REFS1 );         // ADC4 (Temp Sensor) and Ref voltage = 1.1V;
    delay(10);                         // Settling time min 1 ms, take 100 ms
}

unsigned int TEMP_read()
{
    // Seta modo de leitura de temperatura interna
    ADMUX |= (1<<MUX0)|(1<<MUX1)|(1<<MUX2)|(1<<MUX3); 
    // Setando referencia interna 1.1v
    ADMUX |= (1<<REFS1);
    // HAbilita conversão
    ADCSRA = (1<<ADPS2) | (1<<ADPS1) | (1<<ADEN);
    
    
    // Aguarda estabilização da tensão de referência
    ADCSRA |= (1<<ADEN);
    delay(20);
    
    DIDR0 |= (1<<ADC2D);
    
    // Inicia conversão
    ADCSRA |= (1<<ADSC);
    // Aguarda fim da conversão
    while (test_Bit(ADCSRA, ADSC));
    return ADC;
    ADCSRA &= ~(_BV(ADEN));
}

#endif