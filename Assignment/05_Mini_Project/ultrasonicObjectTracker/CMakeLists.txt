cmake_minimum_required(VERSION 3.20)
project(ultrasonicObjectTracker)

if(NOT CMAKE_TOOLCHAIN_FILE)
    message(FATAL_ERROR
        "This project must be configured with the AVR toolchain file, e.g.\n"
        "  cmake -B build-avr -S . -DCMAKE_TOOLCHAIN_FILE=cmake/avr-toolchain.cmake\n"
        "For host-side unit tests instead, configure tests/ directly:\n"
        "  cmake -B build-tests -S tests")
endif()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#add_compile_options(-Wall -Wextra -Werror -Wconversion -Wshadow)

set(SOURCE_FILES
    src/main.cpp
    src/uart.cpp
    src/timer.cpp
    src/adc.cpp
)

add_executable(ultrasonicObjectTracker.elf ${SOURCE_FILES})
target_include_directories(ultrasonicObjectTracker.elf PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/ include)

# Print flash/SRAM usage after every build
add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
    COMMAND ${AVR_SIZE} --mcu=${AVR_MCU} --format=avr $<TARGET_FILE:${PROJECT_NAME}.elf>
    COMMENT "Firmware size (flash/SRAM):"
)

# .elf -> .hex conversion, format avrdude actually uses
add_custom_command(
    OUTPUT  ${PROJECT_NAME}.hex
    COMMAND ${AVR_OBJCOPY} -O ihex -R .eeprom 
            $<TARGET_FILE:${PROJECT_NAME}.elf> ${PROJECT_NAME}.hex
    DEPENDS ${PROJECT_NAME}.elf
    COMMENT "Generating ${PROJECT_NAME}.hex"
)

add_custom_target(hex ALL DEPENDS ${PROJECT_NAME}.hex)

# Convenience upload target: cmake --build build-avr --target flash
if(AVRDUDE)
    add_custom_target(flash
        COMMAND ${AVRDUDE} -c ${AVR_PROGRAMMER} -p ${AVR_MCU}
                -P ${AVR_UPLOAD_PORT} -b ${AVR_UPLOAD_BAUD}
                -U flash:w:${PROJECT_NAME}.hex:i
        DEPENDS ${PROJECT_NAME}.hex
        COMMENT "Flashing ${PROJECT_NAME}.hex to ${AVR_UPLOAD_PORT}"
        VERBATIM
    )
endif()