cmake_minimum_required(VERSION 3.10)

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/avr.toolchain.cmake)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/avr.toolchain.cmake)

project(12_counter_LCD
LANGUAGES CXX
VERSION 1.0.0
DESCRIPTION "Button Counter with LCD Display"
)

        set(MCU "atmega328p")
        set(F_CPU "16000000UL")
        set(COM_PORT "COM12")

        set(CMAKE_CXX_FLAGS "-mmcu=${MCU} -DF_CPU=${F_CPU} -Os -Wall -std=c++11")

        add_executable(${PROJECT_NAME}.elf src/main.cpp src/lcd.cpp)
        add_custom_target(${PROJECT_NAME}.hex ALL
            COMMAND ${AVR_OBJCOPY} -O ihex -R .eeprom "${PROJECT_NAME}.elf" "${PROJECT_NAME}.hex"
            DEPENDS ${PROJECT_NAME}.elf
        )

        add_custom_command(TARGET ${PROJECT_NAME}.hex POST_BUILD
            COMMAND ${AVR_SIZE_TOOL} -C --mcu=${MCU} "${PROJECT_NAME}.elf"
        )

target_include_directories(${PROJECT_NAME}.elf PRIVATE include)