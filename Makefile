######################################
# Makefile
# The template used from Stm32fx CubeMX
#####################################

######################################
# PROJECT
######################################
PROJECT = avr-soft-pwm
TARGET = atmega328p
PROG_SOFT = avrdude
PROG_DEV = arduino
DEV_PORT = /dev/ttyACM0


######################################
# building variables
######################################
# debug build?
DEBUG = 1
# optimization
OPT = -Og


#######################################
# paths
#######################################
# Build path
BUILD_DIR = build
BIN_DIR = bin
HEX_DIR = hex
######################################
# source
######################################
# C sources
C_SOURCES =  \
src/main.c \
src/sig.c \
src/sin.c


# ASM sources
ASM_SOURCES =  


#######################################
# binaries
#######################################
PREFIX =avr-
# The gcc compiler bin path can be either defined in make command via GCC_PATH variable (> make GCC_PATH=xxx)
# either it can be added to the PATH environment variable.
ifdef GCC_PATH
CC = $(GCC_PATH)/$(PREFIX)gcc
AS = $(GCC_PATH)/$(PREFIX)gcc -x assembler-with-cpp
CP = $(GCC_PATH)/$(PREFIX)objcopy
SZ = $(GCC_PATH)/$(PREFIX)size
else
CC = $(PREFIX)gcc
AS = $(PREFIX)gcc -x assembler-with-cpp
CP = $(PREFIX)objcopy
SZ = $(PREFIX)size
endif
BIN = $(CP) -O binary -S

#######################################
# CFLAGS
#######################################
# macros for gcc
# AS defines
AS_DEFS =

# C defines
C_DEFS = 


# AS includes
AS_INCLUDES =  \
-I/inc

# C includes
C_INCLUDES =  \
-Iinc \

# compile gcc flags
ASFLAGS = -xassembler-with-cpp -mmcu=$(TARGET) -nostdlib

CFLAGS = -mmcu=$(TARGET) $(C_DEFS) $(C_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2
endif


# Generate dependency information
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"


#######################################
# LDFLAGS
#######################################
# link script


# libraries
LIBS =
LIBDIR =
LDFLAGS = 
# default action: build all
all: $(BIN_DIR)/$(PROJECT).elf $(HEX_DIR)/$(PROJECT).hex


#######################################
# build the application
#######################################
# list of objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))
# list of ASM program objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR)
	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
	$(AS) -c $(CFLAGS) $< -o $@

$(BIN_DIR)/$(PROJECT).elf: $(OBJECTS) Makefile
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@

$(HEX_DIR)/$(PROJECT).hex: $(BIN_DIR)/$(PROJECT).elf Makefile
	$(CP) -O ihex -R .eeprom $< $@
	$(SZ) $@


$(BUILD_DIR)/%.hex: $(BULD_DIR)/%.elf | $(BUILD_DIR)
	$(HEX) $< $@
	
$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(BIN) $< $@	
	
$(BUILD_DIR):
	mkdir $@		

.PHONY: clean deploy-flash deploy-eeprom set-fuse

deploy-flash:
	$(PROG_SOFT) -p $(TARGET) -c $(PROG_DEV) -P $(DEV_PORT) -v -u -U flash:w:$(HEX_DIR)/$(PROJECT).hex

deploy-eeprom:
	$(OBJCOPY) -I binary -O ihex --change-addresses=0x0020 $(DOCS_PATH)/eeprom.txt $(HEX_DIR)/eeprom.hex 
	$(PROG_SOFT) -p $(TARGET) -c $(PROG_DEV) -P $(DEV_PORT) -v -u -U eeprom:w:$(HEX_DIR)/eeprom.hex

set-fuse:
	$(PROG_SOFT) -p $(TARGET) -c $(PROG_DEV) -P $(DEV_PORT) -v -u -U lfuse:w:$(HEX_DIR)/lfuse.hex:h 
	$(PROG_SOFT) -p $(TARGET) -c $(PROG_DEV) -P $(DEV_PORT) -v -u -U hfuse:w:$(HEX_DIR)/lfuse.hex:h 
	$(PROG_SOFT) -p $(TARGET) -c $(PROG_DEV) -P $(DEV_PORT) -v -u -U efuse:w:$(HEX_DIR)/efuse.hex:h 

clean:
	# rm -f $(BUILD_DIR)/*.o
	-rm -fR $(BUILD_DIR)
	rm -f $(HEX_DIR)/$(PROJECT).hex
	rm -f $(HEX_DIR)/eeprom.hex


#######################################
# dependencies
#######################################
-include $(wildcard $(BUILD_DIR)/*.d)

# *** EOF ***