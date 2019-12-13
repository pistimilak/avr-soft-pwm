/**
 * @file soft_pwm.c
 * @author Istvan Milak (istvan.milak@gmail.com)
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

#include <util/delay.h>
#include "soft_pwm.h"

#if SPWM_TOP_VAL > 255 && SPWM_TOP_VAL < 65536
    volatile uint16_t spwm_duty_cycle_buff[SPWM_MAX_CHANNEL_NUM] = {0};
#else
    volatile uint8_t spwm_duty_cycle_buff[SPWM_MAX_CHANNEL_NUM] = {0};
#endif



#if SPWM_USE_PORT_BUFFERING
/*Buffering port, if used*/
/*A, B, C, D, E, F, G, H*/
volatile static uint8_t spwm_port_buff[SPWM_MAX_PORT_NUM] = {0};
#endif


volatile static uint16_t spwm_tick_cnt = 0;
volatile static uint16_t spwm_en_state = 0;

extern void idle_hook();


/**
 * @brief 
 * 
 * @param en_state 
 */
void spwm_init(uint16_t en_state)
{
    //reset values
    spwm_en_state = en_state;
    spwm_tick_cnt = 0;
    uint8_t i;

    
#if SPWM_USE_PORT_BUFFERING
    for(i = 0; i < SPWM_MAX_PORT_NUM; spwm_port_buff[i] = 0, i++);
#endif
    for(i = 0; i < SPWM_MAX_CHANNEL_NUM; spwm_duty_cycle_buff[i] = 0, i++);

    // init DDR
    if(spwm_en_state & (0x0001 << SPWM_CH0_ID)) SPWM_CH0_DDR |= (1 << SPWM_CH0);
    if(spwm_en_state & (0x0001 << SPWM_CH1_ID)) SPWM_CH1_DDR |= (1 << SPWM_CH1);
    if(spwm_en_state & (0x0001 << SPWM_CH2_ID)) SPWM_CH2_DDR |= (1 << SPWM_CH2);
    if(spwm_en_state & (0x0001 << SPWM_CH3_ID)) SPWM_CH3_DDR |= (1 << SPWM_CH3);
    if(spwm_en_state & (0x0001 << SPWM_CH4_ID)) SPWM_CH4_DDR |= (1 << SPWM_CH4);
    if(spwm_en_state & (0x0001 << SPWM_CH5_ID)) SPWM_CH5_DDR |= (1 << SPWM_CH5);
    if(spwm_en_state & (0x0001 << SPWM_CH6_ID)) SPWM_CH6_DDR |= (1 << SPWM_CH6);
    if(spwm_en_state & (0x0001 << SPWM_CH7_ID)) SPWM_CH7_DDR |= (1 << SPWM_CH7);
    if(spwm_en_state & (0x0001 << SPWM_CH8_ID)) SPWM_CH8_DDR |= (1 << SPWM_CH8);
    if(spwm_en_state & (0x0001 << SPWM_CH9_ID)) SPWM_CH9_DDR |= (1 << SPWM_CH9);
    if(spwm_en_state & (0x0001 << SPWM_CH10_ID)) SPWM_CH10_DDR |= (1 << SPWM_CH10);
    if(spwm_en_state & (0x0001 << SPWM_CH11_ID)) SPWM_CH11_DDR |= (1 << SPWM_CH11);
    if(spwm_en_state & (0x0001 << SPWM_CH12_ID)) SPWM_CH12_DDR |= (1 << SPWM_CH12);
    if(spwm_en_state & (0x0001 << SPWM_CH13_ID)) SPWM_CH13_DDR |= (1 << SPWM_CH13);
    if(spwm_en_state & (0x0001 << SPWM_CH14_ID)) SPWM_CH14_DDR |= (1 << SPWM_CH14);
    if(spwm_en_state & (0x0001 << SPWM_CH15_ID)) SPWM_CH15_DDR |= (1 << SPWM_CH15);
}

#if SPWM_USE_PORT_BUFFERING
/**
 * @brief 
 * 
 * @param uint8_t 
 * @return uint8_t* 
 */
static uint8_t* spwm_get_port_buff(volatile uint8_t *port) 
{
    switch ((uint16_t)port) {
#ifdef PORTA
        case (uint16_t)(&PORTA):
            return (uint8_t*)&spwm_port_buff[SPWM_PORTA_BUFF_IDX];
#endif
#ifdef PORTB
        case (uint16_t)(&PORTB):
            return (uint8_t*)&spwm_port_buff[SPWM_PORTB_BUFF_IDX];
#endif
#ifdef PORTC
        case (uint16_t)(&PORTC):
            return (uint8_t*)&spwm_port_buff[SPWM_PORTC_BUFF_IDX];
#endif
#ifdef PORTD
        case (uint16_t)(&PORTD):
            return (uint8_t*)&spwm_port_buff[SPWM_PORTD_BUFF_IDX];
#endif
#ifdef PORTE
        case (uint16_t)(&PORTE):
            return (uint8_t*)&spwm_port_buff[SPWM_PORTE_BUFF_IDX];
#endif
#ifdef PORTF
        case (uint16_t)(&PORTF):
            return (uint8_t*)&spwm_port_buff[SPWM_PORTF_BUFF_IDX];
#endif
#ifdef PORTG
        case (uint16_t)(&PORTG):
            return (uint8_t*)&spwm_port_buff[SPWM_PORTG_BUFF_IDX];
#endif
#ifdef PORTH
        case (uint16_t)(&PORTH):
            return (uint8_t*)&spwm_port_buff[SPWM_PORTH_BUFF_IDX];
#endif
        default:
            return (uint8_t *)0;
    }
}

/**
 * @brief 
 * 
 */
static void spwm_buffering_ports()
{
#ifdef PORTA
    #if SPWM_PORTA_USED
            spwm_port_buff[SPWM_PORTA_BUFF_IDX] = PORTA;
    #endif
#endif
#ifdef PORTB
    #if SPWM_PORTB_USED
            spwm_port_buff[SPWM_PORTB_BUFF_IDX] = PORTB;
    #endif
#endif
#ifdef PORTC
    #if SPWM_PORTC_USED
            spwm_port_buff[SPWM_PORTC_BUFF_IDX] = PORTC;
    #endif
#endif
#ifdef PORTD
    #if SPWM_PORTD_USED
            spwm_port_buff[SPWM_PORTD_BUFF_IDX] = PORTD;
    #endif
#endif
#ifdef PORTE
    #if SPWM_PORTE_USED
            spwm_port_buff[SPWM_PORTE_BUFF_IDX] = PORTE;
    #endif
#endif
#ifdef PORTF
    #if SPWM_PORTF_USED
            spwm_port_buff[SPWM_PORTF_BUFF_IDX] = PORTF;
    #endif
#endif
#ifdef PORTG
    #if SPWM_PORTG_USED
            spwm_port_buff[SPWM_PORTG_BUFF_IDX] = PORTG;
    #endif
#endif
#ifdef PORTH
    #if SPWM_PORTH_USED
            spwm_port_buff[SPWM_PORTH_BUFF_IDX] = PORTH;
    #endif
#endif
}

/**
 * @brief 
 * 
 */
static void spwm_write_ports()
{
#ifdef PORTA
    #if SPWM_PORTA_USED
            PORTA = spwm_port_buff[SPWM_PORTA_BUFF_IDX];
    #endif
#endif
#ifdef PORTB
    #if SPWM_PORTB_USED
            PORTB = spwm_port_buff[SPWM_PORTB_BUFF_IDX];
    #endif
#endif
#ifdef PORTC
    #if SPWM_PORTC_USED
            PORTC = spwm_port_buff[SPWM_PORTC_BUFF_IDX];
    #endif
#endif
#ifdef PORTD
    #if SPWM_PORTD_USED
            PORTD = spwm_port_buff[SPWM_PORTD_BUFF_IDX];
    #endif
#endif
#ifdef PORTE
    #if SPWM_PORTE_USED
            PORTE = spwm_port_buff[SPWM_PORTE_BUFF_IDX];
    #endif
#endif
#ifdef PORTF
    #if SPWM_PORTF_USED
            PORTG = spwm_port_buff[SPWM_PORTF_BUFF_IDX];
    #endif
#endif
#ifdef PORTG
    #if SPWM_PORTG_USED
            PORTG = spwm_port_buff[SPWM_PORTG_BUFF_IDX];
    #endif
#endif
#ifdef PORTH
    #if SPWM_PORTH_USED
            PORTH = spwm_port_buff[SPWM_PORTH_BUFF_IDX];
    #endif
#endif
}

#if SPWM_MODE == SPWM_MODE_NON_INVERTING
    #define __set_outp(port_buff, port, ch_outp, ch_id)        port_buff = spwm_get_port_buff(&port); \
                                                                *port_buff = ((spwm_en_state & (0x0001 << ch_id)) && (spwm_tick_cnt < spwm_duty_cycle_buff[ch_id])) ? \
                                                                (*port_buff | (1 << ch_outp)) : (*port_buff & ~(1 << ch_outp))
#else
    #define __set_outp(port_buff, port, ch_outp, ch_id)        port_buff = spwm_get_port_buff(&port); \
                                                                *port_buff = ((spwm_en_state & (0x0001 << ch_id)) && (spwm_tick_cnt > spwm_duty_cycle_buff[ch_id])) ? \
                                                                (*port_buff | (1 << ch_outp)) : (*port_buff & ~(1 << ch_outp))
#endif


void spwm_tick()
{

    uint8_t *port_buff;
    spwm_buffering_ports();
    
    __set_outp(port_buff, SPWM_CH0_PORT, SPWM_CH0, SPWM_CH0_ID);    // CH0
    __set_outp(port_buff, SPWM_CH1_PORT, SPWM_CH1, SPWM_CH1_ID);    // CH1
    __set_outp(port_buff, SPWM_CH2_PORT, SPWM_CH2, SPWM_CH2_ID);    // CH2
    __set_outp(port_buff, SPWM_CH3_PORT, SPWM_CH3, SPWM_CH3_ID);    // CH3
    __set_outp(port_buff, SPWM_CH4_PORT, SPWM_CH4, SPWM_CH4_ID);    // CH4
    __set_outp(port_buff, SPWM_CH5_PORT, SPWM_CH5, SPWM_CH5_ID);    // CH5
    __set_outp(port_buff, SPWM_CH6_PORT, SPWM_CH6, SPWM_CH6_ID);    // CH6
    __set_outp(port_buff, SPWM_CH7_PORT, SPWM_CH7, SPWM_CH7_ID);    // CH7
    __set_outp(port_buff, SPWM_CH8_PORT, SPWM_CH8, SPWM_CH8_ID);    // CH8
    __set_outp(port_buff, SPWM_CH9_PORT, SPWM_CH9, SPWM_CH9_ID);    // CH9
    __set_outp(port_buff, SPWM_CH10_PORT, SPWM_CH10, SPWM_CH10_ID); // CH10
    __set_outp(port_buff, SPWM_CH11_PORT, SPWM_CH11, SPWM_CH11_ID); // CH11
    __set_outp(port_buff, SPWM_CH12_PORT, SPWM_CH12, SPWM_CH12_ID); // CH12
    __set_outp(port_buff, SPWM_CH13_PORT, SPWM_CH13, SPWM_CH13_ID); // CH13
    __set_outp(port_buff, SPWM_CH14_PORT, SPWM_CH14, SPWM_CH14_ID); // CH14
    __set_outp(port_buff, SPWM_CH15_PORT, SPWM_CH15, SPWM_CH15_ID); // CH15
   
    spwm_write_ports();

    spwm_tick_cnt = (spwm_tick_cnt < SPWM_TOP_VAL) ? (spwm_tick_cnt + 1) : 0;
}
#else


#if SPWM_MODE == SPWM_MODE_NON_INVERTING
    
    #define __set_outp(port, ch_outp, ch_id)                   port = ((spwm_en_state & (0x0001 << ch_id)) && (spwm_tick_cnt < spwm_duty_cycle_buff[ch_id])) ? \
                                                                (port | (1 << ch_outp)) : (port & ~(1 << ch_outp))
#else
    #define __set_outp(port, ch_outp, ch_id)                   port = ((spwm_en_state & (0x0001 << ch_id)) && (spwm_tick_cnt > spwm_duty_cycle_buff[ch_id])) ? \
                                                                (port | (1 << ch_outp)) : (port & ~(1 << ch_outp))
#endif

/**
 * @brief 
 * 
 */
void spwm_tick()
{
    __set_outp(SPWM_CH0_PORT, SPWM_CH0, SPWM_CH0_ID);    // CH0
    __set_outp(SPWM_CH1_PORT, SPWM_CH1, SPWM_CH1_ID);    // CH1
    __set_outp(SPWM_CH2_PORT, SPWM_CH2, SPWM_CH2_ID);    // CH2
    __set_outp(SPWM_CH3_PORT, SPWM_CH3, SPWM_CH3_ID);    // CH3
    __set_outp(SPWM_CH4_PORT, SPWM_CH4, SPWM_CH4_ID);    // CH4
    __set_outp(SPWM_CH5_PORT, SPWM_CH5, SPWM_CH5_ID);    // CH5
    __set_outp(SPWM_CH6_PORT, SPWM_CH6, SPWM_CH6_ID);    // CH6
    __set_outp(SPWM_CH7_PORT, SPWM_CH7, SPWM_CH7_ID);    // CH7
    __set_outp(SPWM_CH8_PORT, SPWM_CH8, SPWM_CH8_ID);    // CH8
    __set_outp(SPWM_CH9_PORT, SPWM_CH9, SPWM_CH9_ID);    // CH9
    __set_outp(SPWM_CH10_PORT, SPWM_CH10, SPWM_CH10_ID); // CH10
    __set_outp(SPWM_CH11_PORT, SPWM_CH11, SPWM_CH11_ID); // CH11
    __set_outp(SPWM_CH12_PORT, SPWM_CH12, SPWM_CH12_ID); // CH12
    __set_outp(SPWM_CH13_PORT, SPWM_CH13, SPWM_CH13_ID); // CH13
    __set_outp(SPWM_CH14_PORT, SPWM_CH14, SPWM_CH14_ID); // CH14
    __set_outp(SPWM_CH15_PORT, SPWM_CH15, SPWM_CH15_ID); // CH15

    spwm_tick_cnt = (spwm_tick_cnt < SPWM_TOP_VAL) ? (spwm_tick_cnt + 1) : 0;
}
#endif