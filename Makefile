NAME = avr-soft-pwm
CC = avr-gcc
OBJCOPY = avr-objcopy
PROG_SOFT = avrdude
PROG_DEV = arduino
DEV_PORT = /dev/ttyUSB0

TARGET = atmega328p
BUILD_PATH = ./build
SRC_PATH = ./src
HEX_PATH = ./hex
BIN_PATH = ./bin
TOOLS_PATH = ./tools

OBJS  = $(BUILD_PATH)/main.o
OBJS += $(BUILD_PATH)/soft_pwm.o
OBJS += $(BUILD_PATH)/sig.o
OBJS += $(BUILD_PATH)/sin.o 


INC = -Iinc

CFLAGS = -mmcu=$(TARGET) -Os $(INC)
ifeq (${INIT_EEPROM}, 1)
CFLAGS += -DINIT_EEPROM
endif

ASMFLAGS = -xassembler-with-cpp -mmcu=$(TARGET) -nostdlib $(INC)
LIBS = 

$(BUILD_PATH)/%.o: $(SRC_PATH)/%.c
	$(CC)  $(CFLAGS) -c -o $@ $<


$(HEX_PATH)/$(NAME).hex: $(BIN_PATH)/$(NAME).elf
	$(OBJCOPY) -O ihex -R .eeprom $< $@
	

$(BIN_PATH)/$(NAME).elf: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^
	avr-size $@

.PHONY: clean install-flash install-eeprom set-fuse

install-flash:
	$(PROG_SOFT) -p $(TARGET) -c $(PROG_DEV) -P $(DEV_PORT) -b57600 -v -u -U flash:w:$(HEX_PATH)/$(NAME).hex

install-eeprom:
	$(OBJCOPY) -I binary -O ihex $(TOOLS_PATH)/eeprom.bin $(HEX_PATH)/eeprom.hex 
	$(PROG_SOFT) -p $(TARGET) -c $(PROG_DEV) -P $(DEV_PORT) -b57600 -v -u -U eeprom:w:$(HEX_PATH)/eeprom.hex

set-fuse:
	$(PROG_SOFT) -p $(TARGET) -c $(PROG_DEV) -P $(DEV_PORT) -b57600 -v -u -U lfuse:w:$(HEX_PATH)/lfuse.hex:h 
	$(PROG_SOFT) -p $(TARGET) -c $(PROG_DEV) -P $(DEV_PORT) -b57600 -v -u -U hfuse:w:$(HEX_PATH)/lfuse.hex:h 
	$(PROG_SOFT) -p $(TARGET) -c $(PROG_DEV) -P $(DEV_PORT) -b57600 -v -u -U efuse:w:$(HEX_PATH)/efuse.hex:h 

clean:
	rm -f $(BUILD_PATH)/*.o
	rm -f $(BIN_PATH)/$(NAME).elf
	rm -f $(HEX_PATH)/$(NAME).hex
	rm -f $(HEX_PATH)/eeprom.hex
	
