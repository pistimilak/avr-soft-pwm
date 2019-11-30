.include "m328Pdef.inc"
.def    tick_cnt_reg    =   r18
.def    en_state_l_reg  =   r19
.def    en_state_h_reg  =   r20
.def    ch_cnt_reg      =   r21
.def    tmp_val         =   r22


#define SPWM_MODE_NONE_INVERTING	0
#define SPWM_MODE_INVERTING			1
#define SPWM_MODE					SPWM_MODE_NON_INVERTING


#if (SPWM_MODE == SPWM_MODE_NONE_INVERTING)
	#warning None Inverting PWM mode activated
#elif (SPWM_MODE == SPWM_MODE_INVERTING)
	#warning Inverting PWM mode activated
#else
	#error Not correct pwm mode selected!
#endif


.equ	SPWM_MAX_CHANNEL_NUM	= 16
.equ	SPWM_RESOLUTION		 	= 255

.equ	SPWM_CH0			 	= 0
.equ	SPWM_CH0_PORT			= PORTB
.equ	SPWM_CH0_DDR			= DDRB

.equ	SPWM_CH1			 	= 1
.equ	SPWM_CH1_PORT			= PORTB
.equ	SPWM_CH1_DDR			= DDRB

.equ	SPWM_CH2			 	= 2
.equ	SPWM_CH2_PORT			= PORTB
.equ	SPWM_CH2_DDR			= DDRB

.equ	SPWM_CH3			 	= 3
.equ	SPWM_CH3_PORT			= PORTB
.equ	SPWM_CH3_DDR			= DDRB

.equ	SPWM_CH4			 	= 4
.equ	SPWM_CH4_PORT			= PORTB
.equ	SPWM_CH4_DDR			= DDRB

.equ	SPWM_CH5			 	= 5
.equ	SPWM_CH5_PORT			= PORTB
.equ	SPWM_CH5_DDR			= DDRB

.equ	SPWM_CH6			 	= 6
.equ	SPWM_CH6_PORT			= PORTB
.equ	SPWM_CH6_DDR			= DDRB

.equ	SPWM_CH7			 	= 7
.equ	SPWM_CH7_PORT			= PORTB
.equ	SPWM_CH7_DDR			= DDRB

.equ	SPWM_CH8			 	= 0
.equ	SPWM_CH8_PORT			= PORTD
.equ	SPWM_CH8_DDR			= DDRD

.equ	SPWM_CH9			 	= 1
.equ	SPWM_CH9_PORT			= PORTD
.equ	SPWM_CH9_DDR			= DDRD

.equ	SPWM_CH10			 	= 2
.equ	SPWM_CH10_PORT			= PORTD
.equ	SPWM_CH10_DDR			= DDRD

.equ	SPWM_CH11			 	= 3
.equ	SPWM_CH11_PORT			= PORTD
.equ	SPWM_CH11_DDR			= DDRD

.equ	SPWM_CH12			 	= 4
.equ	SPWM_CH12_PORT			= PORTD
.equ	SPWM_CH12_DDR			= DDRD

.equ	SPWM_CH13			 	= 5
.equ	SPWM_CH13_PORT			= PORTD
.equ	SPWM_CH13_DDR			= DDRD

.equ	SPWM_CH14			 	= 6
.equ	SPWM_CH14_PORT			= PORTD
.equ	SPWM_CH14_DDR			= DDRD

.equ	SPWM_CH15			 	= 7
.equ	SPWM_CH15_PORT			= PORTD
.equ	SPWM_CH15_DDR			= DDRD

.dseg
spwm_tick_cnt: .byte	1
spwm_val_buff: .byte	16
spwm_en_state: .byte	2



.cseg
.org 0x0000
	jmp main
;----------------------------------------------------------------------------------------------------------
; macro for set channel ddr
;	- @0: status byte reg
;	- @1: status bit
;	- @2: ch ddr port 
;	- @3: ch pin num
;----------------------------------------------------------------------------------------------------------
.macro		SET_CH_DDR
	sbrs	@0, @1										; skip if bit is cleared in status byte
	rjmp	PC+2										; jump to set channel DDDR
	sbi		@2, @3
; PC+2:
.endmacro

;----------------------------------------------------------------------------------------------------------
; macro for set channel ddr
;	- @0: status byte 
;	- @1: ch bit in status
;	- @2: port
;	- @3: pin num
;	- @4: next channel label
; 
;----------------------------------------------------------------------------------------------------------
.macro		SET_CH_OUTP
	ld      tmp_val, Z+									; load channel value to tmp_val, it should be always executed
	sbrs	@0, @1										; if status eneable, skip the jumping to next channel
	rjmp	PC+7										; jump to the next channel
    cp      tick_cnt_reg, tmp_val						; compare value with the tick counter
#if SPWM_MODE == SPWM_MODE_NONE_INVERTING
	brcs	PC+2										; if tick_cnt_reg < channel value (carry is not set) set the channel to HIGH
	rjmp	PC+3										; else clear channel (set to LOW)
; PC+2:
	sbi		@2, @3										; set channel bit on the channel port
	rjmp	PC+2									 	; jump to the next channel
; PC+3:
	cbi		@2, @3										; clear channel bit on port channel port
; PC+7 & PC+2:
#else
	brcs	PC+2										; if tick_cnt_reg < channel value (carry is not set) set the channel to LOW
	rjmp	PC+3										; else set channel to HIGH
; PC+2:
	cbi		@2, @3										; clear channel bit on port channel port
	rjmp	PC+2									 	; jump to the next channel
; PC+3:
	sbi		@2, @3										; set channel bit on the channel port
; PC+7 & PC+2:
#endif
.endmacro


;----------------------------------------------------------------------------------------------------------
; Soft pwm init 8 bit:
;	- reset tick counter
;	- set DDR for channels
;	- reset buffer
;----------------------------------------------------------------------------------------------------------
spwm_init_8b:
	lds		en_state_l_reg, spwm_en_state							; load enable state low byte to register
	lds		en_state_h_reg, spwm_en_state + 1						; load enable state high byte to register
	sts		spwm_tick_cnt, r0										; reset counter
	ldi		r16, SPWM_MAX_CHANNEL_NUM								; reset value
	ldi		ZL, LOW(spwm_val_buff)									; load buffer address to Z
	ldi		ZH, HIGH(spwm_val_buff)
; @0 status byte reg @1 status bit @2 ddr port @3: ch pin num

	SET_CH_DDR		en_state_l_reg,0,SPWM_CH0_DDR,SPWM_CH0			; set ch0 DDR
	SET_CH_DDR		en_state_l_reg,1,SPWM_CH1_DDR,SPWM_CH1			; set ch1 DDR
	SET_CH_DDR		en_state_l_reg,2,SPWM_CH2_DDR,SPWM_CH2			; set ch2 DDR
	SET_CH_DDR		en_state_l_reg,3,SPWM_CH3_DDR,SPWM_CH3			; set ch3 DDR
	SET_CH_DDR		en_state_l_reg,4,SPWM_CH4_DDR,SPWM_CH4			; set ch4 DDR
	SET_CH_DDR		en_state_l_reg,5,SPWM_CH5_DDR,SPWM_CH5			; set ch5 DDR
	SET_CH_DDR		en_state_l_reg,6,SPWM_CH6_DDR,SPWM_CH6			; set ch6 DDR
	SET_CH_DDR		en_state_l_reg,7,SPWM_CH7_DDR,SPWM_CH7			; set ch7 DDR
	SET_CH_DDR		en_state_h_reg,0,SPWM_CH8_DDR,SPWM_CH8			; set ch8 DDR
	SET_CH_DDR		en_state_h_reg,1,SPWM_CH9_DDR,SPWM_CH9			; set ch9 DDR
	SET_CH_DDR		en_state_h_reg,2,SPWM_CH10_DDR,SPWM_CH10		; set ch10 DDR
	SET_CH_DDR		en_state_h_reg,3,SPWM_CH11_DDR,SPWM_CH11		; set ch11 DDR
	SET_CH_DDR		en_state_h_reg,4,SPWM_CH12_DDR,SPWM_CH12		; set ch12 DDR
	SET_CH_DDR		en_state_h_reg,5,SPWM_CH13_DDR,SPWM_CH13		; set ch13 DDR
	SET_CH_DDR		en_state_h_reg,6,SPWM_CH14_DDR,SPWM_CH14		; set ch14 DDR
	SET_CH_DDR		en_state_h_reg,7,SPWM_CH15_DDR,SPWM_CH15		; set ch15 DDR
	nop
RESET_VALUE:
	st		Z+, r0													; set pointer to 0 after increment pointer	
	dec		r16														; decrement temp buff counter
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
    ldi     ZL, LOW(spwm_val_buff)									; pointer to spwm val buffer
    ldi     ZH, HIGH(spwm_val_buff)
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


main:
	rcall 	spwm_init_8b
	ldi 	ZL, LOW(spwm_en_state)
	ldi 	ZH, HIGH(spwm_en_state)
	ldi 	r16, 0b11111111			; set low byte status
	st		Z+, r16
	ldi 	r16, 0b11111111			; set high byte status
	st		Z, r16
	
	ldi		ZL, LOW(spwm_val_buff)		; set buff values
	ldi		ZH, HIGH(spwm_val_buff)
	ldi		r16, 2						; ch0 val
	st		Z+, r16
	ldi		r16, 3						; ch1 val
	st		Z+, r16
	ldi		r16, 0						; ch2 val
	st		Z+, r16
	ldi		r16, 48						; ch3 val
	st		Z+, r16
	ldi		r16, 128					; ch4 val
	st		Z+, r16
	ldi		r16, 255					; ch5 val
	st		Z+, r16
	ldi		r16, 17						; ch6 val
	st		Z+, r16
	ldi		r16, 0						; ch7 val
	st		Z+, r16
	ldi		r16, 200					; ch8 val
	st		Z+, r16
	ldi		r16, 210					; ch9 val
	st		Z+, r16
	ldi		r16, 65						; ch10 val
	st		Z+, r16
	ldi		r16, 112					; ch11 val
	st		Z+, r16
	ldi		r16, 100					; ch12 val
	st		Z+, r16
	ldi		r16, 29						; ch13 val
	st		Z+, r16
	ldi		r16, 64						; ch14 val
	st		Z+, r16
	ldi		r16, 2						; ch15 val
	st		Z, r16
end:
	rcall	spwm_tick_8b
	rjmp	end
