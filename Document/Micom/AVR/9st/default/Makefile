###############################################################################
# Makefile for the project atmega128
###############################################################################

## General Flags
PROJECT = atmega128
MCU = atmega128
TARGET = atmega128.elf
CC = avr-gcc

CPP = avr-g++

## Options common to compile, link and assembly rules
COMMON = -mmcu=$(MCU)

## Compile options common for all C compilation units.
CFLAGS = $(COMMON)
CFLAGS += -Wl,-u,vfprintf -lprintf_flt -lm 
CFLAGS += -MD -MP -MT $(*F).o -MF dep/$(@F).d 

## Assembly specific flags
ASMFLAGS = $(COMMON)
ASMFLAGS += $(CFLAGS)
ASMFLAGS += -x assembler-with-cpp -Wa,-gdwarf2

## Linker flags
LDFLAGS = $(COMMON)
LDFLAGS +=  -Wl,-Map=atmega128.map


## Intel Hex file production flags
HEX_FLASH_FLAGS = -R .eeprom -R .fuse -R .lock -R .signature

HEX_EEPROM_FLAGS = -j .eeprom
HEX_EEPROM_FLAGS += --set-section-flags=.eeprom="alloc,load"
HEX_EEPROM_FLAGS += --change-section-lma .eeprom=0 --no-change-warnings


## Include Directories
INCLUDES = -I"D:\AVR_MID\9st\driver\inc" -I"D:\AVR_MID\9st\inc" 

## Objects that must be built in order to link
OBJECTS = main.o led.o fnd.o ExtInt.o Uart.o Timer.o ADC.o lcd.o Key.o Remocon.o event.o clock.o rtc.o i2c.o gps.o 

## Objects explicitly added by the user
LINKONLYOBJECTS = 

## Build
all: $(TARGET) atmega128.hex atmega128.eep atmega128.lss size

## Compile
main.o: ../main.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

led.o: ../driver/src/led.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

fnd.o: ../driver/src/fnd.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

ExtInt.o: ../driver/src/ExtInt.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

Uart.o: ../driver/src/Uart.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

Timer.o: ../driver/src/Timer.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

ADC.o: ../driver/src/ADC.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

lcd.o: ../driver/src/LCD/lcd.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

Key.o: ../driver/src/Key.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

Remocon.o: ../driver/src/Remocon.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

event.o: ../event/event.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

clock.o: ../app/clock/clock.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

rtc.o: ../driver/src/rtc.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

i2c.o: ../driver/src/i2c.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

gps.o: ../app/gps/gps.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

##Link
$(TARGET): $(OBJECTS)
	 $(CC) $(LDFLAGS) $(OBJECTS) $(LINKONLYOBJECTS) $(LIBDIRS) $(LIBS) -o $(TARGET)

%.hex: $(TARGET)
	avr-objcopy -O ihex $(HEX_FLASH_FLAGS)  $< $@

%.eep: $(TARGET)
	-avr-objcopy $(HEX_EEPROM_FLAGS) -O ihex $< $@ || exit 0

%.lss: $(TARGET)
	avr-objdump -h -S $< > $@

size: ${TARGET}
	@echo
	@avr-size -C --mcu=${MCU} ${TARGET}

## Clean target
.PHONY: clean
clean:
	-rm -rf $(OBJECTS) atmega128.elf dep/* atmega128.hex atmega128.eep atmega128.lss atmega128.map


## Other dependencies
-include $(shell mkdir dep 2>NUL) $(wildcard dep/*)

