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
#define F_CPU   16000000UL
#endif


#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


#define ARDUINO_DEMO    0

#if ARDUINO_DEMO
    #define ARDUION_LED         PB5
    #define DDR_ARDUINO_LED     DDRB
    #define PORT_ARDUINO_LED    PORTB
#else
    #include "soft_pwm.h"
    // #include "sig.h"


    // void Init();
    // volatile const uint8_t sin_signal[100] =
    // {
    // 128,136,143,151,159,167,174,182,
    // 189,196,202,209,215,220,226,231,
    // 235,239,243,246,249,251,253,254,
    // 255,255,255,254,253,251,249,246,
    // 243,239,235,231,226,220,215,209,
    // 202,196,189,182,174,167,159,151,
    // 143,136,128,119,112,104,96,88,
    // 81,73,66,59,53,46,40,35,
    // 29,24,20,16,12,9,6,4,
    // 2,1,0,0,0,1,2,4,
    // 6,9,12,16,20,24,29,35,
    // 40,46,53,59,66,73,81,88,
    // 96,104,112,119
    // };
#endif


int main(void)
{

#if ARDUINO_DEMO
    DDR_ARDUINO_LED |= (1 << ARDUION_LED);
    while(1) {
        PORT_ARDUINO_LED ^= (1 << ARDUION_LED);
        _delay_ms(1000);

    }
#else
    DDRB |= (1 << PB5);
    // spwm_init(0xffff); // enable ch2
    spwm_en_state = 0xffff;
    SPWM_CH2_DDR |= (1 << SPWM_CH2);
    if(spwm_en_state) {
        PORTB |= (1 << PB5);
        _delay_ms(1000);
        PORTB &= ~(1 << PB5);
        _delay_ms(1000);
    }

    while(1) {
        // spwm_tick();
    }

#endif

    return 0;
}
#if !ARDUINO_DEMO



// void Init()
// {
//     /*Init PWM*/
//     spwm_init(0xffff);
//     // spwm_set_ch(0, 127);
//     // spwm_set_ch(1, 24);
//     // spwm_set_ch(2, 78);
//     // spwm_set_ch(3, 200);
//     // spwm_set_ch(4, 180);
//     // spwm_set_ch(5, 128);
//     // spwm_set_ch(6, 54);
//     // spwm_set_ch(7, 90);
//     // spwm_set_ch(8, 0);
//     // spwm_set_ch(9, 234);
//     // spwm_set_ch(10, 255);
//     // spwm_set_ch(11, 128);
//     // spwm_set_ch(12, 3);
//     // spwm_set_ch(14, 4);
//     // spwm_set_ch(15, 168);
//     // DDRB |= (1 << PB5);
//     // TCCR2A = (1 << WGM21); // CTC mode
//     // TCCR2B = (1 << CS22) | (1 << CS21) | (1 << CS20); //prescale 1024
//     // OCR2A = 100;
//     // TIMSK2 = (1 << OCIE2A);
//     // sei();
//     led1 = (volatile sig_t)sig_init(sin_signal, 512, 0);
// }

// ISR(TIMER2_COMPA_vect)
// {
//     // spwm_tick();
//     PORTB ^= (1 << PB5);
// }


#endif
