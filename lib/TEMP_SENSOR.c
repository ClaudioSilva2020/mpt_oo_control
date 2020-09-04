#include "TEMP_SENSOR.h"
#include <Arduino.h>
#include <avr/io.h>
#include <util/delay.h>




//-------------------------Configurações Macros ------------------------------//
#define set_Bit(Reg, bit_x) (Reg|=(1<<bit_x)) //seta bit x do registrador Reg
#define clr_Bit(Reg, bit_x) (Reg&=~(1<<bit_x)) //reseta o bit
#define test_Bit(Reg, bit_x) (Reg&(1<<bit_x))  //testa o estado e retorna 1ou0
#define clp_Bit(Reg, bit_x) (Reg^=(1<<bit_x))  //troca o estado logico do bit

unsigned int TEMP_read()
{
    float of_set = 300;
    double temp_internal;
    // Seta modo de leitura de temperatura interna
    ADMUX |= (1<<MUX0)|(1<<MUX1)|(1<<MUX2)|(1<<MUX3); 
    // Setando referencia interna 1.1v
    ADMUX |= (1<<REFS1);
    // HAbilita conversão
    ADCSRA |= (1<<ADEN);
    // Aguarda estabilização da tensão de referência
    delay(20);
    // Inicia conversão
    ADCSRA |= (1<<ADSC);
    // Aguarda fim da conversão
    while (test_Bit(ADCSRA, ADSC));
    
    temp_internal = (1.22*((ADCH << 8) | ADCL)) + of_set;
    
    return temp_internal;
}