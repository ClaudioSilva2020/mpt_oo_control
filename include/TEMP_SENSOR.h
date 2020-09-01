#ifndef __TEMP_SENSOR
#define __TEMP_SENSOR

#include <Arduino.h>
#include <avr/io.h>
#include <util/delay.h>

unsigned int TEMP_read();

#endif

unsigned int TEMP_read()
{
    unsigned int ad_velue;
    double temp_internal;
    // Seta modo de leitura de temperatura interna
    ADMUX |= (1<<MUX0)|(1<<MUX1)|(1<<MUX2)|(1<<MUX3); 
    // Setando referencia interna 1.1v
    ADMUX |= (1<<REFS1);
    // HAbilita conversão
    ADCSRA |= (1<<ADEN);
    // Aguarda estabilização da tensão de referência
    delay(20);
    

    
    


    return temp_internal;
}