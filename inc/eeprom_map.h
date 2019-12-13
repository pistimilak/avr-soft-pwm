#ifndef __EEPROM_MAP_H__
#define __EEPROM_MAP_H__

#define EEPROM_Signal           ((const uint8_t *)0x0000)           /* uint8_t [1000] signal value array */
#define EEPROM_LED0_offset      ((const uint8_t *)0x03E8)           /* uint8_t LED0 phase offset */
#define EEPROM_LED1_offset      ((const uint8_t *)0x03E9)           /* uint8_t LED1 phase offset */
#define EEPROM_LED2_offset      ((const uint8_t *)0x03EA)           /* uint8_t LED2 phase offset */
#define EEPROM_LED3_offset      ((const uint8_t *)0x03EB)           /* uint8_t LED3 phase offset */
#define EEPROM_LED4_offset      ((const uint8_t *)0x03EC)           /* uint8_t LED4 phase offset */
#define EEPROM_LED5_offset      ((const uint8_t *)0x03ED)           /* uint8_t LED5 phase offset */
#define EEPROM_LED6_offset      ((const uint8_t *)0x03EE)           /* uint8_t LED6 phase offset */
#define EEPROM_LED7_offset      ((const uint8_t *)0x03EF)           /* uint8_t LED7 phase offset */
#define EEPROM_LED8_offset      ((const uint8_t *)0x03F0)           /* uint8_t LED8 phase offset */
#define EEPROM_LED9_offset      ((const uint8_t *)0x03F1)           /* uint8_t LED9 phase offset */
#define EEPROM_LED10_offset     ((const uint8_t *)0x03F2)           /* uint8_t LED10 phase offset */
#define EEPROM_LED11_offset     ((const uint8_t *)0x03F3)           /* uint8_t LED11 phase offset */
#define EEPROM_LED12_offset     ((const uint8_t *)0x03F4)           /* uint8_t LED12 phase offset */
#define EEPROM_LED13_offset     ((const uint8_t *)0x03F5)           /* uint8_t LED13 phase offset */
#define EEPROM_LED14_offset     ((const uint8_t *)0x03F6)           /* uint8_t LED14 phase offset */
#define EEPROM_LED15_offset     ((const uint8_t *)0x03F7)           /* uint8_t LED15 phase offset */
#define EEPROM_SPWM_TIM8_OCR    ((const uint8_t *)0x03F8)           /* uint8_t Timer0 compare match value for soft pwm */
#define EEPROM_SIG_TIM16_OCR    ((const uint16_t *)0x03F9)          /* uint16_t Timer1 comapre match value for signal tracking */
#define EEPROM_SPWM_EN_STATE    ((const uint16_t *)0x03FB)          /* uint16_t enable state for soft pwm*/

#endif