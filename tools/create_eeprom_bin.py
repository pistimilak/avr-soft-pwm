#!/usr/bin/python3
import os
import json


# commands to upload eeprom from the generated binary file
# avr-objcopy -I binary -O ihex --change-addresses=0x0000 ./tools/eeprom.bin ./hex/eeprom.hex 
# avrdude -p atmega328p -c arduino -P /dev/ttyUSB0 -b57600 -v -u -U eeprom:w:./hex/eeprom.hex

# command for downloading eeprom content to hex file:
# avrdude -p atmega328p -c arduino -P /dev/ttyUSB0 -b57600 -v -u -U eeprom:r:./hex/eeprom.hex:i

print("Informations")
print("------------")
print("commands to upload eeprom from the generated binary file:")
print("avr-objcopy -I binary -O ihex --change-addresses=0x0000 ./tools/eeprom.bin ./hex/eeprom.hex")
print("avrdude -p atmega328p -c arduino -P /dev/ttyUSB0 -b57600 -v -u -U eeprom:w:./hex/eeprom.hex\n")
print("command for downloading eeprom content to hex file:")
print("avrdude -p atmega328p -c arduino -P /dev/ttyUSB0 -b57600 -v -u -U eeprom:r:./hex/eeprom.hex:i\n")

with open("eeprom_conf.json") as cfg_file:
    cfg = json.load(cfg_file)


with open("eeprom.bin", 'wb') as dest_file:
    for sig_val in cfg['signal_array']: #write signal array 1 byte
        dest_file.write(sig_val.to_bytes(1, byteorder='little'))
    
    #write led offsets
    dest_file.write(cfg['led_phase_offsets']['led0'].to_bytes(1, byteorder='little'))
    dest_file.write(cfg['led_phase_offsets']['led1'].to_bytes(1, byteorder='little'))
    dest_file.write(cfg['led_phase_offsets']['led2'].to_bytes(1, byteorder='little'))
    dest_file.write(cfg['led_phase_offsets']['led3'].to_bytes(1, byteorder='little'))
    dest_file.write(cfg['led_phase_offsets']['led4'].to_bytes(1, byteorder='little'))
    dest_file.write(cfg['led_phase_offsets']['led5'].to_bytes(1, byteorder='little'))
    dest_file.write(cfg['led_phase_offsets']['led6'].to_bytes(1, byteorder='little'))
    dest_file.write(cfg['led_phase_offsets']['led7'].to_bytes(1, byteorder='little'))
    dest_file.write(cfg['led_phase_offsets']['led8'].to_bytes(1, byteorder='little'))
    dest_file.write(cfg['led_phase_offsets']['led9'].to_bytes(1, byteorder='little'))
    dest_file.write(cfg['led_phase_offsets']['led10'].to_bytes(1, byteorder='little'))
    dest_file.write(cfg['led_phase_offsets']['led11'].to_bytes(1, byteorder='little'))
    dest_file.write(cfg['led_phase_offsets']['led12'].to_bytes(1, byteorder='little'))
    dest_file.write(cfg['led_phase_offsets']['led13'].to_bytes(1, byteorder='little'))
    dest_file.write(cfg['led_phase_offsets']['led14'].to_bytes(1, byteorder='little'))
    dest_file.write(cfg['led_phase_offsets']['led15'].to_bytes(1, byteorder='little'))

    #write signal speed
    dest_file.write(cfg['T_signal'].to_bytes(2, byteorder='little'))
    
    en_state = 0
    if cfg['spwm_enable_state']['led0']:
        en_state = en_state | (1 << 0)
    if cfg['spwm_enable_state']['led1']:
        en_state = en_state | (1 << 1)
    if cfg['spwm_enable_state']['led2']:
        en_state = en_state | (1 << 2)
    if cfg['spwm_enable_state']['led3']:
        en_state = en_state | (1 << 3)
    if cfg['spwm_enable_state']['led4']:
        en_state = en_state | (1 << 4)
    if cfg['spwm_enable_state']['led5']:
        en_state = en_state | (1 << 5)
    if cfg['spwm_enable_state']['led6']:
        en_state = en_state | (1 << 6)
    if cfg['spwm_enable_state']['led7']:
        en_state = en_state | (1 << 7)
    if cfg['spwm_enable_state']['led8']:
        en_state = en_state | (1 << 8)
    if cfg['spwm_enable_state']['led9']:
        en_state = en_state | (1 << 9)
    if cfg['spwm_enable_state']['led10']:
        en_state = en_state | (1 << 10)
    if cfg['spwm_enable_state']['led11']:
        en_state = en_state | (1 << 11)
    if cfg['spwm_enable_state']['led12']:
        en_state = en_state | (1 << 12)
    if cfg['spwm_enable_state']['led13']:
        en_state = en_state | (1 << 13)
    if cfg['spwm_enable_state']['led14']:
        en_state = en_state | (1 << 14)
    if cfg['spwm_enable_state']['led15']:
        en_state = en_state | (1 << 15)

    dest_file.write(en_state.to_bytes(2, byteorder='little'))
print("eeprom.bin file created ({0} bytes)".format(os.stat("./eeprom.bin").st_size))