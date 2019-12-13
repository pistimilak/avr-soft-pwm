/**
 * @file main.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2019-12-07
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef F_CPU
#define F_CPU   (16000000UL)
#endif


#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/eeprom.h>
#include "eeprom_map.h"
#include "soft_pwm.h"
#include "sig.h"

#define LED_NUM     SPWM_MAX_CHANNEL_NUM
#define SIG_LENGTH  1000


void idle_hook();
void Init_EEPROM();
void Init();
sig_val_t eeprom_sig_reader(sig_t *signal);


sig_t leds[LED_NUM];

#if INIT_EEPROM
    #warning EEPROM initializing will be prepared!
    extern const sig_val_t sin_signal[512];
#endif

int main(void)
{
    Init();
    
    while(1) {
    }

    return 0;
}

void idle_hook()
{
    DDRB |= (1 << PB5);
    while(1) {
        PORTB ^= (1 << PB5);
        _delay_ms(500);
    }
}

#if INIT_EEPROM
void Init_EEPROM()
{
    uint8_t i;
    /*write signal to EEPROM*/
    for(i = 0; i < SIG_LENGTH; i++) {
        eeprom_write_byte(EEPROM_Signal + i, sin_signal[i]);
    }

    /*write LED phase offsets*/
    for(i = 0; i < LED_NUM; i++) {
        eeprom_write_byte(EEPROM_LED0_offset + i, i * 10);
    }

    eeprom_write_byte(EEPROM_SPWM_TIM8_OCR, 100);       /*write timer0 OCR*/
    eeprom_write_word(EEPROM_SIG_TIM16_OCR, 2000);      /*write timer1 OCR*/
    eeprom_write_word(EEPROM_SPWM_EN_STATE, 0xffff);    /*write enable all channe;*/
}
#endif

void Init()
{
    
    uint8_t i;
    spwm_init(eeprom_read_word(EEPROM_SPWM_EN_STATE)); // enable channels
    
    /*Init signals*/
    for(i = 0; i < LED_NUM; i++) {
        leds[i] = sig_init(sin_signal, SIG_LENGTH, i * 10, eeprom_sig_reader);
        spwm_set_ch(i, sig_get_val(&leds[i]));
    }

    /*Init Timer0 for spwm*/
    /*Prescale 8, CTC mode*/
    TCCR0A |= (1 << WGM01);
    TCCR0B |= (0 << CS02) | (0 << CS01) | (1 << CS00);
    TIMSK0 |= (1 << OCIE0A);
    OCR0A = 100;

    /*Init Timer1 for signal tracking*/
    /*Prescale 128, CTC mode*/
    /**/
    TCCR1A |= 0;
    TCCR1B |= (1 << WGM12) | (0 << CS12) | (1 << CS01) | (1 << CS10);
    TIMSK1 |= (1 << OCIE1A);
    OCR1A = 2000;
    
    /*Enable interrupts*/
    sei();
}

ISR(TIMER0_COMPA_vect)
{
    spwm_tick();
}

ISR(TIMER1_COMPA_vect)
{
    uint8_t i;
    for(i = 0; i < LED_NUM; i++) {
        spwm_set_ch(i, sig_get_val(&leds[i]));
        sig_tick(&leds[i]);
    }
}

/*implementation for reading signal from EEPROM*/
sig_val_t eeprom_sig_reader(sig_t *signal)
{
    return eeprom_read_byte((signal->pval));
}