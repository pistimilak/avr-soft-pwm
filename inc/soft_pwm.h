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

// #define spwm_set_en_state(state)            spwm_en_state = state
#define spwm_set_ch(id,val)                 spwm_duty_cycle_buff[id] = val

#if SPWM_USE_PORT_BUFFERING
#define SPWM_PORTA_BUFF_IDX      0
#define SPWM_PORTB_BUFF_IDX      1
#define SPWM_PORTC_BUFF_IDX      2
#define SPWM_PORTD_BUFF_IDX      3
#define SPWM_PORTE_BUFF_IDX      4
#define SPWM_PORTF_BUFF_IDX      5
#define SPWM_PORTG_BUFF_IDX      6
#define SPWM_PORTH_BUFF_IDX      7
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

#if SPWM_USE_PORT_BUFFERING
    #warning Port buffering is enabled
    #if SPWM_PORTA_USED
        #warning SPWM PORTA USED
    #endif
    #if SPWM_PORTB_USED
        #warning SPWM PORTB USED
    #endif
    #if SPWM_PORTC_USED
        #warning SPWM PORTC USED
    #endif
    #if SPWM_PORTD_USED
        #warning SPWM PORTD USED
    #endif
    #if SPWM_PORTE_USED
        #warning SPWM PORTE USED
    #endif
    #if SPWM_PORTF_USED
        #warning SPWM PORTF USED
    #endif
    #if SPWM_PORTG_USED
        #warning SPWM PORTG USED
    #endif
    #if SPWM_PORTH_USED
        #warning SPWM PORTH USED
    #endif
#endif


#if SPWM_TOP_VAL > 255 && SPWM_TOP_VAL < 65536
    extern volatile uint16_t spwm_duty_cycle_buff[SPWM_MAX_CHANNEL_NUM];
#else
    extern volatile uint8_t spwm_duty_cycle_buff[SPWM_MAX_CHANNEL_NUM];
#endif
// extern spwm_duty_cycle_buff[SPWM_MAX_CHANNEL_NUM];

void spwm_init(uint16_t en_state);
void spwm_tick();

#endif