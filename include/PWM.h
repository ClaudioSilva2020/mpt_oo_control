/********************************************************************************
@file PWM.h
@brief arq de cabeçalho e lib firmware de PWM para contrle do cooler
@author Cláudio Silva 
@date 31/08/2020
@version 1.0
*********************************************************************************/

#ifndef __PWM_CONF
#define __PWM_CONF

#include <Arduino.h>
#include <avr/io.h>
#include <util/delay.h>
#include "TEMP_SENSOR.h"

//---------------Protótipos----------------------//
void PWM_conf();
void PWM_alter_rate(unsigned int rate);


/************************************************************
*-------------Função de Configuração do PWM-----------------*
*Neste caso temos o PWM setado no modo rápido sem prescaling*
*O pino de saída referente ao PWM é o PB0 que é referenciado*
*Pelo registrador OC0A                                      *
************************************************************/
void PWM_conf()
{
    //-------Gonfigurado PWM no modo rápido com o TOP=0xFF e atualização no OCRX no BOTTOM-----
    TCCR0A |= (1<<WGM00) | (1<<WGM01);
    //-------lIMPA OC0A na comparação e seta OC0A no BOTTOM (non-inverting mode)---------------
    TCCR0A |= (1<<COM0A1);
    //-------Setado PWM sem prescaling
    TCCR0B |= (1<<CS00);
}

void PWM_alter_rate(unsigned int rate)
{
    OCR0A = rate;
}
#endif
