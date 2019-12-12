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
#include "soft_pwm.h"
#include "sig.h"

#define LED_NUM     9
#define SIG_LENGTH  512


void idle_hook();
void Init();
sig_t leds[LED_NUM];
extern const sig_val_t sin_signal[512];


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

void Init()
{
    
    uint8_t i;
    spwm_init(0x01ff); // enable channels
    
    /*Init signals*/
    for(i = 0; i < LED_NUM; i++) {
        leds[i] = sig_init(sin_signal, SIG_LENGTH, i * 10);
        spwm_set_ch(i, sig_get_val(&leds[i]));
    }

    /*Init Timer0 for spwm*/
    /*Prescale 8, CTC mode*/
    TCCR0A |= (1 << WGM01);
    TCCR0B |= (0 << CS02) | (0 << CS01) | (1 << CS00);
    TIMSK0 |= (1 << OCIE0A);
    OCR0A = 100;

    /*Init Timer1 for signal tracking*/
    TCCR1A |= 0;
    TCCR1B |= (1 << WGM12) | (0 << CS12) | (1 << CS01) | (1 << CS10); //Prescale 128, CTC mode
    TIMSK1 |= (1 << OCIE1A);
    OCR1A = 2000;
    sei();


}

ISR(TIMER0_COMPA_vect)
{
    // PORTB ^= (1 << PB5);
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