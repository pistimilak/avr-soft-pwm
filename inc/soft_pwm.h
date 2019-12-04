#ifndef __SOFT_PWM_H__
#define __SOFT_PWM_H__
#include <inttypes.h>
#include "soft_pwm_cfg.h"


/*Set channel macro*/
#define spwm_set_ch(id, val)        spwm_val_buff[id] = val

/*Declaration*/
extern uint8_t spwm_tick_cnt;
extern uint16_t spwm_en_state;
extern uint8_t spwm_val_buff[SPWM_MAX_CHANNEL_NUM];
extern void spwm_init_8b();
extern void spwm_tick_8b();



#endif