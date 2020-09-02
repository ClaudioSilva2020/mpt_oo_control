#include <stdio.h>
#include <stdlib.h>
#include <Arduino.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include "EEPROM_DATA.h"
#include "TEMP_SENSOR.h"


#define COMAND_CH PB0
#define STATE_RELAY PB2
#define ADDRESS_TON 0x00
#define ADDRESS_TOFF 0x01



// Protótipo de finção
void init_module(unsigned timer_on, unsigned timer_off);
void my_delay_ms(unsigned ms);

// timer_on tempo em nível lógico alto
// timer_off tempo em nível lógico baixo
typedef struct 
{
  int timer_on = 3;
  int timer_off = 2;
}timers_temp;

// instância do timer_temp
timers_temp timers_temp_t; 


int main()
{
  int value_on, value_off;
  // Bit 0 e 1 como saída e bit 2 e 3 como entrada
  // Pull-Up habilitado e as saída em nível lógico baixo
  DDRB |= 0x03; 
  PORTB |= 0x0C;
  value_on = EEPROM_read(ADDRESS_TON);
  value_off = EEPROM_read(ADDRESS_TOFF);

  Serial.begin(9600);

  if ((value_on) == 0xFF)
  {
    EEPROM_write(ADDRESS_TON, timers_temp_t.timer_on);
  }
  if ((value_off) == 0xFF)
  {
    EEPROM_write(ADDRESS_TOFF, timers_temp_t.timer_off);
  }
  
  
  init_module(EEPROM_read(ADDRESS_TON), EEPROM_read(ADDRESS_TOFF));
  



  while (1)
  {
    TEMP_read();
    Serial.println(TEMP_read());
  }
}

// ----------------------------------Função de inicialização----------------------------------//
void init_module(unsigned timer_on, unsigned timer_off)
{
  // Se o relé de saída estiver desacionado: manda sinal pra o comando da chave 
  // por tempo em alto (3seg) aguarda alguns segindos off e envia novamente e 
  // manda nível baixo.
  if (test_Bit(PINB, STATE_RELAY))
  {
    set_Bit(PORTB, COMAND_CH);
    my_delay_ms(timer_on*1000);
    clr_Bit(PORTB, COMAND_CH);
    my_delay_ms(timer_off*1000);
    set_Bit(PORTB, COMAND_CH);
    my_delay_ms(timer_on*1000);
    clr_Bit(PORTB, COMAND_CH);
  }
}
// -------------------------------------Delay com Parâmetros----------------------------------//
void my_delay_ms(unsigned ms)
{
  while (0 < ms)
  {
    _delay_ms(1);
    --ms;
  }
}