cmake_minimum_required(VERSION 3.10)
#1. Set the toolchain file BEFORE defining the project
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/avr.toolchain.cmake)

project(Servo_Pot_controller C CXX)

#2. Microcontroller Settings
set(MCU "atmega328p")
set(F_CPU 16000000UL)   # Arduino Uno uses ATmega328P runs at 16MHz
set(COM_PORT "COM12")   # Change this to your COM port

#3. Compiler  flags for AVR
set(CMAKE_C_FLAGS "-mmcu=${MCU} -DF_CPU=${F_CPU} -Os -Wall -Wstrict-prototypes")

#4.  Define the executable (Notice we now point to src/main.c)
add_executable(${PROJECT_NAME}.elf src/main.c)

#Create a hex file from the elf file
add_custom_target(${PROJECT_NAME}.hex ALL
COMMAND ${AVR_OBJCOPY} -O ihex -R .eeprom "${PROJECT_NAME}.elf" "${PROJECT_NAME}.hex"
DEPENDS ${PROJECT_NAME}.elf)

#Print the size of the firmware
add_custom_command(TARGET ${PROJECT_NAME}.hex POST_BUILD
COMMAND ${AVR_SIZE_TOOL} -C --mcu=${MCU} "${PROJECT_NAME}.elf")

#Optional: Add a "flash" target

add_custom_target(upload
COMMAND ${AVRDUDE} -c arduino -p${MCU} -P ${COM_PORT} -b 115200 -U flash:w:${PROJECT_NAME}.hex:i
DEPENDS ${PROJECT_NAME}.hex)