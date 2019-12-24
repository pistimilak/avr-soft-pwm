# avr-soft-pwm
AVR soft pwm solution

Tested on Arduino nano.

The soft pwm library supports 16 channels which are configurable int the config header.
There is a signal handler library to iterate a signal as pwm duty signal.

The eeprom_map.h file containes the parameter eeprom addresses.
You can modify the parameters in the eeprom with ./tools/create_eeprom_bin.py and the corresponding eeprom_conf.json file
With make you can update the eeprom

Parameters:
- led phase offsets (uint8_t)
- enable state (uint16_t)
- T_signal (uint16_t)
- signal array (uint8_t [1000])

Calculation for real signal period time:
T = T_signal / ((F_CPU / (8 * 1000))
