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
#endif






int main(void)
{

#if ARDUINO_DEMO
    DDR_ARDUINO_LED |= (1 << ARDUION_LED);
    while(1) {
        PORT_ARDUINO_LED |= (1 << ARDUION_LED);
        _delay_ms(1000);
        PORT_ARDUINO_LED &= ~(1 << ARDUION_LED);
        _delay_ms(1000);
    }
#else
    spwm_en_state = 0xffff;
    spwm_init_8b();

    spwm_set_ch(0, 127);
    spwm_set_ch(1, 24);
    spwm_set_ch(2, 78);
    spwm_set_ch(3, 200);
    spwm_set_ch(4, 180);
    spwm_set_ch(5, 0);
    spwm_set_ch(6, 54);
    spwm_set_ch(7, 90);
    spwm_set_ch(8, 0);
    spwm_set_ch(9, 234);
    spwm_set_ch(10, 255);
    spwm_set_ch(11, 128);
    spwm_set_ch(12, 3);
    spwm_set_ch(14, 4);
    spwm_set_ch(15, 168);

    while(1) {
        spwm_tick_8b();
    }
#endif

    return 0;
}