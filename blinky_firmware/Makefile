# Makefile for Lab03-Blinky, ELEC424 Fall 2014
# Authors: Jie Liao, Abeer Javed, Steven Arroyo. Rice University 
# Derived from the crazyflie-firmware Makefile

# Path Definitions
STM_LIB := ../../STM32F10x_StdPeriph_Lib_V3.5.0/Libraries
INCLUDE_DIR = inc
LINK_DIR = linker_script
STARTUP_DIR := $(STM_LIB)/CMSIS/CM3/DeviceSupport/ST/STM32F10x/startup/gcc_ride7
SYSTEM_LIBRARY_INCLUDE_DIR := $(STM_LIB)/STM32F10x_StdPeriph_Driver/inc/
SYSTEM_LIBRARY_SRC_DIR := $(STM_LIB)/STM32F10x_StdPeriph_Driver/src/
DEVICE_SUPPORT_DIR := $(STM_LIB)/CMSIS/CM3/DeviceSupport/ST/STM32F10x/
CORE_INCLUDE_DIR := $(STM_LIB)/CMSIS/CM3/CoreSupport/

# Compiler 
CC = arm-none-eabi-gcc

# Particular processor
PROCESSOR = -mcpu=cortex-m3 -mthumb

# Directories of used header files
SEARCH_DIRECTORIES := -I $(INCLUDE_DIR)
SEARCH_DIRECTORIES += -I $(SYSTEM_LIBRARY_INCLUDE_DIR) -I $(SYSTEM_LIBRARY_SRC_DIR)
SEARCH_DIRECTORIES += -I $(DEVICE_SUPPORT_DIR) -I $(CORE_INCLUDE_DIR)

# STM chip specific flags
STFLAGS = -DSTM32F10X_MD $(SEARCH_DIRECTORIES) -include $(INCLUDE_DIR)/stm32f10x_conf.h

# Define the compiler flags
CFLAGS = -O0 -g3 $(PROCESSOR) $(Include) $(STFLAGS) -Wl,--gc-sections -T $(LINK_DIR)/stm32_flash.ld 

# Source files to include
FILES_TO_LINK := src/blinky.c
FILES_TO_LINK += $(SYSTEM_LIBRARY_SRC_DIR)/stm32f10x_rcc.c
FILES_TO_LINK += $(SYSTEM_LIBRARY_SRC_DIR)/stm32f10x_gpio.c
# FILES_TO_LINK += $(SYSTEM_LIBRARY_SRC_DIR)/stm32f10x_rtc.c
FILES_TO_LINK += $(SYSTEM_LIBRARY_SRC_DIR)/stm32f10x_tim.c
FILES_TO_LINK += $(SYSTEM_LIBRARY_SRC_DIR)/misc.c
FILES_TO_LINK += $(DEVICE_SUPPORT_DIR)/system_stm32f10x.c

# Build all relevant files and create .elf
all: 
	@$(CC) $(CFLAGS) $(STARTUP_DIR)/startup_stm32f10x_md.s -o bin/blinky.elf $(FILES_TO_LINK)

# Program .elf into Crazyflie flash memory via the busblaster
flash:
	@openocd -d0 -f interface/busblaster.cfg -f target/stm32f1x.cfg -c init -c targets -c "reset halt" -c "flash write_image erase bin/blinky.elf" -c "verify_image bin/blinky.elf" -c "reset run" -c shutdown

# Runs OpenOCD, opens GDB terminal, and establishes connection with Crazyflie
debug:
	@xterm -iconic -e openocd -f interface/busblaster.cfg -f target/stm32f1x.cfg -c 'init; targets; reset halt;' &
	@arm-none-eabi-gdb bin/blinky.elf -ex 'target remote:3333'
	@killall openocd

# Remove all files generated by target 'all'
clean:
	@rm bin/blinky.elf	
