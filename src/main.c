/**
 * @file main.c
 * @author Istvan Milak (istvan.milak@gmail.com)
 * @brief AVR soft pwm solution for 16 channels. Signal stored in the EEPROM, tracked by timer interrupt
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
#define BUFF_SIZE   500



void idle_hook();
void Init_EEPROM();
void Init();

sig_val_t eeprom_sig_reader(sig_t *signal);
sig_t leds[LED_NUM];

/*Initializing EEPROM by internal software*/
#ifdef INIT_EEPROM
    #warning EEPROM initializing will be prepared!
    extern volatile const sig_val_t sin_signal[1000];
#endif

int main(void)
{

#ifdef INIT_EEPROM
    Init_EEPROM();
#endif
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

#ifdef INIT_EEPROM
/**
 * @brief Init EEPROM with default values, for this use "make INIT_EEPROM=1 command"
 * 
 */
void Init_EEPROM()
{
    uint16_t i;
    /*write signal to EEPROM*/
    for(i = 0; i < SIG_LENGTH; i++) {
        eeprom_write_byte((uint8_t *)(EEPROM_Signal + i), sin_signal[i]);
    }

    /*write LED phase offsets*/
    for(i = 0; i < LED_NUM; i++) {
        eeprom_write_byte((uint8_t *)(EEPROM_LED0_offset + i), i * 10);
    }

    eeprom_write_word((uint16_t *)EEPROM_SIG_TIM16_OCR, 2000);      /*write timer1 OCR*/
    eeprom_write_word((uint16_t *)EEPROM_SPWM_EN_STATE, 0xffff);    /*write enable all channe;*/
}
#endif

void Init()
{
    
    uint8_t i;


    spwm_init(eeprom_read_word(EEPROM_SPWM_EN_STATE)); // enable channels
    
    /*Init signals*/
    for(i = 0; i < LED_NUM; i++) {
        leds[i] = sig_init((sig_val_t *)EEPROM_Signal, SIG_LENGTH, 
                            eeprom_read_byte(EEPROM_LED0_offset + i));
    }

    /*Init Timer0 for spwm*/
    /*Prescale 8, CTC mode*/
    TCCR0A |= (1 << WGM01);
    TCCR0B |= (0 << CS02) | (1 << CS01) | (0 << CS00);
    TIMSK0 |= (1 << OCIE0A);
    OCR0A = 1;

    /*Init Timer1 for signal tracking*/
    /*Prescale 8, CTC mode*/
    TCCR1A |= 0;
    TCCR1B |= (1 << WGM12) | (0 << CS12) | (1 << CS01) | (0 << CS10);
    TIMSK1 |= (1 << OCIE1A);
    OCR1A = eeprom_read_word(EEPROM_SIG_TIM16_OCR);
    /*Enable interrupts*/
    sei();
}

/*Timer interrupt service routin for soft pwm*/
ISR(TIMER0_COMPA_vect)
{
    spwm_tick();
}

/*Timer interrupt service routin fr signal tracking*/
ISR(TIMER1_COMPA_vect)
{
    uint8_t i;
    for(i = 0; i < LED_NUM; i++) {
        spwm_set_ch(i, eeprom_sig_reader(&leds[i]));
        sig_tick(&leds[i]);
    }
}

/**
 * @brief implementation for reading signal from EEPROM*
 * 
 * @param signal signal handler pointer
 * @return sig_val_t pointed value from EEPROM
 */
sig_val_t eeprom_sig_reader(sig_t *signal)
{
    return eeprom_read_byte(signal->pval);
}