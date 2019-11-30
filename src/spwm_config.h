#ifndef _SPWM_H_
#define _SPWM_H_
/*
Developer: Istvan Milak
Configuration header for soft pwm library
*/
#include <inttypes.h>

/*Define the port whic containes the pwm pins. eg. for 8 channel uint8_t*/
typedef uint16_t spwm_port_t;

/*Resolution of pwm: from 0 to PWM_RES*/
#define SPWM_RES     255

/*Inverting mode*/
#define SPWM_INVERTING_MODE     0


// typedef struct {
//     spwm_port_t port_buff[PWM_RES]; // buffer for storring the pwm port values
//     void (*init)(void *write_fnc, spwm_port_t *read_fnc);               // init timers and peripherials
//     void (*write)(spwm_port_t); // function pointer for write arg is the port value
//     spwm_port_t (*read);        // read soft pwm port
// } spwm_t;


#endif