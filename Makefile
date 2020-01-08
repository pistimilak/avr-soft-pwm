NAME = avr-soft-pwm
CC = avr-gcc
OBJCOPY = avr-objcopy
PROG_SOFT = avrdude
PROG_DEV = arduino
DEV_PORT = /dev/ttyUSB0

TARGET = atmega328p
BUILD_DIR = ./build
SRC_DIR = ./src
HEX_DIR = ./hex
BIN_DIR = ./bin
TOOLS_DIR = ./tools

OBJS  = $(BUILD_DIR)/main.o
OBJS += $(BUILD_DIR)/soft_pwm.o
OBJS += $(BUILD_DIR)/sig.o
OBJS += $(BUILD_DIR)/sin.o 


INC = -Iinc

CFLAGS = -mmcu=$(TARGET) -Os $(INC)
ifeq (${INIT_EEPROM}, 1)
CFLAGS += -DINIT_EEPROM
endif

ASMFLAGS = -xassembler-with-cpp -mmcu=$(TARGET) -nostdlib $(INC)
LIBS = 


$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC)  $(CFLAGS) -c -o $@ $<


$(HEX_DIR)/$(NAME).hex: $(BIN_DIR)/$(NAME).elf
	$(OBJCOPY) -O ihex -R .eeprom $< $@
	

$(BIN_DIR)/$(NAME).elf: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^
	avr-size $@

$(shell   mkdir -p $(BUILD_DIR))



.PHONY: clean install-flash install-eeprom set-fuse

install-flash:
	$(PROG_SOFT) -p $(TARGET) -c $(PROG_DEV) -P $(DEV_PORT) -b57600 -v -u -U flash:w:$(HEX_DIR)/$(NAME).hex

install-eeprom:
	./tools/create_eeprom_bin.py
	$(OBJCOPY) -I binary -O ihex $(TOOLS_DIR)/eeprom.bin $(HEX_DIR)/eeprom.hex 
	$(PROG_SOFT) -p $(TARGET) -c $(PROG_DEV) -P $(DEV_PORT) -b57600 -v -u -U eeprom:w:$(HEX_DIR)/eeprom.hex

set-fuse:
	$(PROG_SOFT) -p $(TARGET) -c $(PROG_DEV) -P $(DEV_PORT) -b57600 -v -u -U lfuse:w:$(HEX_DIR)/lfuse.hex:h 
	$(PROG_SOFT) -p $(TARGET) -c $(PROG_DEV) -P $(DEV_PORT) -b57600 -v -u -U hfuse:w:$(HEX_DIR)/hfuse.hex:h 
	$(PROG_SOFT) -p $(TARGET) -c $(PROG_DEV) -P $(DEV_PORT) -b57600 -v -u -U efuse:w:$(HEX_DIR)/efuse.hex:h 

clean:
	rm -rf $(BUILD_DIR)
	rm -f $(BIN_DIR)/$(NAME).elf
	rm -f $(HEX_DIR)/$(NAME).hex
	rm -f $(HEX_DIR)/eeprom.hex
	
