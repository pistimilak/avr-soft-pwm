# avr-soft-pwm
AVR soft pwm solution

## Description
Tested on Arduino nano.

The soft pwm library supports 16 channels which are configurable int the config header.
There is a signal handler library to iterate a signal as pwm duty cycle.

You can find the soft pwm settings in ***./inc/soft_pwm_config.h*** file.

The signal settings are in ***./inc/sig_config.h*** file.

The ***./inc/eeprom_map.h*** file containes the parameter addresses of EEPROM.

You can modify the parameters in the EEPROM with ***./tools/create_eeprom_bin.py*** and the corresponding ***eeprom_conf.json*** file.
With make you can update the EEPROM.

Parameters:
- LED signal phase offsets (uint8_t)
- enable state (uint16_t)
- T_signal (uint16_t)
- signal array (uint8_t [1000])

Calculation for real signal period time:
```
T = T_signal / (F_CPU / (8 * 1000))

T :        time of the complete iteration of signal (1000 element) [s]
T_signal : Timer OCR value, stored in the EEPROM
F_CPU:     16 MHz => 16 * 10^6 Hz

```
## Programing flash
```
$ make install-flash
```

## Create configuration
Example:
1. Configure the parameters in ***./tools/eeprom_conf.json***

2. Create configuration bin:
```
$ python3 ./tools/create_eeprom_bin.py
```

3. Create hex from the bin:
```
$ avr-objcopy -I binary -O ihex --change-addresses=0x0000 ./tools/eeprom.bin ./hex/eeprom.hex
```

4. Programming EEPROM:
```
$ avrdude -p atmega328p -c arduino -P /dev/ttyUSB0 -b57600 -v -u -U eeprom:w:./hex/eeprom.hex
```

Or use make for programming EEPROM (step 2 and 3 together):
```
$ make install-eeprom
```
