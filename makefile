NAME = soft-pwm
CC = avr-gcc
OBJCOPY = avr-objcopy
PROG_SOFT = avrdude
PROG_DEV = arduino
DEV_PORT = /dev/ttyACM0

TARGET = atmega328p
OBJ_PATH = ./obj/
SRC_PATH = ./src/
HEX_PATH = ./hex/
BIN_PATH = ./bin/
DOCS_PATH = ./docs/
# OBJS = obj/main.o
OBJS = obj/main.o obj/soft_pwm.o
DEPS = 

CFLAGS = -mmcu=$(TARGET) -Os
ASMFLAGS = -xassembler-with-cpp -mmcu=$(TARGET) -nostdlib
# ASMFLAGS = -mmcu=$(TARGET)
LIBS = 

# %.o: %.c
# 	$(CC)  $(CFLAGS) -c -o $@ $<




$(NAME).hex: $(NAME).elf
	$(OBJCOPY) -O ihex -R .eeprom $(BIN_PATH)$< $(HEX_PATH)$@
	

$(NAME).elf: $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN_PATH)$@ $^

obj/main.o: src/main.c
	$(CC) $(CFLAGS) -c -o  $@ $^
# obj/soft_pwm_cfg.o: src/soft_pwm_cfg.c
# 	$(CC) $(CFLAGS) -c -o  $@ $^
obj/soft_pwm.o: src/soft_pwm.S
	$(CC) $(ASMFLAGS) -c -o $@ $^

# %.o: %.c
# 	$(CC)  $(CFLAGS) -c -o  $@ $^


.PHONY: clean install-flash install-eeprom set-fuse

install-flash:
	$(PROG_SOFT) -p $(TARGET) -c $(PROG_DEV) -P $(DEV_PORT) -v -u -U flash:w:$(HEX_PATH)$(NAME).hex

install-eeprom:
	$(OBJCOPY) -I binary -O ihex --change-addresses=0x0020 $(DOCS_PATH)eeprom.txt $(HEX_PATH)eeprom.hex 
	$(PROG_SOFT) -p $(TARGET) -c $(PROG_DEV) -P $(DEV_PORT) -v -u -U eeprom:w:$(HEX_PATH)eeprom.hex

set-fuse:
	$(PROG_SOFT) -p $(TARGET) -c $(PROG_DEV) -P $(DEV_PORT) -v -u -U lfuse:w:$(HEX_PATH)lfuse.hex:h 
	$(PROG_SOFT) -p $(TARGET) -c $(PROG_DEV) -P $(DEV_PORT) -v -u -U hfuse:w:$(HEX_PATH)lfuse.hex:h 
	$(PROG_SOFT) -p $(TARGET) -c $(PROG_DEV) -P $(DEV_PORT) -v -u -U efuse:w:$(HEX_PATH)efuse.hex:h 

clean:
	rm -f $(OBJ_PATH)*.o
	rm -f $(HEX_PATH)$(NAME).hex
	rm -f $(HEX_PATH)eeprom.hex
	
