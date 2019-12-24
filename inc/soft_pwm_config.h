/**
 * @file soft_pwm_config.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2019-12-07
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef __SOFT_PWM_CONFIG_H__
#define __SOFT_PWM_CONFIG_H__

#include <avr/io.h>


/*Top value of soft pwm counter*/
#define SPWM_TOP_VAL                255


/*Type of pwm, it can be INVERTING or NON_INVERTING*/
/*Do not modify*/
#define SPWM_MODE_INVERTING         0
#define SPWM_MODE_NON_INVERTING     1

/*Here you can select the mode (inverting or non inverting)*/
#define SPWM_MODE                   SPWM_MODE_NON_INVERTING

/*
Port buffering:
Collecting all modification for particular port and write each modification in one step.
A little bit slower then not buffering
*/
#define SPWM_USE_PORT_BUFFERING     0

/*Select manualy the configured ports to buffering*/
#if SPWM_USE_PORT_BUFFERING
    #define SPWM_MAX_PORT_NUM       8
    #define SPWM_PORTA_USED         0
    #define SPWM_PORTB_USED         1
    #define SPWM_PORTC_USED         1
    #define SPWM_PORTD_USED         1
    #define SPWM_PORTE_USED         0
    #define SPWM_PORTF_USED         0
    #define SPWM_PORTG_USED         0
    #define SPWM_PORTH_USED         0
#endif

/*Max channel number*/
/*Do not modify*/
#define SPWM_MAX_CHANNEL_NUM        16


/*Output configuration*/
// CH0
#define SPWM_CH0                 PD2
#define SPWM_CH0_DDR             DDRD
#define SPWM_CH0_PORT            PORTD
// CH1
#define SPWM_CH1                 PD3
#define SPWM_CH1_DDR             DDRD
#define SPWM_CH1_PORT            PORTD
// CH2
#define SPWM_CH2                 PD4
#define SPWM_CH2_DDR             DDRD
#define SPWM_CH2_PORT            PORTD
// CH3
#define SPWM_CH3                 PD5
#define SPWM_CH3_DDR             DDRD
#define SPWM_CH3_PORT            PORTD
// CH4
#define SPWM_CH4                 PD6
#define SPWM_CH4_DDR             DDRD
#define SPWM_CH4_PORT            PORTD
// CH5
#define SPWM_CH5                 PD7
#define SPWM_CH5_DDR             DDRD
#define SPWM_CH5_PORT            PORTD
// CH6
#define SPWM_CH6                 PB0
#define SPWM_CH6_DDR             DDRB
#define SPWM_CH6_PORT            PORTB
// CH7
#define SPWM_CH7                 PB1
#define SPWM_CH7_DDR             DDRB
#define SPWM_CH7_PORT            PORTB
// CH8
#define SPWM_CH8                 PB2
#define SPWM_CH8_DDR             DDRB
#define SPWM_CH8_PORT            PORTB
// CH9
#define SPWM_CH9                 PB3
#define SPWM_CH9_DDR             DDRB
#define SPWM_CH9_PORT            PORTB
// CH10
#define SPWM_CH10                PB4
#define SPWM_CH10_DDR            DDRB
#define SPWM_CH10_PORT           PORTB
// CH11
#define SPWM_CH11                PB5
#define SPWM_CH11_DDR            DDRB
#define SPWM_CH11_PORT           PORTB
// CH12
#define SPWM_CH12                PC0
#define SPWM_CH12_DDR            DDRC
#define SPWM_CH12_PORT           PORTC
// CH13
#define SPWM_CH13                PC1
#define SPWM_CH13_DDR            DDRC
#define SPWM_CH13_PORT           PORTC
// CH14
#define SPWM_CH14                PC2
#define SPWM_CH14_DDR            DDRC
#define SPWM_CH14_PORT           PORTC
// CH15
#define SPWM_CH15                PC3
#define SPWM_CH15_DDR            DDRC
#define SPWM_CH15_PORT           PORTC





/*End configuration*/
#endif