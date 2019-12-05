#include "soft_pwm.h"

#if SPWM_TOP_VAL > 255 && SPWM_TOP_VAL < 65536
    uint16_t spwm_duty_cycle_buff[SPWM_MAX_CHANNEL_NUM] = {0};
#else
    uint8_t spwm_duty_cycle_buff[SPWM_MAX_CHANNEL_NUM] = {0};
#endif
static uint16_t spwm_tick_cnt = 0;
static uint16_t spwm_en_state = 0;

/*Buffering port, if used*/
#ifdef PORTA
    #if __IS_PORT_USED(PORTA)
        static uint8_t PORTA_buff = 0;
    #endif
#endif
#ifdef PORTB
    #if __IS_PORT_USED(PORTB)
        static uint8_t PORTB_buff = 0;
    #endif
#endif
#ifdef PORTC
    #if __IS_PORT_USED(PORTC)
        static uint8_t PORTC_buff = 0;
    #endif
#endif
#ifdef PORTD
    #if __IS_PORT_USED(PORTD)
        static uint8_t PORTD_buff = 0;
    #endif
#endif
#ifdef PORTE
    #if __IS_PORT_USED(PORTE)
        static uint8_t PORTE_buff = 0;
    #endif
#endif
#ifdef PORTF
    #if __IS_PORT_USED(PORTF)
        static uint8_t PORTF_buff = 0;
    #endif
#endif
#ifdef PORTG
    #if __IS_PORT_USED(PORTG)
        static uint8_t PORTG_buff = 0;
    #endif
#endif
#ifdef PORTH
    #if __IS_PORT_USED(PORTH)
        static uint8_t PORTH_buff = 0;
    #endif
#endif


void spwm_init()
{

}

/*get port buffer pointer*/
static uint8_t* spwm_get_port_buff(uint8_t *port) 
{
    switch(port) {

#ifdef PORTA
    #if __IS_PORT_USED(PORTA)
            case PORTA:
                return &PORTA_buff;
    #endif
#endif
#ifdef PORTB
    #if __IS_PORT_USED(PORTB)
            case PORTB:
                return &PORTB_buff;
    #endif
#endif
#ifdef PORTC
    #if __IS_PORT_USED(PORTC)
            case PORTC:
                return &PORTC_buff;
    #endif
#endif
#ifdef PORTD
    #if __IS_PORT_USED(PORTD)
            case PORTD:
                return &PORTD_buff;
    #endif
#endif
#ifdef PORTE
    #if __IS_PORT_USED(PORTE)
            case PORTE:
                return &PORTE_buff;
    #endif
#endif
#ifdef PORTF
    #if __IS_PORT_USED(PORTF)
            case PORTF:
                return &PORTF_buff;
    #endif
#endif
#ifdef PORTG
    #if __IS_PORT_USED(PORTG)
            case PORTG:
                return &PORTG_buff;
    #endif
#endif
#ifdef PORTH
    #if __IS_PORT_USED(PORTH)
            case PORTH:
                return &PORTH_buff;
    #endif
#endif
    }
}

static void spwm_buffering_ports()
{
#ifdef PORTA
    #if __IS_PORT_USED(PORTA)
            PORTA_buff = PORTA;
    #endif
#endif
#ifdef PORTB
    #if __IS_PORT_USED(PORTB)
            PORTB_buff = PORTB;
    #endif
#endif
#ifdef PORTC
    #if __IS_PORT_USED(PORTC)
            PORTC_buff = PORTC;
    #endif
#endif
#ifdef PORTD
    #if __IS_PORT_USED(PORTD)
            PORTD_buff = PORTD;
    #endif
#endif
#ifdef PORTE
    #if __IS_PORT_USED(PORTE)
            PORTE_buff = PORTE;
    #endif
#endif
#ifdef PORTF
    #if __IS_PORT_USED(PORTF)
            PORTF_buff = PORTF;
    #endif
#endif
#ifdef PORTG
    #if __IS_PORT_USED(PORTG)
            PORTG_buff = PORTG;
    #endif
#endif
#ifdef PORTH
    #if __IS_PORT_USED(PORTH)
            PORTH_buff = PORTH;
    #endif
#endif
}


static void spwm_write_ports()
{
#ifdef PORTA
    #if __IS_PORT_USED(PORTA)
            PORTA = PORTA_buff;
    #endif
#endif
#ifdef PORTB
    #if __IS_PORT_USED(PORTB)
            PORTB = PORTB_buff;
    #endif
#endif
#ifdef PORTC
    #if __IS_PORT_USED(PORTC)
            PORTC = PORTC_buff;
    #endif
#endif
#ifdef PORTD
    #if __IS_PORT_USED(PORTD)
            PORTD = PORTD_buff;
    #endif
#endif
#ifdef PORTE
    #if __IS_PORT_USED(PORTE)
            PORTE = PORTE_buff;
    #endif
#endif
#ifdef PORTF
    #if __IS_PORT_USED(PORTF)
            PORTG = PORTG_buff;
    #endif
#endif
#ifdef PORTG
    #if __IS_PORT_USED(PORTG)
            PORTG = PORTG_buff;
    #endif
#endif
#ifdef PORTH
    #if __IS_PORT_USED(PORTH)
            PORTH = PORTH_buff;
    #endif
#endif
}



void spwm_tick()
{

    uint8_t *port_buff;
    spwm_buffering_ports();
    // CH0
    port_buff = spwm_get_port_buff(SPWM_CH0_PORT);
    *port_buff = (spwm_en_state & (1 << SPWM_CH0_ID)) && (spwm_tick_cnt < spwm_duty_cycle_buff[SPWM_CH0_ID])) ? 
                            (*port_buff | (1 << SPWM_CH0)) : (*port_buff & ~(1 << SPWM_CH0));

    // CH1
    port_buff = spwm_get_port_buff(SPWM_CH1_PORT);
    *port_buff = (spwm_en_state & (1 << SPWM_CH1_ID)) && (spwm_tick_cnt < spwm_duty_cycle_buff[SPWM_CH1_ID])) ? 
                            (*port_buff | (1 << SPWM_CH1)) : (*port_buff & ~(1 << SPWM_CH1));

    // CH2
    port_buff = spwm_get_port_buff(SPWM_CH2_PORT);
    *port_buff = (spwm_en_state & (1 << SPWM_CH2_ID)) && (spwm_tick_cnt < spwm_duty_cycle_buff[SPWM_CH2_ID])) ? 
                            (*port_buff | (1 << SPWM_CH2)) : (*port_buff & ~(1 << SPWM_CH2));

    
    // CH3
    port_buff = spwm_get_port_buff(SPWM_CH3_PORT);
    *port_buff = (spwm_en_state & (1 << SPWM_CH3_ID)) && (spwm_tick_cnt < spwm_duty_cycle_buff[SPWM_CH3_ID])) ? 
                            (*port_buff | (1 << SPWM_CH3)) : (*port_buff & ~(1 << SPWM_CH3));


    // CH4
    port_buff = spwm_get_port_buff(SPWM_CH4_PORT);
    *port_buff = (spwm_en_state & (1 << SPWM_CH4_ID)) && (spwm_tick_cnt < spwm_duty_cycle_buff[SPWM_CH4_ID])) ? 
                            (*port_buff | (1 << SPWM_CH4)) : (*port_buff & ~(1 << SPWM_CH4));
    

    // CH5
    port_buff = spwm_get_port_buff(SPWM_CH5_PORT);
    *port_buff = (spwm_en_state & (1 << SPWM_CH5_ID)) && (spwm_tick_cnt < spwm_duty_cycle_buff[SPWM_CH5_ID])) ? 
                            (*port_buff | (1 << SPWM_CH5)) : (*port_buff & ~(1 << SPWM_CH5));



    // CH6
    port_buff = spwm_get_port_buff(SPWM_CH6_PORT);
    *port_buff = (spwm_en_state & (1 << SPWM_CH6_ID)) && (spwm_tick_cnt < spwm_duty_cycle_buff[SPWM_CH6_ID])) ? 
                            (*port_buff | (1 << SPWM_CH6)) : (*port_buff & ~(1 << SPWM_CH6));


    // CH7
    port_buff = spwm_get_port_buff(SPWM_CH7_PORT);
    *port_buff = (spwm_en_state & (1 << SPWM_CH7_ID)) && (spwm_tick_cnt < spwm_duty_cycle_buff[SPWM_CH7_ID])) ? 
                            (*port_buff | (1 << SPWM_CH7)) : (*port_buff & ~(1 << SPWM_CH7));


    // CH8
    port_buff = spwm_get_port_buff(SPWM_CH8_PORT);
    *port_buff = (spwm_en_state & (1 << SPWM_CH8_ID)) && (spwm_tick_cnt < spwm_duty_cycle_buff[SPWM_CH8_ID])) ? 
                            (*port_buff | (1 << SPWM_CH8)) : (*port_buff & ~(1 << SPWM_CH8));

    // CH9
    port_buff = spwm_get_port_buff(SPWM_CH9_PORT);
    *port_buff = (spwm_en_state & (1 << SPWM_CH9_ID)) && (spwm_tick_cnt < spwm_duty_cycle_buff[SPWM_CH9_ID])) ? 
                            (*port_buff | (1 << SPWM_CH9)) : (*port_buff & ~(1 << SPWM_CH9));

    // CH10
    port_buff = spwm_get_port_buff(SPWM_CH10_PORT);
    *port_buff = (spwm_en_state & (1 << SPWM_CH10_ID)) && (spwm_tick_cnt < spwm_duty_cycle_buff[SPWM_CH10_ID])) ? 
                            (*port_buff | (1 << SPWM_CH10)) : (*port_buff & ~(1 << SPWM_CH10));

    
    // CH11
    port_buff = spwm_get_port_buff(SPWM_CH11_PORT);
    *port_buff = (spwm_en_state & (1 << SPWM_CH11_ID)) && (spwm_tick_cnt < spwm_duty_cycle_buff[SPWM_CH11_ID])) ? 
                            (*port_buff | (1 << SPWM_CH11)) : (*port_buff & ~(1 << SPWM_CH11));


    // CH12
    port_buff = spwm_get_port_buff(SPWM_CH12_PORT);
    *port_buff = (spwm_en_state & (1 << SPWM_CH12_ID)) && (spwm_tick_cnt < spwm_duty_cycle_buff[SPWM_CH12_ID])) ? 
                            (*port_buff | (1 << SPWM_CH12)) : (*port_buff & ~(1 << SPWM_CH12));
    

    // CH13
    port_buff = spwm_get_port_buff(SPWM_CH13_PORT);
    *port_buff = (spwm_en_state & (1 << SPWM_CH13_ID)) && (spwm_tick_cnt < spwm_duty_cycle_buff[SPWM_CH13_ID])) ? 
                            (*port_buff | (1 << SPWM_CH13)) : (*port_buff & ~(1 << SPWM_CH13));



    // CH14
    port_buff = spwm_get_port_buff(SPWM_CH14_PORT);
    *port_buff = (spwm_en_state & (1 << SPWM_CH14_ID)) && (spwm_tick_cnt < spwm_duty_cycle_buff[SPWM_CH14_ID])) ? 
                            (*port_buff | (1 << SPWM_CH14)) : (*port_buff & ~(1 << SPWM_CH14));


    // CH15
    port_buff = spwm_get_port_buff(SPWM_CH15_PORT);
    *port_buff = (spwm_en_state & (1 << SPWM_CH15_ID)) && (spwm_tick_cnt < spwm_duty_cycle_buff[SPWM_CH15_ID])) ? 
                            (*port_buff | (1 << SPWM_CH15)) : (*port_buff & ~(1 << SPWM_CH15));


    spwm_write_ports();

    spwm_tick_cnt = spwm_tick_cnt < SPWM_TOP_VAL ? ++spwm_tick_cnt : 0;

}