# avr-soft-pwm
AVR soft pwm solution

## Description
Tested on Arduino nano.

The soft pwm library supports 16 channels which are configurable int the config header.
There is a signal handler library to iterate a signal as pwm duty signal.

The eeprom_map.h file containes the parameter eeprom addresses.

You can modify the parameters in the eeprom with ***./tools/create_eeprom_bin.py*** and the corresponding ***eeprom_conf.json** file
With make you can update the eeprom

Parameters:
- led phase offsets (uint8_t)
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
1. Create configuration bin:
```
$ python3 ./tools/create_eeprom_bin.py
```

2. Create hex from the bin:
```
$ avr-objcopy -I binary -O ihex --change-addresses=0x0000 ./tools/eeprom.bin ./hex/eeprom.hex
```

3. Programming EEPROM:
```
avrdude -p atmega328p -c arduino -P /dev/ttyUSB0 -b57600 -v -u -U eeprom:w:./hex/eeprom.hex
```

4. Use make for programming EEPROM (step 2 and 3 together):
```
$ make install-eeprom
```
