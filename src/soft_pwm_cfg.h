#ifndef __SOFT_PWM_CFG_H__
#define __SOFT_PWM_CFG_H__



/*Type of pwm, it can be INVERTING or NON_INVERTING*/
/*Do not modify*/
#define SPWM_MODE_INVERTING         0
#define SPWM_MODE_NON_INVERTING     1

#define SPWM_MODE                   SPWM_MODE_NON_INVERTING // set mode at here

/*Max channel number*/
/*Do not modify*/
#define SPWM_MAX_CHANNEL_NUM     16

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

/*Output configuration*/
// CH0
#define SPWM_CH0                 PB0
#define SPWM_CH0_DDR             DDRB
#define SPWM_CH0_PORT            PORTB
// CH1
#define SPWM_CH1                 PB1
#define SPWM_CH1_DDR             DDRB
#define SPWM_CH1_PORT            PORTB
// CH2
#define SPWM_CH2                 PB2
#define SPWM_CH2_DDR             DDRB
#define SPWM_CH2_PORT            PORTB
// CH3
#define SPWM_CH3                 PB3
#define SPWM_CH3_DDR             DDRB
#define SPWM_CH3_PORT            PORTB
// CH4
#define SPWM_CH4                 PB4
#define SPWM_CH4_DDR             DDRB
#define SPWM_CH4_PORT            PORTB
// CH5
#define SPWM_CH5                 PB5
#define SPWM_CH5_DDR             DDRB
#define SPWM_CH5_PORT            PORTB
// CH6
#define SPWM_CH6                 PB6
#define SPWM_CH6_DDR             DDRB
#define SPWM_CH6_PORT            PORTB
// CH7
#define SPWM_CH7                 PB7
#define SPWM_CH7_DDR             DDRB
#define SPWM_CH7_PORT            PORTB
// CH8
#define SPWM_CH8                 PD0
#define SPWM_CH8_DDR             DDRD
#define SPWM_CH8_PORT            PORTD
// CH9
#define SPWM_CH9                 PD1
#define SPWM_CH9_DDR             DDRD
#define SPWM_CH9_PORT            PORTD
// CH10
#define SPWM_CH10                PD2
#define SPWM_CH10_DDR            DDRD
#define SPWM_CH10_PORT           PORTD
// CH11
#define SPWM_CH11                PD3
#define SPWM_CH11_DDR            DDRD
#define SPWM_CH11_PORT           PORTD
// CH12
#define SPWM_CH12                PD4
#define SPWM_CH12_DDR            DDRD
#define SPWM_CH12_PORT           PORTD
// CH13
#define SPWM_CH13                PD5
#define SPWM_CH13_DDR            DDRD
#define SPWM_CH13_PORT           PORTD
// CH14
#define SPWM_CH14                PD6
#define SPWM_CH14_DDR            DDRD
#define SPWM_CH14_PORT           PORTD
// CH15
#define SPWM_CH15                PD7
#define SPWM_CH15_DDR            DDRD
#define SPWM_CH15_PORT           PORTD


/*Enable channels: set 0 or 1 the left operandin masking to enable channel*/
// uint16_t spwm_en_state = (uint16_t)((1<<SPWM_CH0_ID)|(1<<SPWM_CH1_ID)|(1<<SPWM_CH2_ID)|(1<<SPWM_CH3_ID)|
//                                 (1<<SPWM_CH4_ID)|(1<<SPWM_CH5_ID)|(1<<SPWM_CH6_ID)|(1<<SPWM_CH7_ID)|
//                                 (1<<SPWM_CH8_ID)|(1<<SPWM_CH9_ID)|(1<<SPWM_CH10_ID)|(1<<SPWM_CH11_ID)|
//                                 (1<<SPWM_CH12_ID)|(1<<SPWM_CH13_ID)|(1<<SPWM_CH14_ID)|(1<<SPWM_CH15_ID));




/*Check configuration*/
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

/*End configuration*/
#endif