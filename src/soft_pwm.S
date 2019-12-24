#define __SFR_OFFSET    0
#include <avr/io.h>
#include "soft_pwm_cfg.h"

#define tick_cnt_reg  		r18
#define en_state_l_reg		r19
#define en_state_h_reg		r20
#define ch_cnt_reg    		r21
#define tmp_val       		r22


.global spwm_init_8b
.global spwm_tick_8b
.global spwm_tick_cnt
.global spwm_en_state
.global spwm_val_buff

.section .data
spwm_tick_cnt: .byte	1
spwm_en_state: .byte	2
spwm_val_buff: .byte	SPWM_MAX_CHANNEL_NUM


.section .text




;----------------------------------------------------------------------------------------------------------
; macro for set channel ddr
;	- @0: status byte reg
;	- @1: status bit
;	- @2: ch ddr port 
;	- @3: ch pin num
;----------------------------------------------------------------------------------------------------------
.macro		SET_CH_DDR	stat_byte:req, stat_bit:req, ch_ddr:req, ch_pin:req
	sbrs	\stat_byte, \stat_bit								; skip if bit is cleared in status byte
;	rjmp	PC+2										; jump to set channel DDDR
	rjmp	.+3										; jump to set channel DDDR
	sbi		\ch_ddr, \ch_pin
; PC+2:
.endm

;----------------------------------------------------------------------------------------------------------
; macro for set channel ddr
;	- @0: status byte 
;	- @1: ch bit in status
;	- @2: port
;	- @3: pin num
;----------------------------------------------------------------------------------------------------------
.macro		SET_CH_OUTP		stat_byte:req, stat_bit:req, ch_port:req, ch_bit:req
	ld      tmp_val, Z+									; load channel value to tmp_val, it should be always executed
	sbrs	\stat_byte, \stat_bit										; if status eneable, skip the jumping to next channel
;	rjmp	PC+7										; jump to the next channel
	rjmp	.+13										; jump to the next channel
    cp      tick_cnt_reg, tmp_val						; compare value with the tick counter
#if SPWM_MODE == SPWM_MODE_NONE_INVERTING
;	brcs	PC+2										; if tick_cnt_reg < channel value (carry is not set) set the channel to HIGH
	brcs	.+3										; if tick_cnt_reg < channel value (carry is not set) set the channel to HIGH
;	rjmp	PC+3										; else clear channel (set to LOW)
	rjmp	.+5										; else clear channel (set to LOW)	
; PC+2:
	sbi		\ch_port, \ch_bit										; set channel bit on the channel port
;	rjmp	PC+2									 	; jump to the next channel
	rjmp	.+3									 	; jump to the next channel
; PC+3:
	cbi		\ch_port, \ch_bit										; clear channel bit on port channel port
; PC+7 & PC+2:
#else
;	brcs	PC+2										; if tick_cnt_reg < channel value (carry is not set) set the channel to LOW
	brcs	.+3										; if tick_cnt_reg < channel value (carry is not set) set the channel to LOW
;	rjmp	PC+3										; else set channel to HIGH
	rjmp	.+5										; else set channel to HIGH
; PC+2:
	cbi		\ch_port, \ch_bit										; clear channel bit on port channel port
;	rjmp	PC+2									 	; jump to the next channel
	rjmp	.+3									 	; jump to the next channel
; PC+3:
	sbi		\ch_port, \ch_bit										; set channel bit on the channel port
; PC+7 & PC+2:
#endif
.endm


;----------------------------------------------------------------------------------------------------------
; Soft pwm init 8 bit:
;	- reset tick counter
;	- set DDR for channels
;	- reset buffer
;----------------------------------------------------------------------------------------------------------
spwm_init_8b:
;	sbi		DDRB, 5
;	sbi		PORTB, 5
;	rjmp	.+9
;	nop
;	nop
;	nop
;	nop
;	cbi		PORTB, 5
;	nop
;	nop

	lds		en_state_l_reg, spwm_en_state							; load enable state low byte to register
	lds		en_state_h_reg, spwm_en_state + 1						; load enable state high byte to register
	sts		spwm_tick_cnt, r1							; reset counter
	ldi		r23, SPWM_MAX_CHANNEL_NUM					; reset value
	ldi		ZL, lo8(spwm_val_buff)						; load buffer address to Z
	ldi		ZH, hi8(spwm_val_buff)
; @0 status byte reg @1 status bit @2 ddr port @3: ch pin num
	SET_CH_DDR		en_state_l_reg, 0, SPWM_CH0_DDR, SPWM_CH0			; set ch0 DDR
	SET_CH_DDR		en_state_l_reg, 1, SPWM_CH1_DDR, SPWM_CH1			; set ch1 DDR
	SET_CH_DDR		en_state_l_reg, 2, SPWM_CH2_DDR, SPWM_CH2			; set ch2 DDR
	SET_CH_DDR		en_state_l_reg, 3, SPWM_CH3_DDR, SPWM_CH3			; set ch3 DDR
	SET_CH_DDR		en_state_l_reg, 4, SPWM_CH4_DDR, SPWM_CH4			; set ch4 DDR
	SET_CH_DDR		en_state_l_reg, 5, SPWM_CH5_DDR, SPWM_CH5			; set ch5 DDR
	SET_CH_DDR		en_state_l_reg, 6, SPWM_CH6_DDR, SPWM_CH6			; set ch6 DDR
	SET_CH_DDR		en_state_l_reg, 7, SPWM_CH7_DDR, SPWM_CH7			; set ch7 DDR
	SET_CH_DDR		en_state_h_reg, 0, SPWM_CH8_DDR, SPWM_CH8			; set ch8 DDR
	SET_CH_DDR		en_state_h_reg, 1, SPWM_CH9_DDR, SPWM_CH9			; set ch9 DDR
	SET_CH_DDR		en_state_h_reg, 2, SPWM_CH10_DDR, SPWM_CH10		; set ch10 DDR
	SET_CH_DDR		en_state_h_reg, 3, SPWM_CH11_DDR, SPWM_CH11		; set ch11 DDR
	SET_CH_DDR		en_state_h_reg, 4, SPWM_CH12_DDR, SPWM_CH12		; set ch12 DDR
	SET_CH_DDR		en_state_h_reg, 5, SPWM_CH13_DDR, SPWM_CH13		; set ch13 DDR
	SET_CH_DDR		en_state_h_reg, 6, SPWM_CH14_DDR, SPWM_CH14		; set ch14 DDR
	SET_CH_DDR		en_state_h_reg, 7, SPWM_CH15_DDR, SPWM_CH15		; set ch15 DDR
	nop
RESET_VALUE:
	st		Z+, r1													; set pointer to 0 after increment pointer	
	dec		r23														; decrement temp buff counter
	brne	RESET_VALUE												; reset if cnt not 0
	ret																; return
	
;----------------------------------------------------------------------------------------------------------
; Soft PWM tick 8 bit:
;	- compare the tick counter value with the pwm buff value and enable/disable output
;	- increment and store the counter
;	- shoul be called in timmer interrupt
; The function takes 192 cycle on Atmega328p emulator (AVR studio 4) if all of channels enabled
;----------------------------------------------------------------------------------------------------------
spwm_tick_8b:
    lds		tick_cnt_reg, spwm_tick_cnt								; load spwm tick to register
	lds		en_state_l_reg, spwm_en_state							; load enable state low byte to register
	lds		en_state_h_reg, spwm_en_state + 1						; load enable state high byte to register
    ldi     ZL, lo8(spwm_val_buff)									; pointer to spwm val buffer
    ldi     ZH, hi8(spwm_val_buff)
; @0 status byte @1: ch bit in status, @2: port, @3: pin num
	SET_CH_OUTP		en_state_l_reg,0,SPWM_CH0_PORT,SPWM_CH0			; set ch0 output
	SET_CH_OUTP		en_state_l_reg,1,SPWM_CH1_PORT,SPWM_CH1			; set ch1 output
	SET_CH_OUTP		en_state_l_reg,2,SPWM_CH2_PORT,SPWM_CH2			; set ch2 output
	SET_CH_OUTP		en_state_l_reg,3,SPWM_CH3_PORT,SPWM_CH3			; set ch3 output
	SET_CH_OUTP		en_state_l_reg,4,SPWM_CH4_PORT,SPWM_CH4			; set ch4 output
	SET_CH_OUTP		en_state_l_reg,5,SPWM_CH5_PORT,SPWM_CH5			; set ch5 output
	SET_CH_OUTP		en_state_l_reg,6,SPWM_CH6_PORT,SPWM_CH6			; set ch6 output
	SET_CH_OUTP		en_state_l_reg,7,SPWM_CH7_PORT,SPWM_CH7			; set ch7 output
	SET_CH_OUTP		en_state_h_reg,0,SPWM_CH8_PORT,SPWM_CH8			; set ch8 output
	SET_CH_OUTP		en_state_h_reg,1,SPWM_CH9_PORT,SPWM_CH9			; set ch9 output
	SET_CH_OUTP		en_state_h_reg,2,SPWM_CH10_PORT,SPWM_CH10		; set ch10 output
	SET_CH_OUTP		en_state_h_reg,3,SPWM_CH11_PORT,SPWM_CH11		; set ch11 output
	SET_CH_OUTP		en_state_h_reg,4,SPWM_CH12_PORT,SPWM_CH12		; set ch12 output
	SET_CH_OUTP		en_state_h_reg,5,SPWM_CH13_PORT,SPWM_CH13		; set ch13 output
	SET_CH_OUTP		en_state_h_reg,6,SPWM_CH14_PORT,SPWM_CH14		; set ch14 output
	SET_CH_OUTP		en_state_h_reg,7,SPWM_CH15_PORT,SPWM_CH15		; set ch15 output
	inc		tick_cnt_reg											; increment counter
	sts		spwm_tick_cnt, tick_cnt_reg								; store the tick_cnt reg value to spwm_tick_cnt
	ret																; return
