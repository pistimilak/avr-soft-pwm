#ifndef __SOFT_PWM_H__
#define __SOFT_PWM_H__


#include <avr/io.h>
#include <inttypes.h>
#include "soft_pwm_config.h"

/*Channel IDs*/
#define SPWM_CH0_ID              0
#define SPWM_CH1_ID              1
#define SPWM_CH2_ID              2
#define SPWM_CH3_ID              3
#define SPWM_CH4_ID              4
#define SPWM_CH5_ID              5
#define SPWM_CH6_ID              6
#define SPWM_CH7_ID              7
#define SPWM_CH8_ID              8
#define SPWM_CH9_ID              9
#define SPWM_CH10_ID             10
#define SPWM_CH11_ID             11
#define SPWM_CH12_ID             12
#define SPWM_CH13_ID             13
#define SPWM_CH14_ID             14
#define SPWM_CH15_ID             15


#define __IS_PORT_USED(port)        (((SPWM_CHO_PORT ) == (port)) || ((SPWM_CH1_PORT ) == (port)) || \
                                     ((SPWM_CH2_PORT ) == (port)) || ((SPWM_CH3_PORT ) == (port)) || \
                                     ((SPWM_CH4_PORT ) == (port)) || ((SPWM_CH5_PORT ) == (port)) || \
                                     ((SPWM_CH6_PORT ) == (port)) || ((SPWM_CH7_PORT ) == (port)) || \
                                     ((SPWM_CH8_PORT ) == (port)) || ((SPWM_CH9_PORT ) == (port)) || \
                                     ((SPWM_CH10_PORT) == (port)) || ((SPWM_CH11_PORT) == (port)) || \
                                     ((SPWM_CH12_PORT) == (port)) || ((SPWM_CH13_PORT) == (port)) || \
                                     ((SPWM_CH14_PORT) == (port)) || ((SPWM_CH15_PORT) == (port)))




// #define spwm_set_en_state(state)            spwm_en_state = state
#define spwm_set_ch(id,val)                 spwm_duty_cycle_buff[id] = val

/*Check configuration*/
#if __IS_PORT_USED(PORTA)
    #warning SPWM on PORTA configured
#endif

#if __IS_PORT_USED(PORTB)
    #warning SPWM on PORTB configured
#endif

#ifdef PORTC
    #if __IS_PORT_USED(PORTC)
        #warning SPWM on PORTC configured
    #endif
#endif

#ifdef PORTD
    #if __IS_PORT_USED(PORTD)
        #warning SPWM on PORTD configured
    #endif
#endif

#ifdef PORTE
    #if __IS_PORT_USED(PORTE)
        #warning SPWM on PORTE configured
    #endif
#endif

#ifdef PORTF
    #if __IS_PORT_USED(PORTF)
        #warning SPWM on PORTF configured
    #endif
#endif

#ifdef PORTG
    #if __IS_PORT_USED(PORTG)
        #warning SPWM on PORTG configured
    #endif
#endif

#ifdef PORTH
    #if __IS_PORT_USED(PORTH)
        #warning SPWM on PORTH configured
    #endif
#endif

#if (SPWM_MODE==SPWM_MODE_NON_INVERTING)
    #warning None Inverting PWM mode activated
#elif (SPWM_MODE==SPWM_MODE_INVERTING)
    #warning Inverting PWM mode activated
#else
    #error Not correct pwm mode selected!
#endif

#if SPWM_MAX_CHANNEL_NUM != 16
    #error SPWM channel count is not correct
#endif

#if SPWM_TOP_VAL > 255 && SPWM_TOP_VAL < 65536
    uint16_t spwm_duty_cycle_buff[SPWM_MAX_CHANNEL_NUM] = {0};
#else
    uint8_t spwm_duty_cycle_buff[SPWM_MAX_CHANNEL_NUM] = {0};
#endif
extern spwm_duty_cycle_buff[SPWM_MAX_CHANNEL_NUM];

#endif